#include "ui.hpp"

UI::UI(){
    
}

UI::~UI(){

}

void UI::init(){
    //ui assets loading
    NF_HANDLER::loadSprite(l_ui.SPRITE, l_ui.id, l_ui.w, l_ui.h);
    NF_HANDLER::loadPalette(l_ui.PALETTE, l_ui.id);

    NF_HANDLER::loadSprite(s_ui.SPRITE, s_ui.id, s_ui.w, s_ui.h);
    NF_HANDLER::loadPalette(s_ui.PALETTE, s_ui.id);

    NF_HANDLER::loadSprite(n_ui.SPRITE, n_ui.id, n_ui.w, n_ui.h);
    NF_HANDLER::loadPalette(n_ui.PALETTE, n_ui.id);

    //number UI
    for (int i = 0; i < 9; i++){
        NF_HANDLER::vramSprite(Constants::GAME_SCREEN, n_ui.id, n_ui.offset + i, true);
    }
    //score ui
    for (int i = 0; i < 7; i++){
        NF_HANDLER::vramSprite(Constants::GAME_SCREEN, s_ui.id, s_ui.offset + i, true);
    }
    //medal / little ui
    for (int i = 0; i < 2; i++){
        NF_HANDLER::vramSprite(Constants::GAME_SCREEN, l_ui.id, l_ui.offset + i, true);
    }

    NF_HANDLER::vramPalette(Constants::GAME_SCREEN, n_ui.id, n_ui.id);
    NF_HANDLER::vramPalette(Constants::GAME_SCREEN, s_ui.id, s_ui.id);
    NF_HANDLER::vramPalette(Constants::GAME_SCREEN, l_ui.id, l_ui.id);

    //create score text sprites
    for (int i = 0; i < 3; i++){
        NF_HANDLER::createSprite(Constants::GAME_SCREEN, Constants::ST_O + i, Constants::ST_O + i, n_ui.id, 128 - n_ui.w, 40);
        NF_HANDLER::enableRotScale(Constants::GAME_SCREEN, Constants::ST_O + i, Constants::ST_O + i, true);
        NF_HANDLER::spriteRotScale(Constants::GAME_SCREEN, Constants::ST_O + i, 0, 360, 360);

        if (i != 0){
            NF_HANDLER::showSprite(Constants::GAME_SCREEN, Constants::ST_O + i, false);
        }
    }

    //create screen score text sprites
    for (int i = 0; i < 3; i++){
        NF_HANDLER::createSprite(Constants::GAME_SCREEN, Constants::SST_O_ONE + i, Constants::SST_O_ONE + i, n_ui.id, 162 - i * 8, 78);
        NF_HANDLER::spriteLayer(Constants::GAME_SCREEN, Constants::SST_O_ONE + i, n_ui.layer);
        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, Constants::SST_O_ONE + i, Constants::SST_O_FRAME);
    }
    for (int i = 0; i < 3; i++){
        NF_HANDLER::createSprite(Constants::GAME_SCREEN, Constants::SST_O_TWO + i, Constants::SST_O_TWO + i, n_ui.id, 162 - i * 8, 98);
        NF_HANDLER::spriteLayer(Constants::GAME_SCREEN, Constants::SST_O_TWO + i, n_ui.layer);
        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, Constants::SST_O_TWO + i, Constants::SST_O_FRAME);
    }

    //create title sprites
    NF_HANDLER::createSprite(Constants::GAME_SCREEN, s_ui.offset, s_ui.offset, s_ui.id, 128 - s_ui.w, 20);
    NF_HANDLER::createSprite(Constants::GAME_SCREEN, s_ui.offset + 1, s_ui.offset + 1, s_ui.id, 128, 20);
    for (int i = 0; i < 2; i++){
        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, s_ui.offset + i, 6 + i);
        NF_HANDLER::spriteLayer(Constants::GAME_SCREEN, s_ui.offset + i, 1);
    }

    //create tap image sprite
    NF_HANDLER::createSprite(Constants::GAME_SCREEN, s_ui.offset + 2, s_ui.offset + 2, s_ui.id, 128 - s_ui.w / 2, 60);
    NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, s_ui.offset + 2, 8);
    NF_HANDLER::spriteLayer(Constants::GAME_SCREEN, s_ui.offset + 2, 1);
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, s_ui.offset + 2, false);

    //create score screen sprites
    NF_HANDLER::createSprite(Constants::GAME_SCREEN, s_ui.offset + 3, s_ui.offset + 3, s_ui.id, 128 - s_ui.w, 60);
    NF_HANDLER::createSprite(Constants::GAME_SCREEN, s_ui.offset + 4, s_ui.offset + 4, s_ui.id, 128, 60);
    NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, s_ui.offset + 4, 1);
    NF_HANDLER::spriteLayer(Constants::GAME_SCREEN, s_ui.offset + 3, 1);
    NF_HANDLER::spriteLayer(Constants::GAME_SCREEN, s_ui.offset + 4, 1);

    //create play button sprites
    NF_HANDLER::createSprite(Constants::GAME_SCREEN, s_ui.offset + 5, s_ui.offset + 5, s_ui.id, 128 - s_ui.w / 2, 92);
    NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, s_ui.offset + 5, 9);

    //create cr button sprite
    NF_HANDLER::createSprite(Constants::GAME_SCREEN, s_ui.offset + 6, s_ui.offset + 6, s_ui.id, 128 - s_ui.w / 2, 144);
    NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, s_ui.offset + 6, 10);
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, s_ui.offset + 6, false);

    //create medal sprite
    NF_HANDLER::createSprite(Constants::GAME_SCREEN, l_ui.offset, l_ui.offset, l_ui.id, 80, 80);
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, l_ui.offset, false);

    //create new high score sprite
    NF_HANDLER::createSprite(Constants::GAME_SCREEN, l_ui.offset + 1, l_ui.offset + 1, l_ui.id, 128, 81);
    NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, l_ui.offset + 1, 4);
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, l_ui.offset + 1, false);


    gameScoreScreen(false);
    showGameScoreCounter(false, 0);
}

