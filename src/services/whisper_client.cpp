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
    String partModel = "--" + boundary + "\r\n" +
                       "Content-Disposition: form-data; name=\"model\"\r\n\r\n" +
                       "whisper-1\r\n";

    String headers =
        "Authorization: Bearer " + String(API_KEY) + "\r\n" +
        "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n" +
        "Connection: close\r\n";

    String body = partModel + "--" + boundary + "--\r\n";

    NetworkHandler network;
    String response;
    if (network.sendHttpPostRequest("/v1/audio/transcriptions", headers, body, response)) {
        Serial.println("API応答: " + response);
    } else {
        Serial.println("リクエスト送信に失敗しました");
    }

    recordingFile.close();
}
