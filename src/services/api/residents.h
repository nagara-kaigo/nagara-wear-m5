#ifndef RESIDENTS_H
#define RESIDENTS_H

#include <Arduino.h>
#include "api.h"

String getTenantResidents(MyApi& api);

String createResident(
    MyApi& api,
    const String& familyName,
    const String& givenName,
    const String& familyNameFurigana,
    const String& givenNameFurigana,
    const String& dateOfBirth,
    const String& gender,
    const String& admissionDate);
    
#endif