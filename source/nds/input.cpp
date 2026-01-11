#include "input.hpp"

namespace DS_INPUT{
    void scan(){
        scanKeys();
    }

    int getKeysDown(){
        return keysDown();
    }

    int getKeysHeld(){
        return keysHeld();
    }

    void getTouch(touchPosition& touch){
        return touchRead(&touch);
    }

    bool anyKeyPressed(int key){
        return key != 0 && (key & KEY_TOUCH) == 0;
    }

    bool touchDown(int key){
        return (key & KEY_TOUCH) != 0;
    }

    bool touchScreenTouched(touchPosition& touch){
        return touch.px > 0 || touch.py > 0;
    }

    bool touchInBounds(touchPosition& touch, const Constants::Rect& b_rect){
         return touch.px >= b_rect.x && touch.px <= b_rect.x + b_rect.w &&
                touch.px >= b_rect.y && touch.py <= b_rect.y + b_rect.h;
    }
}