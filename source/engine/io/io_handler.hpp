#pragma once

#include <cstdio>

namespace IO_HANDLER{
    struct SaveData {
        int highScore;
    };

    extern void init();

    extern int loadHighscore(const char* path);

    extern void saveHighscore(const char* path, int score);

    extern bool loadSaveData(const char* path, SaveData& data);
    extern void saveSaveData(const char* path, const SaveData& data);
}