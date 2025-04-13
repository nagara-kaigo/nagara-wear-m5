#ifndef MY_API_H
#define MY_API_H

#include <Arduino.h>
#include "config.h" // Base URL

class MyApi {
public:
  //ゲッター
  String getuserToken() const {return userToken;};

  String getTenantUid() const {return tenantUid;};

  String getResidentUid() const {return residentUid;};

  //String getFoodRecordUid() const {return foodRecordUid;};
  String getRecordUid() const {return recordUid;};

  String getRecordExtract() const {return recordExtract;};

  String getBaseUrl() const {return _baseUrl;};

  //セッター
  void setuserToken(const String Value) {userToken = Value;};

  void settenantUid(const String Value) {tenantUid = Value;};

  void setresidentUid(const String Value) {residentUid = Value;};

  //void setfoodRecordUid(const String Value) {foodRecordUid = Value;};
  void setRecordUid(const String Value) {recordUid = Value;};

  void setRecordExtract(const String Value) { recordExtract = Value;};

  // コンストラクタ (API のベースURLを設定)
  MyApi(const String& baseUrl = API_BASE_URL);

  //ログイン
  String loginToApi(const String& ID, const String& password);

  // テナント一覧（権限ないから実行できない）
  String getTenants(const String& token);

  //ユーザー情報取得
  String getMe(const String& token);

  //チャット一覧取得
  String getChats(const String& token);

  //テナントレジデント取得
  String getTenantResident(const String& token);

  //テナントレジデント作成
  // MyApiクラスに新しいシグネチャを追記する
  String createResidents(const String& token,
    const String& familyName,
    const String& givenName,
    const String& familyNameFurigana,
    const String& givenNameFurigana,
    const String& dateOfBirth,
    const String& gender,
    const String& admissionDate);


private:
  String _baseUrl;

  String userToken;

  String tenantUid;

  String residentUid;

  //String foodRecordUid;
  String recordUid;

  String recordExtract;
};

#endif
