#pragma once

namespace Assets{

    //background assets
    struct scrolling_bg{
        static constexpr const char* BG = "backgrounds/ScrollingBg";
        static constexpr const char* BG_NAME = "ScrollingBg";
        static constexpr int width = 256;
        static constexpr int height = 256;
        static constexpr int layer = 2;
    };
    struct city_bg{
        static constexpr const char* BG = "backgrounds/Bg1";
        static constexpr const char* BG_NAME = "DayBg";
        static constexpr int width = 256;
        static constexpr int height = 256;
        static constexpr int layer = 3;
    };
    struct night_bg{
        static constexpr const char* BG = "backgrounds/Bg2";
        static constexpr const char* BG_NAME = "NightBG";
        static constexpr int width = 256;
        static constexpr int height = 256;
        static constexpr int layer = 3;
    };

    //ui assets
    struct little_ui{
        static constexpr const char* SPRITE = "sprites/LittleUI";
        static constexpr const char* PALETTE = "palettes/LittleUI";
        static constexpr int id = 4;
        static constexpr int offset = 17;
        static constexpr int w = 32;
        static constexpr int h = 32;
        static constexpr int layer = 0;
    };
    struct score_ui{
        static constexpr const char* SPRITE = "sprites/ScoreScreenUI";
        static constexpr const char* PALETTE = "palettes/ScoreScreenUI";
        static constexpr int id = 3;
        static constexpr int offset = 10;
        static constexpr int w = 64;
        static constexpr int h = 64;
        static constexpr int layer = 1;
    };
    struct number_ui{
        static constexpr const char* SPRITE = "sprites/NumberUI";
        static constexpr const char* PALETTE = "palettes/NumberUI";
        static constexpr int id = 2;
        static constexpr int offset = 1;
        static constexpr int w = 16;
        static constexpr int h = 16;
        static constexpr int layer = 0;
    };

    //game assets
    struct gfx_pipes{
        static constexpr const char* SPRITE = "sprites/Pipes";
        static constexpr const char* PALETTE = "palettes/Pipes";
        static constexpr int id = 1;
        static constexpr int offset = 26;
        static constexpr int w = 32;
        static constexpr int h = 64;
        static constexpr int layer = 0;
    };
    struct gfx_bird{
        static constexpr const char* SPRITE = "sprites/Birds";
        static constexpr const char* PALETTE = "palettes/Birds";
        static constexpr int id = 0;
        static constexpr int offset = 0;
        static constexpr int w = 16;
        static constexpr int h = 16;
        static constexpr int layer = 0;
    };
}