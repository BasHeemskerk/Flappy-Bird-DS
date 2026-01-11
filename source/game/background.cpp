#include "background.hpp"

BG::BG()
    : x_pos(DEFAULT_SCROLL_BACKGROUND_X_POS)
    , y_pos(DEFAULT_SCROLL_BACKGROUND_Y_POS)
{

}

BG::~BG(){

}

void BG::init(){
    //backgrounds loading
    NF_HANDLER::loadBackground(sb.BG, sb.BG_NAME, sb.width, sb.height);
    NF_HANDLER::createBackground(Constants::GAME_SCREEN, sb.layer, sb.BG_NAME);
    NF_HANDLER::scrollBackground(Constants::GAME_SCREEN, sb.layer, x_pos, y_pos);
    
    NF_HANDLER::loadBackground(cb.BG, cb.BG_NAME, cb.width, cb.height);
    NF_HANDLER::createBackground(Constants::GAME_SCREEN, cb.layer, cb.BG_NAME);

    NF_HANDLER::loadBackground(nb.BG, nb.BG_NAME, nb.width, nb.height);

    randomBackground(false); //we just have to initialize
}

void BG::randomBackground(bool do_random){
    if (do_random){
        if (rand() % 400 < 300){
            NF_HANDLER::deleteBackground(Constants::GAME_SCREEN, cb.layer);
            NF_HANDLER::createBackground(Constants::GAME_SCREEN, cb.layer, cb.BG_NAME);
            NF_HANDLER::scrollBackground(Constants::GAME_SCREEN, cb.layer, 0, DEFAULT_NORMAL_BACKGROUND_Y_POS);
        } else {
            NF_HANDLER::deleteBackground(Constants::GAME_SCREEN, nb.layer);
            NF_HANDLER::createBackground(Constants::GAME_SCREEN, nb.layer, nb.BG_NAME);
            NF_HANDLER::scrollBackground(Constants::GAME_SCREEN, nb.layer, 0, DEFAULT_NORMAL_BACKGROUND_Y_POS);
        }
    }
    else {
        NF_HANDLER::scrollBackground(Constants::GAME_SCREEN, cb.layer, 0, DEFAULT_NORMAL_BACKGROUND_Y_POS);
    }
}

void BG::scrollBackground(){
    x_pos++;

    if (x_pos >= 255){
        x_pos = 0;
    }

    NF_HANDLER::scrollBackground(Constants::GAME_SCREEN, sb.layer, x_pos, y_pos);
}