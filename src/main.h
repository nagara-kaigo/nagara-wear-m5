#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <M5Unified.h>
#include <ArduinoJson.h>
#include <stack>

enum RecordType {
    MEAL,
    DRINK,
    EXCRETION,
    BATH,
    EVERYDAY
};

enum MealTime {
    BREAKFAST,
    LUNCH,
    DINNER
};

enum Screen {
    ROADING,
    PICK_USER,
    PICK_RESIDENT,
    PICK_RECORD_TYPE,
    STANDBY,
    TRANSCRIPTION,
    EXTRACT
};

enum SwipeState {
    NONE,
    RIGHT,
    LEFT
};

struct Resident {
    String familyName;
    String givenName;
    String residentUid;
};

struct AppState {
    String userName;
    Resident selectedResident;
    RecordType selectedRecordType;
    MealTime mealTime;
    Screen currentScreen;
    std::vector<Resident> residentsList;
    size_t currentResidentPage;
    size_t totalResidentPage;
    std::stack<Screen> screenHistory;
};

inline String recordTypeToString(RecordType type) {
    switch (type) {
        case MEAL:       return "食事";
        case DRINK:      return "水分";
        case EXCRETION:  return "排泄";
        case BATH:       return "入浴";
        case EVERYDAY:   return "日常";
        default:         return "";
    }
}

#endif // MAIN_H 