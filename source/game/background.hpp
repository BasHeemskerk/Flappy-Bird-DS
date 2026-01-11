#pragma once

#include "assets.hpp"
#include "constants.hpp"

#include "../engine/graphics/nf_handler.hpp"

class BG{
    public:
        BG();
        ~BG();

        void init();
        void randomBackground(bool do_random);
        void scrollBackground();

    private:
        Assets::scrolling_bg sb; //scrolling background asset
        Assets::city_bg cb; //city background asset
        Assets::night_bg nb;

        int x_pos;
        int y_pos;

        static constexpr int DEFAULT_SCROLL_BACKGROUND_Y_POS = -150;
        static constexpr int DEFAULT_SCROLL_BACKGROUND_X_POS = 0;
        static constexpr int DEFAULT_NORMAL_BACKGROUND_Y_POS = 70;
};