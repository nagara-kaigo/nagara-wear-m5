#include "whisper_client.h"
#include "network_handler.h"
#include "SD.h"
#include "config.h"
#include "../task_manager.h"
#include <string>
#include <ArduinoJson.h>


//extern AudioRecorder recorder;
const char* API_KEY = OPENAI_API_KEY;

//パース後のテキスト変数
String JPresponse;


void writeWavHeader(File file, int sampleRate, int bitsPerSample, int numChannels) {
    uint32_t fileSize = 0; // 後で更新
    uint32_t dataChunkSize = 0;
  
    uint8_t wavHeader[44] = {
      'R','I','F','F',
      (uint8_t)(fileSize      ), (uint8_t)(fileSize >> 8 ), (uint8_t)(fileSize >>16 ), (uint8_t)(fileSize >>24 ),
      'W','A','V','E',
      'f','m','t',' ',
      16,0,0,0,
      1,0,
      (uint8_t)numChannels, (uint8_t)(numChannels >> 8),
      (uint8_t)(sampleRate      ), (uint8_t)(sampleRate >> 8 ), (uint8_t)(sampleRate >>16 ), (uint8_t)(sampleRate >>24 ),
      (uint8_t)((sampleRate * numChannels * bitsPerSample/8)      ),
      (uint8_t)((sampleRate * numChannels * bitsPerSample/8) >> 8 ),
      (uint8_t)((sampleRate * numChannels * bitsPerSample/8) >>16 ),
      (uint8_t)((sampleRate * numChannels * bitsPerSample/8) >>24 ),
      (uint8_t)(numChannels * bitsPerSample/8),0,
      (uint8_t)bitsPerSample,0,
      'd','a','t','a',
      (uint8_t)(dataChunkSize      ), (uint8_t)(dataChunkSize >> 8 ),
      (uint8_t)(dataChunkSize >>16 ), (uint8_t)(dataChunkSize >>24 )
    };
  
    file.write(wavHeader, 44);
  }

  void updateWavHeader(File file) {
    if (!file) return;
    uint32_t fileSize = file.size();
    uint32_t dataChunkSize = fileSize - 44; // 実際のデータサイズ
  
    file.seek(4);
    file.write((uint8_t *)&fileSize, 4);
  
    file.seek(40);
    file.write((uint8_t *)&dataChunkSize, 4);
  }



  //JSONから任意のパーツを取り出す
  String getJsonValue(const String& response, const String& key) {
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
    File recordingFile = SD.open("/recording.wav", FILE_READ);
    if (!recordingFile) {
        Serial.println("録音ファイルを開けませんでした");
        return;
    }

    if (recorder.isRecording()) {
        Serial.println("task1 isRecording: reading from ring buffer");
  
        // リングバッファから未処理分を読み取る
        size_t available = 0;
        if (xSemaphoreTake(recorder.getRingBufferMutex(), (TickType_t)100) == pdTRUE) {
          // いまの書き込み位置をコピーして、
          size_t currentWriteIndex = recorder.getwriteIndex();
          // (writeIndex - readIndex + BUFFER_SIZE) % BUFFER_SIZE が未読バイト数
          available = (currentWriteIndex + BUFFER_SIZE - recorder.getreadIndex()) % BUFFER_SIZE;
  
          // 大きすぎると chunkFile が巨大になるので、必要なら制限
          // ここではとりあえず全部読み出す
          for (size_t i = 0; i < available; i++) {
            uint8_t* tempBuf = recorder.gettempBuffer();
            tempBuf[i] = recorder.getaudioRingBuffer()[recorder.getreadIndex()];
            recorder.setReadIndex((recorder.getreadIndex() + 1) % BUFFER_SIZE);
          }
          xSemaphoreGive(recorder.getRingBufferMutex());
        }
  
        if (available == 0) {
          Serial.println("No new data in ring buffer");
        }
        Serial.println("open SD");
        SD.remove("/recording.wav");
        recordingFile = SD.open("/recording.wav", FILE_WRITE);
        writeWavHeader(recordingFile, 16000, 16, 1);
        recordingFile.write(recorder.gettempBuffer(), available);
        updateWavHeader(recordingFile);
        recordingFile.flush();
        recordingFile.close();
    }
    Serial.println("complete reccording.wav");
    recordingFile = SD.open("/recording.wav", FILE_READ);
    Serial.println("open SDcard for Reading");



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

    JPresponse = getJsonValue(response,"text");
    Serial.println("API応答: " + response);

    Serial.println("API応答: " + JPresponse);
}


