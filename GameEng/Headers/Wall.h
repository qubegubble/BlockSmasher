#ifndef WALL_H
#define WALL_H

#include <SDL.h>

class Wall {
private:
	SDL_Rect rect;
	SDL_Color color;

public:
	Wall(int x, int y, int w, int h, SDL_Color initialColor);


	SDL_Rect GetRect() const;
	SDL_Color GetColor() const;

	void Render(SDL_Renderer* renderer) const;
	void SetColor(SDL_Color newColor);
};

#endif
