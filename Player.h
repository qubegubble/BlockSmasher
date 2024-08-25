#pragma once
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

	public:
		Movement();
		void MovePlayer();
		void JumpPlayer();
		void AttackPlayer();
		void GuardPlayer();
		
		int getPlayerX() const;
		int getPlayerY() const;
	};
}