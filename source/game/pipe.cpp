#include "pipe.hpp"

Pipe::Pipe(){

}

Pipe::~Pipe(){ 

}

void Pipe::init(int id, int start_x){
    static bool pipesLoaded = false;
    if (!pipesLoaded) {
        NF_HANDLER::loadSprite(gfx_p.SPRITE, gfx_p.id, gfx_p.w, gfx_p.h);
        NF_HANDLER::loadPalette(gfx_p.PALETTE, gfx_p.id);

        NF_HANDLER::vramPalette(Constants::GAME_SCREEN, gfx_p.id, gfx_p.id);

        for (int i = 0; i < Constants::PIPE_COUNT * 2; i++) {
            NF_HANDLER::vramSprite(Constants::GAME_SCREEN, gfx_p.id, gfx_p.offset + i, true);
        }

        pipesLoaded = true;
    }

    pipe_id = id;

    sprite_id_btm = gfx_p.offset + (id * 2);
    sprite_id_top = gfx_p.offset + (id * 2 ) + 1;

    x_pos = start_x;

    gap_y = randomGapY();

    scored = false;

    NF_HANDLER::createSprite(Constants::GAME_SCREEN, sprite_id_top, sprite_id_top, gfx_p.id, x_pos, 0);
    NF_HANDLER::createSprite(Constants::GAME_SCREEN, sprite_id_btm, sprite_id_btm, gfx_p.id, x_pos, 0);

    NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, sprite_id_top, 3);

    NF_HANDLER::spriteLayer(Constants::GAME_SCREEN, sprite_id_top, gfx_p.layer + 3);
    NF_HANDLER::spriteLayer(Constants::GAME_SCREEN, sprite_id_btm, gfx_p.layer + 3);

    updatePosition();

    active = true;
}

int Pipe::randomGapY(){
    return 86 + rand() % 34;
}

void Pipe::updatePosition(){
    int top_y = gap_y - 120;
    int btm_y = gap_y;

    NF_HANDLER::moveSprite(Constants::GAME_SCREEN, sprite_id_top, x_pos, top_y);
    NF_HANDLER::moveSprite(Constants::GAME_SCREEN, sprite_id_btm, x_pos, btm_y);
}

void Pipe::update(){
    if (!active){
        return; 
    }
    
    x_pos--;

    if (x_pos < -PIPE_WIDTH) {
        respawn();
    }

    updatePosition();
}

void Pipe::respawn(){
    x_pos += (PIPE_WIDTH + 68) * Constants::PIPE_COUNT;
    gap_y = randomGapY();
    scored = false;
}

bool Pipe::checkCollision(int bird_x, int bird_y, int bird_w, int bird_h){
    if (!active){
        return false;
    }

    if (x_pos - 11 <= bird_x && x_pos + 26 >= bird_x){
        if (gap_y <= bird_y + 16 || gap_y >= bird_y + 57){
            return true;
        }
    }
    return false;
}

bool Pipe::checkScore(int bird_x){
    if (scored){
        return false;
    }

    if (bird_x > x_pos + PIPE_WIDTH){
        scored = true;
        return true;
    }

    return false;
}

void Pipe::reset(int id, int pos){
    int newPos = pos + (id * 100);
    init(id, newPos);
}