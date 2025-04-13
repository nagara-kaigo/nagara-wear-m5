#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <Arduino.h>
#include <vector>
#include "main.h" // vector<Resident>を使うために必要

String getJsonValue(const String& jsonText, const String& part);
String getValueInJson(const String& jsonText, const String& part, const String& field);
std::vector<Resident> getValueAllInJson(const String& jsonStr,const String& arrayKey,const std::vector<String>& fields);

#endif
