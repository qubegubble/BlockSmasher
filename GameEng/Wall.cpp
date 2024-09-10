#include "Headers\Wall.h";
#include <SDL2/SDL.h>

Wall::Wall(int x, int y, int w, int h, SDL_Color initialColor) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	color = initialColor;
}

SDL_Rect Wall::GetRect() const {
	return rect;
}

SDL_Color Wall::GetColor() const {
	return color;
}

void Wall::SetColor(SDL_Color newColor) {
	color = newColor;
}

void Wall::Render(SDL_Renderer* renderer) const{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}