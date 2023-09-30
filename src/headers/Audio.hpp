#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

class Audio {
    public:
        Audio() {
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
        }

        Mix_Music* load_music(const char* filename) {
            return Mix_LoadMUS(filename);
        }
        Mix_Chunk* load_audio(const char* filename) {
            return Mix_LoadWAV(filename);
        }

        void play_music(Mix_Music* music, int loops = -1) {
            Mix_PlayMusic(music, loops);
        }
        void play_sfx(Mix_Chunk* sfx) {
            Mix_PlayChannel(-1, sfx, 0);
        }
};
