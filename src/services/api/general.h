#ifndef GENERAL_H
#define GENERAL_H
#include <Arduino.h>
#include "api.h"

//HtTP POST　リクエストの共通関数
String httpPostJson(MyApi& api, const String& endpoint, const String& jsonBody, const String& token = "");

// HTTP GET リクエストの共通関数
String httpGet(MyApi& api, const String& endpoint, const String& token = "");

String httpPatchJson(MyApi& api, const String& endpoint, const String& jsonBody, const String& token = "");

#endif