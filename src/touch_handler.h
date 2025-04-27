#ifndef TOUCH_HANDLER_H
#define TOUCH_HANDLER_H
#include <M5Unified.h>

void handleTouchEvents();
void handleFooterTouch(const lgfx::v1::touch_point_t& touch);

#endif // TOUCH_HANDLER_H