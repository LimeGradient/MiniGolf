#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "draw.h"
#include "log.h"
#include "cleanup.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define TILE_SIZE 40;

SDL_Window* win;
SDL_Renderer* ren;

bool keys[322];
const std::string path = "sprites/";

void LogSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

int main() {
    for (int i = 0; i < 322; i++) {
        keys[i] = false;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        LogSDLError(std::cout, "IMG_Init");
        SDL_Quit();
        return 1;
    }

    win = SDL_CreateWindow("Golf Devlog", 0, 0, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    std::string circle_path = "sprites/circle.png";
    SDL_Texture* circle = loadTexture(circle_path, ren);
    if (circle == nullptr) {
        LogSDLError(std::cout, "CircleError:");
        cleanup(circle, ren, win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_RenderClear(ren);

    int iW, iH;
	SDL_QueryTexture(circle, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;
	renderTexture(circle, ren, x, y);

    SDL_RenderPresent(ren);

    SDL_Rect circleRect = {x, y, iW, iH};

    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    keys[e.key.keysym.sym] = true;
                    // if (keys[SDLK_d]) {
                    //     circleRect.x += 10;
                    //     SDL_RenderClear(ren);
                    //     SDL_RenderCopy(ren, loadTexture(circle_path, ren), nullptr, &circleRect);
                    //     SDL_RenderPresent(ren);
                    // }
                    // if (keys[SDLK_a]) {
                    //     circleRect.x -= 10;
                    //     SDL_RenderClear(ren);
                    //     SDL_RenderCopy(ren, loadTexture(circle_path, ren), nullptr, &circleRect);
                    //     SDL_RenderPresent(ren);
                    // }
                    break;
                case SDL_KEYUP:
                    keys[e.key.keysym.sym] = false;
                    break;
            }

        }

    }

    cleanup(circle, ren, win);
    IMG_Quit();
    SDL_Quit();
}