#include "nf_handler.hpp"

namespace NF_HANDLER{
    void init_nf_handler(const char* name, int screen_one, int screen_two){
        //set the nightfox game assets folder
        NF_SetRootFolder(name);

        //init our gamescreens
        NF_Set2D(screen_one, 0);
        NF_Set2D(screen_two, 0);
    }

    void initBackgrounds(int screen_one, int screen_two){
        //init our backgrounds
        NF_InitTiledBgBuffers();
        NF_InitTiledBgSys(screen_one);
        NF_InitTiledBgSys(screen_two);   
    }

    void initSprites(int screen){
        //init our sprite system
        NF_InitSpriteBuffers();
        NF_InitSpriteSys(screen);
    }

    //background functions
    void loadBackground(const char* path, const char* name, int w, int h){
        NF_LoadTiledBg(path, name, w, h);
    }
    void createBackground(int screen, int layer, const char* name){
        NF_CreateTiledBg(screen, layer, name);
    }
    void deleteBackground(int screen, int layer){
        NF_DeleteTiledBg(screen, layer);
    }
    void scrollBackground(int screen, int layer, int x, int y){
        NF_ScrollBg(screen, layer, x, y);
    }


    //sprite creation and loading
    void createSprite(int screen, int id, int gfx, int pal, int x, int y){
        NF_CreateSprite(screen, id, gfx, pal, x, y);
    }
    void loadSprite(const char* path, int id, int w, int h){
        NF_LoadSpriteGfx(path, id, w, h);
    }
    void vramSprite(int screen, int id, int slot, bool keep_f){
        NF_VramSpriteGfx(screen, id, slot, keep_f);
    }

    void spriteLayer(int screen, int id, int layer){
        NF_SpriteLayer(screen, id, layer);
    }
    void spriteFrame(int screen, int id, int frame){
        NF_SpriteFrame(screen, id, frame);
    }
    void spriteRotScale(int screen, int id, int rot, int scale_x, int scale_y){
        NF_SpriteRotScale(screen, id, rot, scale_x, scale_y);
    }

    void moveSprite(int screen, int id, int x, int y){
        NF_MoveSprite(screen, id, x, y);
    }
    void enableRotScale(int screen, int sprite_id, int rotscale_id, bool double_s){
        NF_EnableSpriteRotScale(screen, sprite_id, rotscale_id, double_s);
    }
    void showSprite(int screen, int id, bool show){
        NF_ShowSprite(screen, id, show);
    }

    void loadPalette(const char* path, int id){
        NF_LoadSpritePal(path, id);
    }
    void vramPalette(int screen, int id, int slot){
        NF_VramSpritePal(screen, id, slot);
    }

    //screen clearing functions
    void setSpriteOam(int screen){
        NF_SpriteOamSet(screen);
    }
    void updateOAM(){
        oamUpdate(&oamSub);
    }
    void waitVBlank(){
        swiWaitForVBlank();
    }
}