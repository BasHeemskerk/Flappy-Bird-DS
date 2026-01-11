#include "sfx_handler.hpp"

namespace SFX_HANDLER{
    void init(){
        mmInitDefaultMem((mm_addr)soundbank_bin);
    }
}