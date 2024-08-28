#ifndef PLAYER_h
#define PLAYER_H
#include <SDL.h>
#include <vector>
#include "Wall.h"

namespace Player {
	
	class Movement {
	private:
		int playerX;
		int playerY;
		int speed;
		bool movingLeft;
		bool movingRight;
		bool movingDown;
		bool movingUp;
		bool isInteracting;
		bool playerAttacking;
		bool playerGuarding;

	public:
		Movement();
		void HandleEvent(const SDL_Event& event);
		void Update(const std::vector<Wall>& platforms);
		void AttackPlayer();
		void GuardPlayer();
		void Interact();
		
		int GetPlayerX() const;
		int GetPlayerY() const;

		bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
	};
}

#endif