#include <iostream>
#include <string>

#include "raylib.h"

using namespace std;

Color Green = Color{ 38, 185, 154, 255 };
Color Dark_Green = Color{ 20, 160, 133, 255 };
Color Light_Green = Color{ 129, 204, 184, 255 };
Color Yellow = Color{ 243, 213, 91, 255 };

int playerScore = 0;
int compScore = 0;

// Ball Class
class Ball {
public:
	float posX, posY;
	int speedX, speedY;
	int radius;
	Color color = WHITE;
	
	Ball(float positionX, float positionY, int radius, int speedX, int speedY) 
	{
		this->posX = positionX;
		this->posY = positionY;
		this->radius = radius;
		this->speedX = speedX;
		this->speedY = speedY;
	}

	void Draw() 
	{
		DrawCircle(posX, posY, radius, color);
	}

	void Update() 
	{
		posX += speedX;
		posY += speedY;

		// Computer scores 
		if (posX + radius >= GetScreenWidth()) 
		{
			compScore++;
			ResetBall();
		}

		// Player scores
		if (posX - radius <= 0) 
		{
			playerScore++;
			ResetBall();
		}
		
		if (posY + radius >= GetScreenHeight() || posY - radius <= 0) 
		{
			speedY *= -1;
		}
	}

	void ResetBall() {
		posX = GetScreenWidth() / static_cast<float>(2);
		posY = GetScreenHeight() / static_cast<float>(2);

		int speedChoice[2] = { -1,1 };
		speedX *= speedChoice[GetRandomValue(0, 1)];
		speedY *= speedChoice[GetRandomValue(0, 1)];
	}


};

// Paddle Class
class Paddle {
protected:
	void LimitMove()
	{
		if (posY <= 0) {
			posY = 0;
		}
		if (posY + height >= GetScreenHeight()) {
			posY = GetScreenHeight() - height;
		}
	}

public:
	float posX, posY;
	float width, height;
	int speed;
	Color color = WHITE;

	Paddle(float positionX, float positionY, float width, float height, int speed) 
	{
		this->posX = positionX;
		this->posY = positionY;
		this->width = width;
		this->height = height;
		this->speed = speed;
	}

	void Draw()
	{
		DrawRectangleRounded(Rectangle{ posX, posY, width, height }, 0.8, 0, color);
	}

	void Update()
	{
		if (IsKeyDown(KEY_UP))
		{
			posY -= speed;
		}
		
		if (IsKeyDown(KEY_DOWN))
		{
			posY += speed;
		}
		LimitMove();
	}
};

// CompPaddle Class
class CompPaddle : public Paddle {
public:
	CompPaddle(float positionX, float positionY, float width, float height, int speed)
		: Paddle(positionX, positionY, width, height, speed) { };

	void Update(int ballY) {
		if (posY + height / 2 > ballY) {
			posY -= speed;
		}
		if (posY + height / 2 <= ballY) {
			posY += speed;
		}
		LimitMove();
	}
};


int main() {

	const int windowWidth = 1024;
	const int windowHeight = 768;

	InitWindow(windowWidth, windowHeight, "Pong 2D");
	SetTargetFPS(60);
	
	// Create instances of game objects
	Ball ball(windowWidth / 2, windowHeight / 2, 10, 8, 10);
	Paddle player(windowWidth - 55, windowHeight / 2 - 60, 20, 120, 10);
	CompPaddle computer(35, windowHeight / 2 - 60, 20, 120, 10);

	// Game Loop
	while (WindowShouldClose() == false) 
	{
		BeginDrawing();

		ball.Update();
		player.Update();
		computer.Update(ball.posY);

		if (CheckCollisionCircleRec({ ball.posX, ball.posY }, ball.radius, { player.posX, player.posY, player.width, player.height })) {
			ball.speedX *= -1;
		}

		if (CheckCollisionCircleRec({ ball.posX, ball.posY }, ball.radius, { computer.posX, computer.posY, computer.width, computer.height })) {
			ball.speedX *= -1;
		}

		// Drawing Game
		ClearBackground(BLACK);

		ball.Draw();

		player.Draw();
		computer.Draw();

		DrawText(TextFormat("%i", compScore), windowWidth / 4 - 20, 20, 25, WHITE);
		DrawText(TextFormat("%i", playerScore), 3 * (windowWidth / 4) - 20, 20, 25, WHITE);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

