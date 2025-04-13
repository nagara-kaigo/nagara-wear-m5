#include <M5Core2.h>      
#include "template_food_extract.h"
#include "../../ui/header.h"
#include "../../ui/footer.h"

void showFoodRecordFromJson(const JsonDocument& doc) {
    // JSONデータから必要な値を取得
    int mainCoursePercentage = doc["mainCoursePercentage"];
    int sideDishPercentage = doc["sideDishPercentage"];
    int soupPercentage = doc["soupPercentage"];
    String beverageType = doc["beverageType"].as<String>();
    int beverageVolume = doc["beverageVolume"];
    String notes = doc["notes"].as<String>();
 
    // データを画面に表示
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextSize(2);
     
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.print("Main Course %: ");
    M5.Lcd.println(mainCoursePercentage);
 
    M5.Lcd.print("Side Dish %: ");
    M5.Lcd.println(sideDishPercentage);
 
    M5.Lcd.print("Soup %: ");
    M5.Lcd.println(soupPercentage);
 
    M5.Lcd.print("Beverage Type: ");
    M5.Lcd.println(beverageType);
 
    M5.Lcd.print("Beverage Volume: ");
    M5.Lcd.println(beverageVolume);
 
    M5.Lcd.print("Notes: ");
    M5.Lcd.println(notes);
}
