#include <iostream>
#include "game.h"

Game::Game()
    : ball(GetScreenWidth() / 2, GetScreenHeight() / 2, 10, 8, 10),
    player(GetScreenWidth() - 55, GetScreenHeight() / 2 - 60, 20, 120, 10),
    computer(35, GetScreenHeight() / 2 - 60, 20, 120, 10),
    playerScore(0), compScore(0), gameStarted(false) {}

void Game::Update() {
    if (!gameStarted) {
        if (IsKeyPressed(KEY_ENTER)) {
            gameStarted = true;
        }
    }
    else {
        ball.Update();
        player.Update();
        computer.Update(ball.posY);

        // Ball collision detection with paddles
        if (CheckCollisionCircleRec({ ball.posX, ball.posY }, ball.radius, { player.posX, player.posY, player.width, player.height })) {
            ball.speedX *= -1;
        }

        if (CheckCollisionCircleRec({ ball.posX, ball.posY }, ball.radius, { computer.posX, computer.posY, computer.width, computer.height })) {
            ball.speedX *= -1;
        }

        // Check whether a point has been scored
        if (ball.posX + ball.radius >= GetScreenWidth()) {
            compScore++;
            printf("Computer scores! CompScore: %d\n", compScore);
            ball.ResetBall();
        }

        if (ball.posX - ball.radius <= 0) {
            playerScore++;
            printf("Computer scores! PlayerScore: %d\n", playerScore);
            ball.ResetBall();
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    if (!gameStarted) {
        DrawText("PONG", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 80, 60, WHITE);
        DrawText("Press ENTER to Start", GetScreenWidth() / 2 - 200, GetScreenHeight() / 2 + 20, 30, WHITE);
    }
    else {
        ball.Draw();
        player.Draw();
        computer.Draw();

        DrawText(TextFormat("%i", compScore), GetScreenWidth() / 4 - 20, 20, 25, WHITE);
        DrawText(TextFormat("%i", playerScore), 3 * (GetScreenWidth() / 4) - 20, 20, 25, WHITE);
    }

    EndDrawing();
}

void Game::ResetGame() {
    playerScore = 0;
    compScore = 0;
    ball.ResetBall();
    gameStarted = false;
}
