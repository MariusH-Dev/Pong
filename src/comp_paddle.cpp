#include <iostream>
#include "comp_paddle.h"

CompPaddle::CompPaddle(float positionX, float positionY, float width, float height, int speed)
    : Paddle(positionX, positionY, width, height, speed) {
    printf("CompPaddle initialized at Y position: %f\n", posY);
}

void CompPaddle::Update(int ballY) {
    if (posY + height / 2 > ballY) {
        posY -= speed;
    }
    if (posY + height / 2 <= ballY) {
        posY += speed;
    }
    LimitMove();
}
