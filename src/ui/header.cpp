#include "header.h"
#include <M5Unified.h>

void showHeaderBar(const String &title) {
    M5.Display.drawLine(10, 30, 310, 30, TFT_BLACK);
    M5.Display.setTextDatum(textdatum_t::middle_center);
    M5.Display.drawString(title, 160, 15);
}