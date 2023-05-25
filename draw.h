#ifndef DRAW_H
#define DRAW_H

#include <string>
#include <SDL2/SDL.h>

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
SDL_Rect* renderRectFromTexture(SDL_Texture* tex, SDL_Rect* rect);


#endif