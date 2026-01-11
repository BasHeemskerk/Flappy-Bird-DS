#pragma once

#include "assets.hpp"
#include "constants.hpp"
#include "state.hpp"

#include "../engine/graphics/nf_handler.hpp"

class UI{
    public:
        UI();
        ~UI();

        void init();

        void hidePlayButton();
        void showTitleWithFlag(int flag);

        void getReadyScreen(bool show);
        void gameOverScreen();
        void newHighscoreScreen(bool show);

        void gameScoreScreen(bool show);
        void showGameScoreCounter(bool show, int score);
        void clearGameScoreCounter(bool show);
        void showScoreAndMedalScreen(bool show, int score, int hiscore);

        void reset();
        /*void update(GAME_STATE& state, int score, int highscore);*/
    
    private:
        Assets::little_ui l_ui; //little ui assets
        Assets::score_ui s_ui; //score uit assets
        Assets::number_ui n_ui; //number ui assets
};