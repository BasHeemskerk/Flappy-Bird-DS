#pragma once

//nds library
#include <nds.h>

//math function
#include <math.h>

//for the random system
#include <time.h>

//other scripts
#include "state.hpp" //for our game state reference
#include "assets.hpp"
#include "constants.hpp"

#include "bird.hpp"
#include "pipe.hpp"
#include "ui.hpp"
#include "background.hpp"

#include "../nds/input.hpp"

#include "../engine/io/io_handler.hpp" //file handler
#include "../engine/audio/sfx_handler.hpp" //audio handler
#include "../engine/graphics/nf_handler.hpp" //graphics handler (talks to NF lib)

class FB_GAME{
    public:
        FB_GAME();
        ~FB_GAME();

        void gameLoop();
    
    private:
        int hiScore;
        int gScore;

        void init();
        void load_assets();
        void load_sprites();
        void load_audio();

        void scroll_background();

        void input();
        void update();
        void draw();

        void onGameStateChanged(GAME_STATE from, GAME_STATE to);
        void updateScoreUi(int score);
        void resetGame();
        

        SFX_HANDLER::Clip sfx_die{SFX_DIE};
        SFX_HANDLER::Clip sfx_hit{SFX_HIT};
        SFX_HANDLER::Clip sfx_point{SFX_POINT};
        SFX_HANDLER::Clip sfx_woosh{SFX_SWOOSH};
        SFX_HANDLER::Clip sfx_wing{SFX_WING};

        Bird bird;
        Pipe pipes[3];
        UI ui;
        BG bg;
        

        int sprite_pal_incr = 0;
        int backgroundXPos = 0;
        
};