# DCON2025-wear
## 概要
文字起こしから介護記録の情報を抽出して記録するサービスで用いるウェアラブルデバイスのコード。

## セットアップ
1. リポジトリのクローンと移動
```
git clone git@github.com:shun-harutaro/dcon2025-wear.git
cd dcon2025-wear
```
2. config.env の作成
```
touch config.env
echo "WIFI_SSID=[wifi_ssid]" >> config.env
echo "WIFI_PASSWORD=[wifi_password]" >> config.env
echo "OPENAI_API_KEY=[openai_api_key]" >> config.env
echo "SERVER_URL=[server_url]" >> config.env
echo "DEFAULT_USER_UUID=[default_user_uuid]" >> config.env
echo "CARE_RECEIVER_UUID_1=[care_receiver_uuid]" >> config.env
echo "CARE_RECEIVER_UUID_2=[care_receiver_uuid]" >> config.env
echo "CARE_RECEIVER_UUID_3=[care_receiver_uuid]" >> config.env
```
3. config.h の作成
```
python generate_config.py
```
4. Arduino IDE で `src/main.ino`を開いて転送
