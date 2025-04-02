#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <Arduino.h>

String getJsonValue(const String& jsonText, const String& part);
String getValueInJson(const String& jsonText, const String& part, const String& field);

#endif