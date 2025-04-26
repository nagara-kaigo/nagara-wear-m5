#include <WebSocketsClient.h>
#include <ArduinoJson.h>

extern WebSocketsClient webSocket;

void sendSessionUpdate() {
    StaticJsonDocument<512> doc;          // ← 少し余裕をもたせる
    doc["type"] = "session.update";

    JsonObject s = doc.createNestedObject("session");
    s["input_audio_format"] = "pcm16";    // 文字列で指定（必須）

    // ★オプションで VAD 設定も追加できます
    JsonObject vad = s.createNestedObject("turn_detection");
    vad["type"]               = "server_vad";
    vad["threshold"]          = 0.5;
    vad["silence_duration_ms"]= 300;

    String out;
    serializeJson(doc, out);

    if (webSocket.isConnected()) {        // 念のため接続確認
        webSocket.sendTXT(out);
    } else {
        Serial.println("WS not connected; session.update skipped");
    }
}

  

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch (type) {
      case WStype_DISCONNECTED:
        Serial.println("WebSocket Disconnected");
        break;
      case WStype_CONNECTED:
        Serial.println("WebSocket Connected");
        sendSessionUpdate();
        break;
      case WStype_TEXT:
        Serial.printf("Received: %s\n", payload);
        break;
      default:
        break;
    }
  }



void sendPcmChunk(const int16_t* data, size_t samples) {
// WebSocket がまだハンドシェイク中なら捨てる or バッファリング
if (webSocket.isConnected()) {
    webSocket.sendBIN(reinterpret_cast<const uint8_t*>(data),
                samples * sizeof(int16_t));
}
  }
  