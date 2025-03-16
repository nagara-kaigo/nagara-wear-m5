#include "whisper_client.h"
#include "network_handler.h"
#include "SD.h"
#include "config.h"

const char* API_KEY = OPENAI_API_KEY;

void transcribeAudio() {
    File recordingFile = SD.open("/recording.wav", FILE_READ);
    if (!recordingFile) {
        Serial.println("録音ファイルを開けませんでした");
        return;
    }

    String boundary = "----M5StackBoundary";
    
    // `model` のパート
    String partModel = "--" + boundary + "\r\n" +
                       "Content-Disposition: form-data; name=\"model\"\r\n\r\n" +
                       "whisper-1\r\n";

    // `file` のヘッダー
    String partFileHeader = "--" + boundary + "\r\n" +
                            "Content-Disposition: form-data; name=\"file\"; filename=\"recording.wav\"\r\n" +
                            "Content-Type: audio/wav\r\n\r\n";

    String partEnd = "\r\n--" + boundary + "--\r\n";

    // **Content-Length の計算**
    size_t fileSize = recordingFile.size();
    size_t contentLength = partModel.length() + partFileHeader.length() + fileSize + partEnd.length();

    // **HTTP ヘッダーの作成**
    String headers = String(
        "POST /v1/audio/transcriptions HTTP/1.1\r\n") +
        "Host: api.openai.com\r\n" +
        "Authorization: Bearer " + String(API_KEY) + "\r\n" +
        "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n" +
        "Content-Length: " + String(contentLength) + "\r\n" +
        "Connection: close\r\n\r\n";

    // **HTTP リクエストの送信**
    NetworkHandler network;
    WiFiClientSecure& client = network.getClient();  // `WiFiClientSecure` の取得

    if (!client.connect("api.openai.com", 443)) {
        Serial.println("APIサーバーに接続できませんでした");
        return;
    }

    // **ヘッダー送信**
    client.print(headers);

    // **`model` のパートを送信**
    client.print(partModel);

    // **`file` のヘッダーを送信**
    client.print(partFileHeader);

    // **音声データをチャンク単位で送信**
    uint8_t buffer[512];
    size_t bytesRead;
    while ((bytesRead = recordingFile.read(buffer, sizeof(buffer))) > 0) {
        client.write(buffer, bytesRead);
    }

    // **最後のバウンダリを送信**
    client.print(partEnd);

    recordingFile.close();

    // **レスポンスの取得**
    String response = "";
    while (client.available() == 0) {
        delay(10);
    }

    while (client.available()) {
        response += client.readString();
    }

    client.stop();

    Serial.println("API応答: " + response);
}
