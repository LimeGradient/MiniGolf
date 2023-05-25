#ifndef BALL_H
#define BALL_H

typedef struct MousePos {
    int x; int y;
} MousePos;

float calculateBallForce(MousePos start, MousePos end);

#endif