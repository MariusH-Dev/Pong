#ifndef POWERUP_H
#define POWERUP_H

#include "paddle.h"
#include "raylib.h"

class PowerUp {
public:
	float posX, posY, width, height, speedX, speedY;
	Color color;
	bool isActive;

	PowerUp(float posX, float posY);
	void ActivateEffect(Paddle& paddle);
	void Draw() const;
	void Update();
	bool CheckCollisionWithPaddle(Rectangle paddle) const;

};
#endif