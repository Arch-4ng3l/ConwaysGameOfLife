#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <tuple>
#include <vector>
#include <array>

const int GAME_WIDTH = 640; 
const int GAME_HEIGHT = 480;

class Screen {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer= nullptr;
	SDL_Renderer* offscreen= nullptr;
	SDL_Event e;	
	std::vector<SDL_FPoint> points;
	public:
	Screen() {
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_CreateWindowAndRenderer(640*2, 480*2, 0, &window, &renderer);
		SDL_RenderSetScale(renderer, 4, 4);
		offscreen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	}

	void pixel(float x, float y) {
		points.emplace_back(x, y);
	}

	void show() {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		for(auto& point : points) {
			SDL_RenderDrawPointF(renderer, point.x, point.y);
		}
		SDL_RenderPresent(renderer);
	
	}
	void showPoint(int x, int y) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawPointF(renderer, x, y);

	}

	void clear() {
		points.clear();
	}

	void input(std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH>& game) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				SDL_Quit();
				exit(0);
			}
			if(e.type == SDL_MOUSEBUTTONDOWN) {
				do {
					int x;
					int y;
					SDL_GetMouseState(&x, &y);
					x = x / 4; 
					y = y / 4;

					game[x][y] = 1;


					this->pixel(x, y);
					this->showPoint(x, y);
					SDL_PollEvent(&e);

				} while(e.type != SDL_MOUSEBUTTONUP);
			}
		}
		this->clear();

	}


};
