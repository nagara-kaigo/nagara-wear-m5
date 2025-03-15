#include "whisper_client.h"
#include <Arduino.h>
#include <HTTPClient.h>
#include "SD.h"
#include "config.h"

const char* host = "api.openai.com";
const int httpsPort = 443;
const char* api_key = OPENAI_API_KEY;

void transcribeAudio(const char* filename) {
    WiFiClientSecure client;
    client.setInsecure();
    if (!client.connect(host, httpsPort)) {
        Serial.println("OpenAI APIへの接続に失敗しました");
        return;
    }
    File file = SD.open(filename, FILE_READ);
    if (!file) return;
    size_t fileSize = file.size();

    String boundary = "----M5StackBoundary";
    String partModel = "--" + boundary + "\r\n" + "Content-Disposition: form-data; name=\"model\"\r\n\r\n" + "whisper-1\r\n";
    String partLanguage = "--" + boundary + "\r\n" + "Content-Disposition: form-data; name=\"language\"\r\n\r\n" + "ja\r\n";
    String partFileHeader = "--" + boundary + "\r\n" + "Content-Disposition: form-data; name=\"file\"; filename=\"recording.wav\"\r\n" + "Content-Type: audio/wav\r\n\r\n";
    String partEnd = "\r\n--" + boundary + "--\r\n";

    size_t contentLength = partModel.length() + partLanguage.length() + partFileHeader.length() + fileSize + partEnd.length();
    String request = String("POST ") + "/v1/audio/transcriptions" + " HTTP/1.1\r\n" +
                    "Host: " + host + "\r\n" +
                    "Authorization: Bearer " + String(api_key) + "\r\n" +
                    "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n" +
                    "Content-Length: " + String(contentLength) + "\r\n" +
                    "Connection: close\r\n\r\n";
    
    client.print(request);
    client.print(partModel);
    client.print(partLanguage);
    client.print(partFileHeader);

    uint8_t buf[512];
    while (file.available()) {
        int n = file.read(buf, sizeof(buf));
        client.write(buf, n);
    }
    file.close();
}