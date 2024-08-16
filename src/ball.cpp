#include "ball.h"

Ball::Ball(float positionX, float positionY, int radius, int speedX, int speedY)
	: posX(positionX), posY(positionY), radius(radius), speedX(speedX), speedY(speedY) {}

void Ball::Draw()
{
	DrawCircle(posX, posY, radius, Color(WHITE));
}

void Ball::Update()
{
	posX += speedX;
	posY += speedY;


	if (posY + radius >= GetScreenHeight() || posY - radius <= 0) {
		speedY *= -1;
	}
}

void Ball::ResetBall() {
	posX = GetScreenWidth() / static_cast<float>(2);
	posY = GetScreenHeight() / static_cast<float>(2);

	int speedChoice[2] = { -1,1 };
	speedX *= speedChoice[GetRandomValue(0, 1)];
	speedY *= speedChoice[GetRandomValue(0, 1)];
}