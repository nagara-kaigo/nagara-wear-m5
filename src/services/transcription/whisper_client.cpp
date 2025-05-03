#include "whisper_client.h"
#include "SD.h"
#include "config.h"
#include "../../task_manager.h"
#include <string>
#include <ArduinoJson.h>
#include <M5Core2.h>
#include "../../services/api/api.h"
#include "../../screens/screen_transcription.h"
#include "main.h"
#include "../../screens/screen_display_extract.h"
#include "../api/records.h"
#include <WiFiClientSecure.h>
#include "../../system/sd_handler.h"
#include "realtime_api.h"

extern AudioRecorder recorder;
const char* API_KEY = OPENAI_API_KEY;

//パース後のテキスト変数
String jpResponse;

extern WiFiClientSecure client;
extern WebSocketsClient webSocket;
//クラスの継承
extern MyApi api;
extern AppState appState;

const i2s_port_t I2S_PORT = I2S_NUM_0; // 実際に使っている I2S ポート




  //JSONから任意のパーツを取り出す
  String getHTTPJsonValue(const String& response, const String& key) {
    // 1) HTTPレスポンス文字列中でヘッダーとボディを区切りにしている "\r\n\r\n" を探す
    int index = response.indexOf("\r\n\r\n");
    if (index == -1) {
      // ヘッダーらしきものが見つからない場合はエラー扱い
      Serial.println("[Error] Could not find HTTP header delimiter.");
      return "";
    }

    // 2) JSONの部分を抜き出す
    String jsonPart = response.substring(index + 4);

    // 3) JSON解析用のドキュメントを用意（バッファサイズは適宜拡大可能）
    DynamicJsonDocument doc(1024);

    // 4) JSON文字列をdocにパース
    DeserializationError error = deserializeJson(doc, jsonPart);
    if (error) {
      // パース失敗時はログを出して空文字を返す
      Serial.println("[Error] Failed to parse JSON");
      return "";
    }

    // 5) doc[key] から値を取得し、String へ変換
    if (doc[key].isNull()) {
      // 指定したキーがJSONに含まれていない場合も空文字を返す
      return "";
    }
    String value = doc[key].as<String>();
    return value;
  }








void transcribeAudio() {
  uint8_t sendBuf[320];

  if (xSemaphoreTake(recorder.getRingBufferMutex(), 10 / portTICK_PERIOD_MS)) {
      if (recorder.isSendBufferReady(320)) {
          recorder->readFromBuffer(sendBuf, 320);  // 自作関数: バッファから320読み出し
          xSemaphoreGive(recorder->ringBufferMutex);
  
          String b64Audio = b64(sendBuf, 320);
          sendTranscriptionChunk(b64Audio);  // WebSocketで送信する関数
      } else {
          xSemaphoreGive(recorder->ringBufferMutex);
          vTaskDelay(5 / portTICK_PERIOD_MS);  // 少し待ってから再試行
      }
  }
}


