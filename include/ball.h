#ifndef BALL_H
#define BALL_H

#include "raylib.h"

class Ball {
public:
	float posX, posY;
	int speedX, speedY;
	int radius;

    Ball(float positionX, float positionY, int radius, int speedX, int speedY);
    void Draw();
    void Update();
    void ResetBall();
};

#endif
