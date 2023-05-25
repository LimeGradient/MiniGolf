#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ball.h"

float calculateBallForce(MousePos down, MousePos up) {
    int x, y;
    x = up.x - down.x;
    y = up.y - down.y;

    return x - y;
}