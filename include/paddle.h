#ifndef PADDLE_H
#define PADDLE_H

#include "raylib.h"
#include <string>

class Paddle {
protected:
    void LimitMove();
    void ResetPowerUp();

public:
    float posX, posY, width, height, powerUpTimer;
    int speed;
    bool isPowerUpActive;
    Texture2D metalTexture;
    
    Paddle(float positionX, float positionY, float width, float height, int speed);
    ~Paddle();
    
    void Draw() const;
    void TextureLoad();
    void TextureUnload() const;
    void Update();
};

#endif
