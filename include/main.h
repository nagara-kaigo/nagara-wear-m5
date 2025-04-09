#ifndef MAIN_H
#define MAIN_H

#define LCDWIDE 320
#define LCDHEIGHT 240

#include <Arduino.h>
#include <stack>
#include <vector>

//レジデントの情報を識別する構造体
struct Resident {
    String residentUid;
    String familyName;
    String givenName;
    
    // 引数ありコンストラクタ
    Resident(const String& uid, const String& fam, const String& given)
        : residentUid(uid), familyName(fam), givenName(given) {}
    
    // デフォルトコンストラクタも定義
    Resident() : residentUid(""), familyName(""), givenName("") {}
    };

// 画面を識別する列挙型
enum Screen { 
    USER_PICKER, 
    RESIDENT_PICKER, 
    STANDBY,
    FINAL_SCREEN,
    TRANSCRIPTION,
    EXTRACT,
    RECORD_TYPE_PICKER
};

enum RecordType{
    MEAL,
    DRINK,
    EXCRETION,
    BATH,
    EVERYDAY
};

inline String recordTypeToString(RecordType type) {
    switch (type) {
        case MEAL:       return "食事";
        case DRINK:      return "飲料";
        case EXCRETION:  return "排泄";
        case BATH:       return "入浴";
        case EVERYDAY:   return "日常";
        default:         return "";
    }
}

enum MealTime{
    BREAKFAST,
    LUNCH,
    DINNER
};

// アプリケーション全体で使用する状態管理構造体
struct AppState {
    String selectedUser;     // 選択されたユーザー名
    Resident selectedResident; //選択されたレジデントの情報を保持
    Screen currentScreen;    //現在のスクリーン
    std::stack<Screen> screenHistory;//戻る用のスクリーンスタック
    RecordType selectedRecordType; //選択された録音種類
    MealTime mealTime; //食事タイミング
    std::vector<Resident> residentsList; //レジデントの構造体配列
    size_t currentResidentPage = 0; // 現在のページ (0から)
    size_t totalResidentPage = 1;  // 総ページ数  (1から)
};

#endif
