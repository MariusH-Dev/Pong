#ifndef PADDLE_H
#define PADDLE_H

#include "raylib.h"

class Paddle {
protected:
    void LimitMove();
    void ResetPowerUp();

public:
    float posX, posY, width, height, powerUpTimer;
    int speed;
    bool isPowerUpActive;

    Paddle(float positionX, float positionY, float width, float height, int speed);
    void Draw();

    void Update();
};

#endif
