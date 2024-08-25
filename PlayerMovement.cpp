#include "Player.h" //header in Header Files
#include <iostream> //header in standard lib
#include <SDL.h>

using namespace Player;
using namespace std;

Movement::Movement() : playerX(100), playerY(100), speed(5), jumpSpeed(20), gravity(2), verticalVelocity(0), isJumping(false), isOnGround(true) {

}

int Movement::getPlayerX() const {
	return playerX;
}

int Movement::getPlayerY() const {
	return playerY;
}

void Movement::MovePlayer(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
		case SDLK_a:
			playerX -= speed;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			playerX += speed;
			break;
		case SDLK_SPACE:
			JumpPlayer();
			break;
		default:
			break;
		}
		if (!isOnGround) {
			verticalVelocity += gravity;
			playerY += verticalVelocity;
			if (playerY >= 100) { // Gotta define GroundLevel cause it could change depending on where the player is.
				playerY = 100;
				isOnGround = true;
				verticalVelocity = 0;
				isJumping = false;
			}
		}
	}
}

void Movement::JumpPlayer() {
	if (isOnGround) {
		verticalVelocity = -jumpSpeed;
		isJumping = true;
		isOnGround = false;
	}
}