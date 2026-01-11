#pragma once 

#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

namespace SFX_HANDLER{

    struct Clip{
        int id;
        bool loaded;

        Clip(int sound_id) : id(sound_id), loaded(false) {}

        void load_clip(){
            if (!loaded){
                mmLoadEffect(id);
                loaded = true;
            }
        }

        void play_clip(){
            if (loaded){
                mmEffect(id);
            }
        }

        void delete_clip(){
            if (loaded){
                mmUnloadEffect(id);
                loaded = false;
            }
        }
    };

    void init();
}