void UI::hidePlayButton(){
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, s_ui.offset + 5, false);
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, s_ui.offset + 6, false);
}

void UI::showTitleWithFlag(int flag){
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, s_ui.offset, flag != -1);
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, s_ui.offset + 1, flag != -1);
}

void UI::getReadyScreen(bool show){
    NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, s_ui.offset, 2);
    NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, s_ui.offset + 1, 3);
    NF_HANDLER::moveSprite(Constants::GAME_SCREEN, s_ui.offset, 128 - s_ui.w, -6);
    NF_HANDLER::moveSprite(Constants::GAME_SCREEN, s_ui.offset + 1, 128, -6);
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, s_ui.offset + 2, show);
}

void UI::gameOverScreen(){
    NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, s_ui.offset, 4);
    NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, s_ui.offset + 1, 5);
    NF_HANDLER::moveSprite(Constants::GAME_SCREEN, s_ui.offset, 128 - s_ui.w, 14);
    NF_HANDLER::moveSprite(Constants::GAME_SCREEN, s_ui.offset + 1, 128, 14);
}

void UI::newHighscoreScreen(bool show){
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, l_ui.offset + 1, show);
}

void UI::gameScoreScreen(bool show){
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, s_ui.offset + 3, show);
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, s_ui.offset + 4, show);
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, l_ui.offset, false);

    if (!show){
        NF_HANDLER::showSprite(Constants::GAME_SCREEN, l_ui.offset + 1, false);
    }

    for (int i = 0; i < 2; i++){
        NF_HANDLER::showSprite(Constants::GAME_SCREEN, (s_ui.id + 1) + i * 3, show);
        NF_HANDLER::showSprite(Constants::GAME_SCREEN, (s_ui.id + 2) + i * 3, false);
        NF_HANDLER::showSprite(Constants::GAME_SCREEN, (s_ui.id + 3) + i * 3, false);
    }
}

