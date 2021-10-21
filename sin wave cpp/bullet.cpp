#include "bullet.h"
void bullet::move() {
	angle += 1;

	yPos += A * sin(B * (angle - C)) + D;

	xPos += Vx;

	bulletRect.x = xPos;
	bulletRect.y = yPos;
}

void bullet::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
	SDL_RenderDrawRect(renderer, &bulletRect);
	SDL_RenderFillRect(renderer, &bulletRect);
	
}

bullet::bullet() {
	xPos = 200;
	yPos = 200;
	bulletRect.x = xPos;
	bulletRect.y = yPos;
	bulletRect.w = 20;
	bulletRect.h = 20;
}

bullet::bullet(float x, float y) {
	bulletRect.x = x;
	bulletRect.y = y;
	xPos = x;
	yPos = y;
	bulletRect.w = 20;
	bulletRect.h = 20;
}

void bullet::adjustVar(bool up, bool down) {
	if (up) {
		D += 1;
	}
	if (down) {
		D -= 1;
	}
}

float bullet::getX() {
	return xPos + 20;
}