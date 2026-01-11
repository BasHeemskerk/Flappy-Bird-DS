#include "io_handler.hpp"

namespace IO_HANDLER{
    
    void init(){

    }

    int loadHighscore(const char* path){
        SaveData data = {0};

        FILE* file = fopen(path, "rb");
        if (file){
            fread(&data, sizeof(SaveData), 1, file);
            fclose(file);
        }

        return data.highScore;
    }

    void saveHighscore(const char* path, int score){
        SaveData data = {score};

        FILE* file = fopen(path, "wb");
        if (file){
            fwrite(&data, sizeof(SaveData), 1, file);
            fclose(file);
        }
    }

    bool loadSaveData(const char* path, SaveData& data){
        FILE* file = fopen(path, "rb");
        if (!file){
            data = {0};
            return false;
        }

        fread(&data, sizeof(SaveData), 1, file);
        fclose(file);
        return true;
    }
    void saveSaveData(const char* path, const SaveData& data){
        FILE* file = fopen(path, "wb");
        if (file){
            fwrite(&data, sizeof(SaveData), 1, file);
            fclose(file);
        }
    }
}