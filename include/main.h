#ifndef MAIN_H
#define MAIN_H

#define LCDWIDE 320
#define LCDHEIGHT 240

#include <Arduino.h>
#include <stack>
#include "../src/services/api/residents.h"
#include <vector>


// 画面を識別する列挙型
enum Screen { 
    USER_PICKER, 
    RESIDENT_PICKER, 
    STANDBY,
    RECORDING,
    FINAL_SCREEN,
    TRANSCRIPTION,
    MEAL_EXTRACT,
    RECORD_TYPE_PICKER
};

enum RecordType{
    MEAL,
    DRINK,
    EXCRETION,
    BATH,
    EVERYDAY
};

enum MealTime{
    BREAKFAST,
    LUNCH,
    DINNER
};

// アプリケーション全体で使用する状態管理構造体
struct AppState {
    String selectedUser;     // 選択されたユーザー名
    std::vector<String> selectedResidentId; // 選択されたレジデントのid
    std::vector<String> selectedResidentFamilyName;// 選択されたレジデントの苗字
    std::vector<String> selectedResidentGivenName;// 選択されたレジデントの名前
    Screen currentScreen;    //現在のスクリーン
    std::stack<Screen> screenHistory;//戻る用のスクリーンスタック
    RecordType selectedRecordType; //選択された録音種類
    MealTime mealTime; //食事タイミング
    std::vector<Resident> residentsList; //レジデントの構造体配列
    size_t currentResidentPage = 0; // 現在のページ (0から)
    size_t totalResidentPage = 1;  // 総ページ数  (1から)
};

#endif
