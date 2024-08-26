#ifndef PLAYER_h
#define PLAYER_H
#include <SDL.h>
#include <vector>
#include "Platform.h"

namespace Player {
	
	class Movement {
	private:
		int playerX;
		int playerY;
		int speed;
		int jumpSpeed;
		int gravity;
		int verticalVelocity;
		bool isJumping;
		bool isOnGround;
		bool movingLeft;
		bool movingRight;
		bool jumping;

	public:
		Movement();
		void HandleEvent(const SDL_Event& event);
		void Update(const std::vector<Platform>& platforms);
		void AttackPlayer();
		void GuardPlayer();
		
		int GetPlayerX() const;
		int GetPlayerY() const;

		bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
	};
}

#endif // PLAYER_H