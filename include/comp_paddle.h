#ifndef COMP_PADDLE_H
#define COMP_PADDLE_H

#include "paddle.h"

class CompPaddle : public Paddle {
private:
    float reactionTime, timeSinceReaction;

public:
    CompPaddle(float positionX, float positionY, float width, float height, int speed);
    void Update(float ballY,float ballSpeedX, float deltaTime);
};

#endif
