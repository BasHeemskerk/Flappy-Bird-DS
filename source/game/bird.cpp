#include "bird.hpp"

Bird::Bird() 
    : x_pos(DEFAULT_BIRD_X_POS)
    , y_pos(DEFAULT_BIRD_Y_POS)
    , y_speed(DEFAULT_BIRD_Y_SPEED)
    , rot(DEFAULT_BIRD_ROT)
    , model(DEFAULT_BIRD_MODEL)
    , birdAnimationTimer(0)
    , currentBirdAnimation(2)
    , reverseAnimation(false)
    , birdYOffset(0.0f) 
{
    

}

Bird::~Bird(){

}

void Bird::init(){
    NF_HANDLER::loadSprite(gfx_b.SPRITE, gfx_b.id, gfx_b.w, gfx_b.h);
    NF_HANDLER::loadPalette(gfx_b.PALETTE, gfx_b.id);

    NF_HANDLER::vramPalette(Constants::GAME_SCREEN, gfx_b.id, gfx_b.id);

    //bird gfx and pal
    NF_HANDLER::vramSprite(Constants::GAME_SCREEN, gfx_b.id, gfx_b.offset, true);

    //create our bird sprite
    NF_HANDLER::createSprite(Constants::GAME_SCREEN, gfx_b.id, gfx_b.offset, gfx_b.id, x_pos, y_pos);
    NF_HANDLER::enableRotScale(Constants::GAME_SCREEN, gfx_b.id, gfx_b.offset, false);
    NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, gfx_b.id, 2 + model * 3);
}

void Bird::idleBob(){
    birdYOffset += 0.1f;
    if (birdYOffset >= 2.0f * Constants::PI){
        birdYOffset -= 2.0f * Constants::PI;
    }

    NF_HANDLER::moveSprite(Constants::GAME_SCREEN, gfx_b.id, x_pos, y_pos + sinf(birdYOffset) * 5);
}

void Bird::animate(){
    birdAnimationTimer++;
    if (birdAnimationTimer >= BIRD_ANIMATION_TIMER_COUNT){
        birdAnimationTimer = 0;

        if (reverseAnimation){
            currentBirdAnimation++; 
        } else {
            currentBirdAnimation--;
        }

        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, gfx_b.id, currentBirdAnimation + model * 3);

        if ((currentBirdAnimation >= BIRD_ANIMATION_COUNT - 1) || (currentBirdAnimation <= 0)){
            reverseAnimation = !reverseAnimation;
        }
    }
}

bool Bird::checkTopAndBottomCollision(){
    if (y_pos > 138){
        y_pos = 138;
        return true;
    }
    else if (y_pos <= -8){
        return true;
    }
    else{
        return false;
    }
}

void Bird::jump(float force){
    y_speed = -force;
}

void Bird::gravity(){
    if (y_speed < 4){
        y_speed += 0.14f;
    }
}

void Bird::interpolateXPos(){
    if (x_pos > DEFAULT_BIRD_X_POS / 2){
        x_pos--;
    }
}

void Bird::update(bool do_gravity){
    y_pos += y_speed;
    if (do_gravity){
        gravity();
    }
    draw();
}

void Bird::draw(){
    NF_HANDLER::moveSprite(Constants::GAME_SCREEN, gfx_b.id, x_pos, y_pos);
    rot = y_speed * 31.5f;
    NF_HANDLER::spriteRotScale(Constants::GAME_SCREEN, gfx_b.id, rot, 256, 256);
}

void Bird::reset(){
    y_pos = DEFAULT_BIRD_Y_POS;
    //x_pos = DEFAULT_BIRD_X_POS;
    y_speed = DEFAULT_BIRD_Y_SPEED;
    rot = DEFAULT_BIRD_ROT;
    model = rand() % 3;
    birdYOffset = 0;
}

void Bird::randomizeColor(){
    model = rand() % 3;
}