#pragma once

namespace Constants{

    //game screen info
    static constexpr int GAME_SCREEN = 1;
    static constexpr int DEBUG_SCREEN = 0;

    static constexpr int PIPE_COUNT = 3;

    //jump force for bird
    static constexpr float JUMP_FORCE = 3.1f;

    //screen width
    static constexpr int SCREEN_X_SIZE = 256;

    //score text frame
    static constexpr int SST_O_FRAME = 10;

    //Score text offset
    static constexpr int ST_O = 1; //Score Text Offset

    //Screen score text offset
    static constexpr int SST_O_ONE = 4; //Screen Score Text Offset
    static constexpr int SST_O_TWO = 7; //Screen Score Text Offset

    //pi
    static constexpr float PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;

    //save data location
    constexpr const char* SAVE_PATH = "fat:/FlappyBirdDS.sav";

    struct Rect
    {
        int x;
        int y;
        int w; 
        int h;
    };
    
    constexpr Rect playButton = {
        128 - 32 + 8,   // x = 104
        92 + 16,        // y = 108
        48,             // w
        32
    };
}