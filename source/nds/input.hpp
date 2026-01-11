#pragma once

#include <nds.h>

#include "../game/constants.hpp"

namespace DS_INPUT{
    extern void scan();
    extern int getKeysDown();
    extern int getKeysHeld();
    extern void getTouch(touchPosition& touch);

    extern bool anyKeyPressed(int key);
    extern bool touchDown(int key);
    extern bool touchScreenTouched(touchPosition& touch);
    extern bool touchInBounds(touchPosition& touch, const Constants::Rect& b_rect);
}