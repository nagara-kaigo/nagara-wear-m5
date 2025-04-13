#include "template_elimination_extract.h"
#include "screen_manager.h"
#include <M5Core2.h>      

void showEliminationRecordFromJson(const JsonDocument& doc) {
    const char* eliminationMethod = doc["eliminationMethod"] | "UNKNOWN";
    bool hasFeces = doc["hasFeces"] | false;
    bool fecalIncontinence = doc["fecalIncontinence"] | false;
    const char* fecesAppearance = doc["fecesAppearance"] | "UNKNOWN";
    int fecesVolume = doc["fecesVolume"] | -1;
    bool hasUrine = doc["hasUrine"] | false;
    bool urinaryIncontinence = doc["fecalIncontinence"] | false;
    const char* urineAppearance = doc["fecesAppearance"] | "UNKNOWN";
    int urineVolume = doc["urineVolume"] | -1;
    const char* notes = doc["notes"] | "";

    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setCursor(0, 60);

    M5.Lcd.print("方法: ");
    M5.Lcd.println(eliminationMethod);

    if (hasFeces) {
        M5.Lcd.print("便: ");
        if (fecalIncontinence) {
            M5.Lcd.println("失禁");
        } else {
            M5.Lcd.print("量: ");
            if (fecesVolume >= 0) {
                M5.Lcd.printf("%d g\n", fecesVolume);
            } else {
                M5.Lcd.println("不明");
            }
            M5.Lcd.print("外観: ");
            M5.Lcd.println(fecesAppearance);
        }
    }

    if (hasUrine) {
        M5.Lcd.print("尿: ");
        if (urinaryIncontinence) {
            M5.Lcd.println("失禁");
        } else {
            M5.Lcd.print("量: ");
            if (urineVolume >= 0) {
                M5.Lcd.printf("%d ml\n", urineVolume);
            } else {
                M5.Lcd.println("不明");
            }
            M5.Lcd.print("外観: ");
            M5.Lcd.println(urineAppearance);
        }
    }

    M5.Lcd.print("特記事項: ");
    if (strlen(notes) > 0) {
        M5.Lcd.println(notes);
    } else {
        M5.Lcd.println("なし");
    }
}