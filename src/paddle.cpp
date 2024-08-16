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
    }
    if (IsKeyDown(KEY_DOWN)) {
        posY += speed;
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
