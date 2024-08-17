#include <iostream>
#include "paddle.h"
#include "raylib.h"

 
Paddle::Paddle(float positionX, float positionY, float width, float height, int speed)
    : posX(positionX), posY(positionY), width(width), height(height), speed(speed), isPowerUpActive(false), powerUpTimer(0.0f) { TextureLoad(); }

Paddle::~Paddle() { TextureUnload(); }

void Paddle::Draw() const 
{
    DrawTexturePro(metalTexture,
        Rectangle{ 0, 0, (float)metalTexture.width, (float)metalTexture.height },
        Rectangle{ posX, posY, width, height },
        Vector2{ 0, 0 }, 0.0f, WHITE);
}

void Paddle::LimitMove()
{
    if (posY <= 0)
        posY = 0;

    if (posY + height >= GetScreenHeight())
        posY = GetScreenHeight() - height;
}

void Paddle::TextureLoad() { metalTexture = LoadTexture("assets/images/metal_texture.png"); }

void Paddle::ResetPowerUp()
{
    height = 120;
    isPowerUpActive = false;
}

void Paddle::TextureUnload() const { UnloadTexture(metalTexture); }

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
