#include <iostream>
#include "comp_paddle.h"

CompPaddle::CompPaddle(float positionX, float positionY, float width, float height, int speed)
    : Paddle(positionX, positionY, width, height, speed), reactionTimer(0.f) {}


void CompPaddle::Update(float ballY,float ballSpeedX, float deltaTime) 
{
    // Set random offset
    float offset = static_cast<float>(GetRandomValue(-30, 30));

    // Check whether the ball flies in the direction of the computer paddle
    if (ballSpeedX < 0) {  // The ball flies to the left, i.e. to the computer paddle


        // Falls der Ball gerade die Richtung gewechselt hat, setzen wir den Timer zurück
        if (reactionTimer <= 0.0f) {
            reactionTimer = GetRandomValue(0, 5) / 200.0f;  
        }

        // Reduziere den Timer
        reactionTimer -= deltaTime;

        // Paddle reagiert nur, wenn der Timer abgelaufen ist
        if (reactionTimer <= 0.0f) {

            // Calculate the difference between the center of the paddle and the ball with offset
            float distanceToBall = (ballY + offset) - (posY + height / 2);

            // Scale the speed based on the distance to the ball
            float scalingFactor = 0.3f;  // Scale the movement speed for fine control
            float adjustedSpeed = scalingFactor * distanceToBall;

            // Limit the maximum speed so that the paddle does not become too fast
            if (adjustedSpeed > speed)
                adjustedSpeed = speed;

            else if (adjustedSpeed < -speed)
                adjustedSpeed = -speed;

            // Movement based on the calculated speed and deltaTime
            posY += adjustedSpeed * deltaTime * 60;  // Scale speed with deltaTime

            LimitMove();
        }
    }
}
