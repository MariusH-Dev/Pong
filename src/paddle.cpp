#include <iostream>
#include "paddle.h"

Paddle::Paddle(float positionX, float positionY, float width, float height, int speed)
    : posX(positionX), posY(positionY), width(width), height(height), speed(speed), isPowerUpActive(false), powerUpTimer(0.0f) {}



void Paddle::Draw() 
{
    DrawRectangleRounded(Rectangle{ posX, posY, width, height }, 0.8, 0, Color{ 255,255,255,255 });
}

void Paddle::LimitMove()
{
    if (posY <= 0)
        posY = 0;

    if (posY + height >= GetScreenHeight())
        posY = GetScreenHeight() - height;
}

void Paddle::ResetPowerUp()
{
    height = 120;
    isPowerUpActive = false;
}

void Paddle::Update() 
{
    if (isPowerUpActive) {
        powerUpTimer -= GetFrameTime();  

        if (powerUpTimer <= 0) {
            ResetPowerUp(); 
        }
    }

    if (IsKeyDown(KEY_UP)) 
        posY -= speed;

    if (IsKeyDown(KEY_DOWN)) 
        posY += speed;
 
    LimitMove();
}