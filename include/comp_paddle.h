#ifndef COMP_PADDLE_H
#define COMP_PADDLE_H

#include "paddle.h"

class CompPaddle : public Paddle {
public:
    CompPaddle(float positionX, float positionY, float width, float height, int speed);
    void Update(int ballY);
};

#endif
