#include <iostream>

#include "ball.h"
#include "game.h"


Ball::Ball(float positionX, float positionY, float radius, float speedX, float speedY)
	: posX(positionX), posY(positionY), radius(radius), speedX(speedX), speedY(speedY) {}

void Ball::Draw() const
{
	DrawCircle(static_cast<int>(posX), static_cast<int>(posY), radius, Color(WHITE));
}

void Ball::IncreaseSpeed() {
	const int maxSpeed = 18;

	if (speedX < maxSpeed)
		speedX *= 1.2f;

	if (speedY < maxSpeed)
		speedY *= 1.05f;
}

void Ball::Update()
{
	posX += speedX;
	posY += speedY;
}

void Ball::ResetBall() 
{
	posX = GetScreenWidth() / static_cast<float>(2);
	posY = GetScreenHeight() / static_cast<float>(2);

	speedX = (speedX > 0 ? -8 : 8);  // Zufällige Richtung
	speedY = 8;
}