#pragma once

#include <math.h>

#include "../game/assets.hpp"
#include "../game/constants.hpp"

#include "../engine/graphics/nf_handler.hpp"

#include "pipe.hpp"
#include "constants.hpp"

class Bird{
    public:
        Bird();
        ~Bird();

        void init();

        float x_pos;
        float y_pos;
        float y_speed;
        float bird_speed;
        float rot;
        int model;

        void jump(float force);
        void update(bool do_gravity);
        bool checkTopAndBottomCollision();

        void animate();
        void idleBob();
        void randomizeColor();
        void interpolateXPos();

        void reset();
    
    private:
        Assets::gfx_bird gfx_b;

        int screen;
        int sprite_id;

        void draw();

        void gravity();

        bool checkCollision(Pipe pipe);

        int birdAnimationTimer;
        int currentBirdAnimation;
        bool reverseAnimation;

        float birdYOffset;

        static constexpr float GRAVITY = 0.14f;
        static constexpr float JUMP_FORCE = -3.1f;
        static constexpr float MAX_FALL_SPEED = 4.0f;
        static constexpr int GROUND_Y = 138;
        static constexpr int CEILING_Y = -8;

        static constexpr int DEFAULT_BIRD_X_POS = Constants::SCREEN_X_SIZE / 2 - 8;
        static constexpr int DEFAULT_BIRD_Y_POS = 80;
        static constexpr int DEFAULT_BIRD_Y_SPEED = 0;
        static constexpr int DEFAULT_BIRD_SPEED = 0;
        static constexpr int DEFAULT_BIRD_ROT = 0;
        static constexpr int DEFAULT_BIRD_MODEL = 0;

        static constexpr int BIRD_ANIMATION_TIMER_COUNT = 10;
        static constexpr int BIRD_ANIMATION_COUNT = 3;

};