#ifndef RESIDENTS_H
#define RESIDENTS_H

#include <Arduino.h>

class MyApi; // 前方宣言

String getTenantResidents(MyApi& api,const String& token);

String createResident(
    MyApi& api,
    const String& token,
    const String& familyName,
    const String& givenName,
    const String& familyNameFurigana,
    const String& givenNameFurigana,
    const String& dateOfBirth,
    const String& gender,
    const String& admissionDate);
    
#endif