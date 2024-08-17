#ifndef BALL_H
#define BALL_H

#include "raylib.h"

class Ball {
public:
	float posX, posY, radius, speedX, speedY;

    Ball(float positionX, float positionY, float radius, float speedX, float speedY);
    void Draw() const;
    void IncreaseSpeed();
    void Update();
    void ResetBall();
};

#endif
