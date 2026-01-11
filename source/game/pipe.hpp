#pragma once

#include "constants.hpp"
#include "assets.hpp"

#include "../engine/graphics/nf_handler.hpp"

class Pipe{
    public:
        Pipe();
        ~Pipe();

        void init(int id, int start_x);
        void update();
        void respawn();
        void updatePosition();

        int randomGapY();
        
        bool checkCollision(int bird_x, int bird_y, int bird_w, int bird_h);
        bool checkScore(int bird_x);

        void reset(int id, int pos);


    private:
        Assets::gfx_pipes gfx_p; //pipes assets

        int pipe_id;

        int x_pos;
        float gap_y;
        int sprite_id_top;
        int sprite_id_btm;
        bool scored;
        bool active;

        void draw();

        void isOffscreen();
        bool passedBird(int bird_X);

        static constexpr int GAP_SIZE = 92;
        static constexpr int PIPE_WIDTH = 32;
        static constexpr int PIPE_HEIGHT = 64;
        static constexpr int SCROLL_SPEED = 2;

        static constexpr int MIN_GAP_Y = PIPE_HEIGHT + 10;   // 74
        static constexpr int MAX_GAP_Y = 192 - PIPE_HEIGHT - GAP_SIZE - 10; // 32? (too small)

};