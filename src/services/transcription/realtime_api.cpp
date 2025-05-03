#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <mbedtls/base64.h>

extern WebSocketsClient webSocket;
constexpr size_t CHUNK_BYTES = 320;


String base64Encord(const uint8_t* data, size_t len) {
    // 出力サイズは 4 * ceil(len/3) + 終端用 1 バイト
    size_t output_len = 4 * ((len + 2) / 3) + 1;
    uint8_t* output = (uint8_t*)malloc(output_len);
    if (!output) {
        // メモリ確保失敗
        return String();
    }

    size_t olen = 0;
    int ret = mbedtls_base64_encode(output, output_len, &olen, data, len);
    if (ret != 0) {
        // エンコード失敗
        free(output);
        return String();
    }

    // 終端文字を入れて String に変換
    output[olen] = '\0';
    String encoded = String((char*)output);
    free(output);
    return encoded;
}


void sendAudioData(const uint8_t* pcmData, size_t dataLen) {
    size_t offset = 0;
    while (offset < dataLen) {
        // 送り残しが CHUNK_BYTES より少なければ残り全部、それ以外は CHUNK_BYTES
        size_t chunkSize = min(CHUNK_BYTES, dataLen - offset);

        // JSON 組み立て
        StaticJsonDocument<512> doc;
        doc["type"] = "audio_chunk";
        // Base64 化して格納
        doc["audio_chunk"] = base64Encord(pcmData + offset, chunkSize);

        // 送信
        String body;
        serializeJson(doc, body);
        webSocket.sendTXT(body);

        offset += chunkSize;
        webSocket.loop();
        delay(2);  // 数ミリ秒でもいいのでタスクを切り替えると安定しやすい
    }
}

void sendCreate() {
    StaticJsonDocument<512> doc;

    // 必須: イベント種別
    doc["type"] = "transcription_session.update";

    // ↓ここから “session” オブジェクト
    JsonObject session = doc.createNestedObject("session");

    // 16-bit PCM (Little-Endian) @ 24 kHz, mono
    session["input_audio_format"] = "pcm16";

    // ── 音声認識モデルとヒント ──
    JsonObject stt = session.createNestedObject("input_audio_transcription");
    stt["model"]    = "whisper-1";   // 例: whisper-1 / gpt-4o-mini-transcribe
    stt["language"] = "ja";          // ISO-639-1。自動判定で良ければ省略可
    // stt["prompt"] = "介護現場の会話です"  // 任意: 文脈のヒント

    // ── ノイズリダクション (近接マイク用) ──
    JsonObject nr = session.createNestedObject("input_audio_noise_reduction");
    nr["type"] = "near_field";       // far_field も選択可 / 無効なら省略

    // ── VAD(無音検出)設定 ──
    JsonObject vad = session.createNestedObject("turn_detection");
    vad["type"]                = "server_vad"; // または semantic_vad
    vad["threshold"]           = 0.5;          // 0.0–1.0：大きいほど音量が必要
    vad["prefix_padding_ms"]   = 300;          // 音声開始前をどれだけ残すか
    vad["silence_duration_ms"] = 500;          // 無音と判定する長さ

    // 送信
    String body;
    serializeJson(doc, body);
    webSocket.sendTXT(body);
}

  

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch (type) {
      case WStype_DISCONNECTED:
        Serial.println("WebSocket Disconnected");
        Serial.printf("[WS] DISCONNECTED: %.*s\n", length, payload);
        break;
      case WStype_CONNECTED:
        Serial.println("WebSocket Connected");
        Serial.println("sendCreate");
        sendCreate();
        break;
      case WStype_TEXT: {
        //receiveWebsockeetConnectedResponse(payload,length);
        Serial.println("WS connection sustain");
        Serial.printf("WS RX: %s\n", payload);
        break;
      default:
        break;
    }
  }
}


  