void UI::showGameScoreCounter(bool show, int score){
    if (score < 10){
        NF_HANDLER::showSprite(Constants::GAME_SCREEN, n_ui.id -1, show);
        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, n_ui.id - 1, score);
    }
    else if (score < 100){
        NF_HANDLER::showSprite(Constants::GAME_SCREEN, n_ui.id, show);
        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, n_ui.id - 1, score / 10);
        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, n_ui.id, score % 10);
        NF_HANDLER::moveSprite(Constants::GAME_SCREEN, n_ui.id - 1, 128 - n_ui.w - 11, 40);
        NF_HANDLER::moveSprite(Constants::GAME_SCREEN, n_ui.id, 128 - n_ui.w + 11, 40);
    }
    else if (score < 1000){
        NF_HANDLER::showSprite(Constants::GAME_SCREEN, n_ui.id, show);
        NF_HANDLER::showSprite(Constants::GAME_SCREEN, n_ui.id + 1, show);
        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, n_ui.id - 1, score / 100);
        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, n_ui.id, score % 100 / 10);
        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, n_ui.id + 1, score % 10);
        NF_HANDLER::moveSprite(Constants::GAME_SCREEN, n_ui.id - 1, 128 - n_ui.w - 22, 40);
        NF_HANDLER::moveSprite(Constants::GAME_SCREEN, n_ui.id, 128 - n_ui.w, 40);
        NF_HANDLER::moveSprite(Constants::GAME_SCREEN, n_ui.id + 1, 128 - n_ui.w + 22, 40);
    }
}

void UI::clearGameScoreCounter(bool show){
    NF_HANDLER::moveSprite(Constants::GAME_SCREEN, n_ui.id - 1, 128 - n_ui.w, 40);
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, n_ui.id - 1, show);
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, n_ui.id, false);
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, n_ui.id + 1, false);
}

void UI::showScoreAndMedalScreen(bool show, int score, int hiscore){

    for (int i = 0; i < 2; i++){
        int scoreToShow = 0;

        if (i == 0){
            scoreToShow = score;
        } else {
            scoreToShow = hiscore;
        }

        if (scoreToShow < 10){
            NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, l_ui.id + i * 3, 10 + scoreToShow);
        }
        else if (scoreToShow < 100){
            NF_HANDLER::showSprite(Constants::GAME_SCREEN, l_ui.id + 1 + i * 3, true);

            NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, l_ui.id + i * 3, 10 + scoreToShow % 10);
            NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, l_ui.id + 1 + i * 3, 10 + scoreToShow / 10);
        }
        else if (scoreToShow < 1000){
            NF_HANDLER::showSprite(Constants::GAME_SCREEN, l_ui.id + 1 + i * 3, true);
            NF_HANDLER::showSprite(Constants::GAME_SCREEN, l_ui.id + 2 + i * 3, true);

            NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, l_ui.id + i * 3, 10 + scoreToShow % 10);
            NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, l_ui.id + 1 + i * 3, 10 + scoreToShow % 100 / 10);
            NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, l_ui.id + 2 + i * 3, 10 + scoreToShow / 100);
        }
    }

    //medal
    NF_HANDLER::showSprite(Constants::GAME_SCREEN, l_ui.offset, true);
    if (score >= 40){
        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, l_ui.offset, 3);
    }
    else if (score >= 30){
        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, l_ui.offset, 2);
    }
    else if (score >= 20){
        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, l_ui.offset, 1);
    }
    else if (score >= 10){
        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, l_ui.offset, 0);
    }
    else{
        NF_HANDLER::showSprite(Constants::GAME_SCREEN, l_ui.offset, false);
    }
}


/*void UI::update(GAME_STATE& state, int score, int highscore){
    switch(state){
        case MENU:
            gameScoreCounter(false);
            showGameScoreCounter(false, score);
            break;
        case DEAD:
            break;
        case PLAYING:
            showGameScoreCounter(true, score);
            showTitleWithFlag(-1);
            getReadyScreen(false);
            break;
        case GET_READY:
            showTitleWithFlag(0);
            getReadyScreen(true);
            hidePlayButton();
            break;
        default:
            break;
    }
}*/


void UI::reset(){
    /*showTitleWithFlag(0);

    scoreScreen(false);
    clearScore(false);
    newHighscore(false);
    showScoreScoreScreen(false, 0, 0);

    getReady(true);

    showTitleWithFlag(-1);*/
}