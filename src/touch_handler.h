#ifndef TOUCH_HANDLER_H
#define TOUCH_HANDLER_H
#include <M5Unified.h>

#define SWIPE_RANGE 30

void handleTouchEvents();
void handleFooterTouch(const lgfx::v1::touch_point_t& touch);

#endif // TOUCH_HANDLER_H