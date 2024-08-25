#ifndef PLAYER_h
#define PLAYER_H
#include <SDL.h>

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
		void Update();
		void AttackPlayer();
		void GuardPlayer();
		
		int getPlayerX() const;
		int getPlayerY() const;
	};
}

#endif // PLAYER_H