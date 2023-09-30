#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>

#include "RenderWindow.hpp"
#include "Audio.hpp"
#include "Inputs.hpp"

bool running = true;

int t = 0;
int h = 20000;
int o = 0;
int c = 100;
int m = 100;
int s = 0;
int last_index = 0;
std::vector<int> prices = {100};

int main(int argc, char* argv[]) {
    //Initializes the window and the inputs
    RenderWindow window("Stock Market ++", 512, 512);
    Audio audio;
    Inputs inputs;

    //Sets the icon
    SDL_Surface* icon = IMG_Load("res/img/icon.png");
    SDL_SetWindowIcon(window.window, icon);

    //Prepares Textures and Fonts
    SDL_Texture* FG = window.loadTexture("res/img/FG.png");
    SDL_Texture* BG = window.loadTexture("res/img/BG.png");
    Font font; font.texture = window.loadTexture("res/img/font.png");

    //Prepares Audio
    Mix_Chunk* sfx = audio.load_audio("res/sfx/buy_sell.wav");

    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        //Update functions
        t ++;
        h ++;

        //Everytime the line progresses
        if (t > 4000) {
            t = 0;
            std::srand(std::time(nullptr));
            int price = prices[prices.size() - 1] + std::rand() % 60 - 20 - o;
            if (price < 0) { price = 0; }
            prices.push_back(price);

            if (prices.size() > 24) { prices.erase(prices.begin()); }
            if (prices[prices.size() - 1] > c + 192) { c += prices[prices.size() - 1] - (c + 192); }
            if (prices[prices.size() - 1] < c - 192) { c += prices[prices.size() - 1] - (c - 192); }
        }

        //Changes the offset
        if (h > 50000) {
            h = 0;
            std::srand(std::time(nullptr));
            o = std::rand() % 80 - 30;
        }

        last_index = prices[prices.size() - 1];


        //Buy Share
        if (inputs.is_scancode_just_pressed(SDL_SCANCODE_EQUALS)) {
            if (s < 3) {
                m -= last_index; s++;
                audio.play_sfx(sfx);
            }
        }
        //Sell share
        if (inputs.is_scancode_just_pressed(SDL_SCANCODE_MINUS)) {
            if (s > 0) {
                m += last_index; s--;
                audio.play_sfx(sfx);
            }
        }


        //Clears window
        SDL_Rect rect; rect.x = 0; rect.y = 0; rect.w = 512; rect.h = 512;
        window.draw_texture(BG, rect, 0, 0, 1, 1, 255, 255, 255, 255);

        //Draw functions

        //Draw Line
        for (int i = 1; i < prices.size(); i ++) {
            window.draw_line(
                (i - 1)*16 + 32,
                272 + -prices[i - 1] + c,
                (i)*16 + 32,
                272 + -prices[i] + c,
                255, 255, 255, 255
            );
        }

        //Draw FG
        window.draw_texture(FG, rect, 0, 0, 1, 1, 255, 255, 255, 255);

        //Current Money
        window.draw_text("money: " + std::to_string(m) + "$", 16, 24, font, 122, 122, 122, 255);

        //Shares
        window.draw_text("shares: " + std::to_string(s) + "/3", 320, 24, font, 122, 122, 122, 255);

        //Current Price
        window.draw_text(std::to_string(last_index),
            (prices.size() - 1)*16 + 40,
            264 + -last_index + c,
            font, 255, 255, 255, 255
        );

        //Renders window
        window.display();
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}
