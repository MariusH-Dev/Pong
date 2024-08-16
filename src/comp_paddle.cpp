#include <iostream>
#include "comp_paddle.h"

CompPaddle::CompPaddle(float positionX, float positionY, float width, float height, int speed)
    : Paddle(positionX, positionY, width, height, speed), reactionTime(0.1f), timeSinceReaction(0.0f) {}


void CompPaddle::Update(float ballY,float ballSpeedX, float deltaTime) {

    // Check whether the ball flies in the direction of the computer paddle
    if (ballSpeedX < 0) {  // The ball flies to the left, i.e. to the computer paddle

        // Calculate the difference between the center of the paddle and the ball
        float distanceToBall = ballY - (posY + height / 2);

        // Scale the speed based on the distance to the ball
        float scalingFactor = 0.3f;  // Scale the movement speed for fine control
        float adjustedSpeed = scalingFactor * distanceToBall;

        // Limit the maximum speed so that the paddle does not become too fast
        if (adjustedSpeed > speed) {
            adjustedSpeed = speed;
        }
        else if (adjustedSpeed < -speed) {
            adjustedSpeed = -speed;
        }

        // Movement based on the calculated speed and deltaTime
        posY += adjustedSpeed * deltaTime * 60;  // Scale speed with deltaTime

        LimitMove();
    }
}
