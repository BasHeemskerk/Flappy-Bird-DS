#include "flappybird.hpp"

//as soon as our object gets initialized in our main file this runs
FB_GAME::FB_GAME(){
    init();
}

FB_GAME::~FB_GAME(){

}

void FB_GAME::init(){
    //init our random system to always start at a random value
    srand(time(0));

    //initialize our nitrofox handler
    NF_HANDLER::init_nf_handler("NITROFS", Constants::GAME_SCREEN, Constants::DEBUG_SCREEN);
    NF_HANDLER::initBackgrounds(Constants::GAME_SCREEN, Constants::DEBUG_SCREEN);
    NF_HANDLER::initSprites(Constants::GAME_SCREEN);

    //initialize our audio clip handler
    SFX_HANDLER::init();
    load_audio();

    hiScore = IO_HANDLER::loadHighscore(Constants::SAVE_PATH);

    //init objects
    bg.init();

    bird.init();

    pipes[0].init(0, 256);
    pipes[1].init(1, 256 + 100);
    pipes[2].init(2, 256 + 200);

    ui.init();
}

void FB_GAME::load_audio(){
    sfx_die.load_clip();
    sfx_hit.load_clip();
    sfx_point.load_clip();
    sfx_woosh.load_clip();
    sfx_wing.load_clip();
}

void FB_GAME::scroll_background(){
    backgroundXPos++;

    if (backgroundXPos >= 255){
        backgroundXPos = 0;
    }
}

void FB_GAME::onGameStateChanged(GAME_STATE from, GAME_STATE to){
    if (to == GET_READY){
        ui.hidePlayButton();
        ui.showTitleWithFlag(0);
        ui.getReadyScreen(true);
        ui.showGameScoreCounter(false, gScore);
        ui.clearGameScoreCounter(false);
        ui.showScoreAndMedalScreen(false, gScore, hiScore);
        ui.gameScoreScreen(false);
        ui.newHighscoreScreen(false);
        sfx_woosh.play_clip();
    }
    else if (to == PLAYING){
        ui.showTitleWithFlag(-1);
        ui.getReadyScreen(false);
        ui.clearGameScoreCounter(true);
        ui.showGameScoreCounter(true, gScore);
        sfx_wing.play_clip();
    }
    else if (to == DEAD){
        ui.clearGameScoreCounter(false);
        ui.gameOverScreen();
        ui.showTitleWithFlag(1);
        ui.gameScoreScreen(true);

        if (gScore > hiScore){
            ui.newHighscoreScreen(true);
            IO_HANDLER::saveHighscore(Constants::SAVE_PATH, gScore);
            hiScore = gScore;

        } 
        
        ui.showScoreAndMedalScreen(true, gScore, hiScore);
    }
    else if (to == MENU){

    }
}

void FB_GAME::updateScoreUi(int score){
    ui.showGameScoreCounter(true, gScore);
}

void FB_GAME::resetGame(){
    gScore = 0;
    bird.reset();
    for (int i = 0; i < 3; i++){
        pipes[i].reset(i, 256);
    }
    bird.randomizeColor();
    bg.randomBackground(true);
}

void FB_GAME::gameLoop(){
    GAME_STATE gs = MENU;
    GAME_STATE prevState = MENU;
 
    while (true){

        DS_INPUT::scan();
        int keyDown = DS_INPUT::getKeysDown();
        int keyHeld = DS_INPUT::getKeysHeld();
        touchPosition touchPos; 
        DS_INPUT::getTouch(touchPos);

        if (gs != prevState){
            onGameStateChanged(prevState, gs);
            prevState = gs;
        }

        switch(gs){
            case MENU:
                bird.animate();
                bg.scrollBackground();

                bird.idleBob();

                if (DS_INPUT::touchInBounds(touchPos, Constants::playButton) || DS_INPUT::anyKeyPressed(keyDown)){

                    //sfx_woosh.play_clip();

                    gs = GET_READY;
                }

                break;
            case DEAD:

                if (DS_INPUT::anyKeyPressed(keyDown) || DS_INPUT::touchDown(keyDown)){
                    resetGame();
                    gs = GET_READY;
                }

                bird.interpolateXPos();
                bird.checkTopAndBottomCollision();
                bird.update(true);

                break;
            case GET_READY:
                bird.animate();
                bg.scrollBackground();

                bird.idleBob();
                bird.interpolateXPos();
                
                if (DS_INPUT::anyKeyPressed(keyDown) || DS_INPUT::touchDown(keyDown)){
                    bird.jump(Constants::JUMP_FORCE);
                    gs = PLAYING;
                }
                
                break;
            case PLAYING:
                bird.animate();
                bg.scrollBackground();

                bird.interpolateXPos();

                for (int i = 0; i < 3; i++){
                    pipes[i].update();

                    if (pipes[i].checkCollision(bird.x_pos, bird.y_pos, 16, 16)){
                        sfx_hit.play_clip();
                        sfx_die.play_clip();

                        gs = DEAD;
                    }

                    if (pipes[i].checkScore(bird.x_pos)){
                        gScore++;
                        updateScoreUi(gScore);
                        sfx_point.play_clip();
                    }
                }

                if (bird.checkTopAndBottomCollision()){
                    sfx_hit.play_clip();
                    sfx_die.play_clip();
                    
                    gs = DEAD;
                }

                if ((DS_INPUT::anyKeyPressed(keyDown) || DS_INPUT::touchDown(keyDown)) && gs != DEAD){
                    bird.jump(Constants::JUMP_FORCE);
                    sfx_wing.play_clip();
                }

                bird.update(true);

                break;
            default:
                break;
        }

        NF_HANDLER::setSpriteOam(Constants::GAME_SCREEN);
        NF_HANDLER::updateOAM();
        NF_HANDLER::waitVBlank();
    } 
}