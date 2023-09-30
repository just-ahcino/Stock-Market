#pragma once
#include <SDL.h>
#include <vector>
#include <algorithm>

class Inputs {
    public:
        bool is_scancode_pressed(SDL_Scancode scancode) {
            return keystate[scancode];
        }
        bool is_scancode_just_pressed(SDL_Scancode scancode) {
            bool result = false;
            if (keystate[scancode]) {
                if (std::find(keypressed.begin(), keypressed.end(), scancode) == keypressed.end()) {
                    keypressed.push_back(scancode);
                    result = true;
                }
            } else {
                if (std::find(keypressed.begin(), keypressed.end(), scancode) != keypressed.end()) {
                    keypressed.erase(std::remove(keypressed.begin(), keypressed.end(), scancode), keypressed.end());
                }
            }

            return result;
        }



    private:
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        std::vector<SDL_Scancode> keypressed;
};
