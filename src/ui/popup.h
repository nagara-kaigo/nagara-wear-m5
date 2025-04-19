#ifndef POPUP_H
#define POPUP_H

struct AppState; // 前方宣言

#define WIFI_POPUP_WIDTH  260
#define WIFI_POPUP_HEIGHT  80
#define WIFI_POPUP_STARTX  30
#define WIFI_POPUP_STARTY  80

void showWifiDisconnectedPopup(const AppState &state);

#endif