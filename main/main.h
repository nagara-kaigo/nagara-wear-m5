#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

// アプリケーション全体で使用する状態管理構造体
struct AppState {
    String selectedUser;     // 選択されたユーザー名
    String selectedReceiver; // 選択された相手の名前
};

// 画面を識別する列挙型
enum Screen { RECEIVER_PICKER, FINAL_SCREEN };

#endif
