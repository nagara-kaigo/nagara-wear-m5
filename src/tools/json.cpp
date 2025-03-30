#include <ArduinoJson.h>
#include "json.h"
//JSONパース関数(HTTPを考慮しない)
//JSONから任意のパーツを取り出す
String getJsonValue(const String& jsonText, const String& part) {
    // 1) JSON解析用のドキュメントを用意（バッファサイズ 1024）
    DynamicJsonDocument doc(1024);
  
    // 2) JSON文字列をdocにパース
    DeserializationError error = deserializeJson(doc, jsonText);
    if (error) {
      // パース失敗時はログを出して空文字を返す
      Serial.println("[Error] Failed to parse JSON");
      return "";
    }
  
    // 3) doc[part] から値を取得
    //    ここで .as<String>() を使って Arduino String に変換
    if (doc[part].isNull()) {
      // 指定したキーがJSONに含まれていない場合も空文字を返す
      return "";
    }
  
    // キーが存在すれば文字列として取得
    String value = doc[part].as<String>();
    return value;
  }
  
  
  String getValueInJson(const String& jsonText, const String& part, const String& field) {
    // 1) JSONをパースする
    DynamicJsonDocument doc(2048); // 必要に応じて容量調整
    DeserializationError error = deserializeJson(doc, jsonText);
    if (error) {
      Serial.print("[Error] Failed to parse JSON: ");
      Serial.println(error.c_str());
      return "";
    }
  
    // 2) "items" が配列か確認
    if (!doc[part].is<JsonArray>()) {
      Serial.println("[Error] 'items' is not an array or not found");
      return "";
    }
    JsonArray itemsArray = doc[part].as<JsonArray>();
    if (itemsArray.size() == 0) {
      Serial.println("[Error] 'items' array is empty");
      return "";
    }
  
    // 3) 配列の先頭要素(0番目)から、指定したキーの値を取得
    //    もしキーが存在しなければ空文字を返す
    String result = itemsArray[0][field] | "";
  
    return result;
  }