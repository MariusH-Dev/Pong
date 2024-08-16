#ifndef PADDLE_H
#define PADDLE_H

#include "raylib.h"

class Paddle {
protected:
    void LimitMove();

public:
    float posX, posY;
    float width, height;
    int speed;

    Paddle(float positionX, float positionY, float width, float height, int speed);
    void Draw();
    virtual void Update();
};

#endif
