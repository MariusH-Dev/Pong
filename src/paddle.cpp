#include <iostream>
#include "paddle.h"

Paddle::Paddle(float positionX, float positionY, float width, float height, int speed)
    : posX(positionX), posY(positionY), width(width), height(height), speed(speed) {}



void Paddle::Draw() {
    
    DrawRectangleRounded(Rectangle{ posX, posY, width, height }, 0.8, 0, Color{ 255,255,255,255 });
}

void Paddle::Update() {
    if (IsKeyDown(KEY_UP)) {
        posY -= speed;
        printf("UP key pressed. New Y position: %f\n", posY);
    }
    if (IsKeyDown(KEY_DOWN)) {
        posY += speed;
        printf("DOWN key pressed. New Y position: %f\n", posY);
    }
 
    LimitMove();
}

void Paddle::LimitMove() {
    if (posY <= 0) {
        posY = 0;
    }
    if (posY + height >= GetScreenHeight()) {
        posY = GetScreenHeight() - height;
    }
}
