#include "network_handler.h"

NetworkHandler::NetworkHandler() {
    client.setInsecure();  // SSL 証明書の検証を無効化
}

bool NetworkHandler::sendHttpPostRequest(const String& url, const String& headers, const String& body, String& response) {
    if (!client.connect("api.openai.com", 443)) {
        Serial.println("APIサーバーに接続できませんでした");
        return false;
    }

    client.print("POST " + url + " HTTP/1.1\r\n");
    client.print("Host: api.openai.com\r\n");
    client.print(headers);
    client.print("Content-Length: " + String(body.length()) + "\r\n\r\n");
    client.print(body);

    // レスポンス取得
    while (client.available() == 0) {
        delay(10);
    }

    response = "";
    while (client.available()) {
        response += client.readString();
    }

    client.stop();
    return true;
}
