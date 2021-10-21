#include<SDL.h>
#include<math.h>

#pragma once
class bullet{
private:
	SDL_Rect bulletRect;
	float xPos;
	float yPos;
	int A = 4;
	float B = .2;
	int C = 7;
	int D = 0;
	double Vx = 5;
	double Vy = 0;
	double angle = 0;
public:
	void draw(SDL_Renderer* renderer);
	void move();
	bullet();
	bullet(float x, float y);
	void adjustVar(bool up, bool down);
	float getX();
};

