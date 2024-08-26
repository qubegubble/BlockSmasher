#include "Platform.h";

Platform::Platform(int x, int y, int w, int h, SDL_Color initialColor) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	color = initialColor;
}

SDL_Rect Platform::GetRect() const {
	return rect;
}

SDL_Color Platform::GetColor() const {
	return color;
}

void Platform::SetColor(SDL_Color newColor) {
	color = newColor;
}

void Platform::Render(SDL_Renderer* renderer) const{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}