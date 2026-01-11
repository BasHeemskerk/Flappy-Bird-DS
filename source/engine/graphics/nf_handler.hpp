#pragma once

//Always include this
#include <nds.h>

//graphic library nightfox lib
#include <nf_lib.h>

//math function
#include <math.h>

namespace NF_HANDLER{
    //initialization functions
    extern void init_nf_handler(const char* name, int screen_one, int screen_two);
    extern void initBackgrounds(int screen_one, int screen_two);
    extern void initSprites(int screen);

    //background functions
    extern void loadBackground(const char* path, const char* name, int w, int h);
    extern void createBackground(int screen, int layer, const char* name);
    extern void deleteBackground(int screen, int layer);
    extern void scrollBackground(int screen, int layer, int x, int y);

    //sprite creation and loading etc
    extern void createSprite(int screen, int id, int gfx, int pal, int x, int y);
    extern void loadSprite(const char* path, int id, int w, int h);
    extern void vramSprite(int screen, int id, int slot, bool keep_f);

    extern void spriteLayer(int screen, int id, int layer);
    extern void spriteFrame(int screen, int id, int frame);
    extern void spriteRotScale(int screen, int id, int rot, int scale_x, int scale_y);

    extern void moveSprite(int screen, int id, int x, int y);
    extern void enableRotScale(int screen, int sprite_id, int rotscale_id, bool double_s);
    extern void showSprite(int screen, int id, bool show);

    extern void loadPalette(const char* path, int id);
    extern void vramPalette(int screen, int id, int slot);

    //screen clearing functions
    extern void setSpriteOam(int screen);
    extern void updateOAM();
    extern void waitVBlank();
}