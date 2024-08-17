#include <iostream>
#include "powerup.h"

PowerUp::PowerUp(float posX, float posY)
	: posX(posX), posY(posY), width(10), height(10), color(YELLOW), isActive(true) {
	do {
		speedX = static_cast<float>(GetRandomValue(-3, 3));
	} while (speedX == 0);
	speedY = 2.0f;
}

void PowerUp::ActivateEffect(Paddle &paddle) 
{
	paddle.height *= 1.2f;
	paddle.isPowerUpActive = true;
	paddle.powerUpTimer = 60.0f;
	isActive = false;
}

bool PowerUp::CheckCollisionWithPaddle(Rectangle paddle) const 
{
	Rectangle powerUpRect = { posX, posY, width, height };

	return isActive && CheckCollisionRecs(powerUpRect, paddle);
}

void PowerUp::Draw() const
{
	if (isActive) {
		DrawRectangle(posX, posY, width, height, color);
		std::cout << "Power-Up Draw!" << std::endl;
	}
}

void PowerUp::Update()
{
	posX += speedX;  
	posY += speedY;

	float screenHeight = GetScreenHeight();

	float middleTop = screenHeight * 0.4f;  
	float middleBottom = screenHeight * 0.6f; 

	if (posY <= middleTop) {
		posY = middleTop;
		speedY *= -1;  
	}
	else if (posY + height >= middleBottom) {
		posY = middleBottom - height;
		speedY *= -1;  
	}

	if (posX <= 0 || posX + width >= GetScreenWidth())
		isActive = false;

	
}