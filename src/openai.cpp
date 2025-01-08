#include "openai.h"
#include "config.h"

WiFiClientSecure client;

bool sendAudioFile(const String &filePath, String &response) {
    if (!client.connect("api.openai.com", 443)) {
        Serial.println("Connection failed!");
        return false;
    }

    String boundary = "----WebKitFormBoundary7MA4YWxkTrZu0gW";
    String contentType = "multipart/form-data; boundary=" + boundary;

    // HTTP リクエストの作成
    String requestBody;
    requestBody += "--" + boundary + "\r\n";
    requestBody += "Content-Disposition: form-data; name=\"file\"; filename=\"" + filePath + "\"\r\n";
    requestBody += "Content-Type: audio/mpeg\r\n\r\n";
    requestBody += "音声データをバイナリで追加する箇所\r\n";
    requestBody += "--" + boundary + "\r\n";
    requestBody += "Content-Disposition: form-data; name=\"model\"\r\n\r\n";
    requestBody += "whisper-1\r\n";
    requestBody += "--" + boundary + "--\r\n";

    // リクエスト送信
    client.println("POST " + String(API_URL_STT) + " HTTP/1.1");
    client.println("Host: api.openai.com");
    client.println("Authorization: Bearer " + String(OPENAI_API_KEY));
    client.println("Content-Type: " + contentType);
    client.println("Content-Length: " + String(requestBody.length()));
    client.println();
    client.print(requestBody);

    // レスポンスの取得
    while (client.connected()) {
        String line = client.readStringUntil('\n');
        if (line == "\r") {
            break;
        }
    }

    response = client.readString();
    client.stop();
    return true;
}
