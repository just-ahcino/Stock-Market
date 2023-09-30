#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

struct Font {
    SDL_Texture* texture;
    int size = 16;
    std::string characters = "abcdefghijklmnopqrstuvwxyz0123456789 !@#$%^&*()-=_+.,:;/\\";
};

class RenderWindow {
    public:
        RenderWindow(const char* title, int w, int h) {
            window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, h, w, SDL_WINDOW_ALLOW_HIGHDPI);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);
        };

        SDL_Texture* loadTexture(const char* filePath) {
            SDL_Texture* texture = NULL;
            texture = IMG_LoadTexture(renderer, filePath);

            if (texture == NULL) {
                std::cout << "Failed to load texture. Error:" << SDL_GetError() << std::endl;
            }

            return texture;
        };

        void cleanUp() { SDL_DestroyWindow(window); };
        void clear() { SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); SDL_RenderClear(renderer); };
        void display() { SDL_RenderPresent(renderer); };

        void draw_texture(SDL_Texture* texture, SDL_Rect src, float x, float y, float sx, float sy, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
            SDL_SetTextureColorMod(texture, r, g, b);
            SDL_SetTextureAlphaMod(texture, a);
            SDL_Rect dst;
            dst.x = x;
            dst.y = y;
            dst.w = src.w * sx;
            dst.h = src.h * sy;

            SDL_RenderCopy(renderer, texture, &src, &dst);
        };

        void draw_line(float x1, float y1, float x2, float y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
            SDL_SetRenderDrawColor(renderer, r, g, b, a);
            SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
        };

        void draw_rect(SDL_Rect rect, bool fill, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
            fill ? SDL_RenderFillRect(renderer, &rect) : SDL_RenderDrawRect(renderer, &rect);
        };

        void draw_text(std::string text, float x, float y, Font font, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
            int v = 0;
            int o = 0;
            SDL_Rect rect; rect.x = 0; rect.y = 0; rect.w = font.size; rect.h = font.size;

            for (int i = 0; i < text.length(); i++) {
                if (text.at(i) != 126) {
                    rect.x = font.characters.find(text.at(i)) * font.size;
                    draw_texture(font.texture, rect, x + ((i-o)*font.size), y + (v*font.size), 1, 1, r, g, b, a);
                } else {
                    v++;
                    o = i + 1;
                }
            }
        };



        SDL_Window* window;
        SDL_Renderer* renderer;
};
