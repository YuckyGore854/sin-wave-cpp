#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "bullet.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	SDL_Window* window = SDL_CreateWindow("Sin wave", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 600, NULL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, NULL);
	bool running = true;

	SDL_Surface* tempSprites = NULL;//temporary surface is needed, this will be deleted later

	SDL_Texture* ship;
	tempSprites = IMG_Load("ship.png");//loads a given string file path into the surface we just made
	std::cout << SDL_GetError() << std::endl;
	ship = SDL_CreateTextureFromSurface(renderer, tempSprites);//puts the contents of that surface into our classes texture variable
	SDL_FreeSurface(tempSprites);
	if (ship == NULL) {
		std::cout << "Nah" << std::endl;
	}
	vector<bullet*> bullets;
	vector<bullet*>::iterator bulletIter;

	int fps = 60;//these variables are for manually capping the framerate
	int frameDelay = 1000 / fps;//this is the frameDelay variable, or approximately how long each frame should take

	Uint32 frameStart;//this variable holds the amount of time at the beginning of a frame
	int frameTime;//this variable holds the actual time of the current frame
	SDL_Event event;

	SDL_Rect playerRect;
	playerRect.x = 200;
	playerRect.y = 200;
	playerRect.w = 59;
	playerRect.h = 64;

	int currBullet = 0;

	while (running) {
		frameStart = SDL_GetTicks();

		
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}
		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
		if (keyboardState[SDL_SCANCODE_UP] || keyboardState[SDL_SCANCODE_W]) {
			playerRect.y -= 7;
		}
		if (keyboardState[SDL_SCANCODE_DOWN] || keyboardState[SDL_SCANCODE_S]) {
			playerRect.y += 7;
		}
		if (keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A]) {
			playerRect.x -= 7;
		}
		if (keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D]) {
			playerRect.x += 7;
		}
		bool UPDOWN[2];
		if (keyboardState[SDL_SCANCODE_I]) {
			UPDOWN[0] = true;
		}
		else
			UPDOWN[0] = false;
		if (keyboardState[SDL_SCANCODE_K]) {
			UPDOWN[1] = true;
		}
		else
			UPDOWN[1] = false;
	
		if (keyboardState[SDL_SCANCODE_SPACE]) {
			bullet* newBullet = new bullet(playerRect.x, playerRect.y);

			bullets.push_back(newBullet);
		}
		bullet bill;
		bill.draw(renderer);
		bill.move();
		
		//RENDER SECTION/////////////////////////
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		SDL_RenderCopy(renderer, ship, NULL, &playerRect);
		for (bulletIter = bullets.begin(); bulletIter != bullets.end(); ++bulletIter) {
			
			if (bullets.size() > 0) {
				(*bulletIter)->draw(renderer);
				(*bulletIter)->move();

				if ((*bulletIter)->getX() > 700) {

					bullets.erase(bullets.begin() + 1);
					
				}
			}
			currBullet++;
			//(*bulletIter)->adjustVar(UPDOWN[0], UPDOWN[1]);
		}
		currBullet = 0;
		std::cout << bullets.size() << std::endl;
		SDL_RenderPresent(renderer);
		
		//END RENDER SECTION//////////////////////
		frameTime = SDL_GetTicks() - frameStart;//calculates how long a frame has been rendered for

		if (frameDelay > frameTime)//if the wanted amount of time between frames is bigger than the current amount of time it took to render the last frame
			SDL_Delay(frameDelay - frameTime);//delay the game until 16.66... miliseconds have passed
	}

	std::cout << "Hello world" << endl;
	return 0;
}