#include "screen.h"
#include <SDL2/SDL_timer.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <thread>
#include <unistd.h>


bool isAlive(std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH>& game, const int x, const int y) {
    int alive = 0;

    if(x > 0 && game[x-1][y] == 1) {
        alive++; 
    }
    if(x < GAME_WIDTH-1 && game[x+1][y] == 1) {
        alive++;
    }

    if(y < GAME_HEIGHT-1 && game[x][y+1] == 1) {
        alive++;
    }

    if(y > 0 && game[x][y-1] == 1) {
        alive++;
    }

    if(x > 0 && y > 0 && game[x-1][y-1]) {
        alive++;
    }

    if(x > 0 && y < GAME_HEIGHT-1 &&  game[x-1][y+1]) {
        alive++;
    }

    if(x < GAME_WIDTH-1 && y < GAME_HEIGHT-1 &&  game[x+1][y+1]) {
        alive++;
    }

    if(x < GAME_WIDTH-1 && y > 0 &&  game[x+1][y-1]) {
        alive++;
    }


    if(game[x][y] == 1 && alive < 2) {
        return false;
    }
    if(game[x][y] == 1 && (alive == 2 || alive == 3)) {
        return true;
    }
    if(alive > 3) {
        return false;
    }
    if(game[x][y] == 0 && alive==3) {
        return true;
    }

    return false;
}

int main() {
    Screen screen;
    std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> display {};
    std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> swap {};

    for(auto& row : display) {
        std::generate(row.begin(), row.end(), []() { return rand() % 10 == 0 ? 1 : 0;});
    }
    while(true) {
        for(int i = 0; i < GAME_WIDTH; i++) {
            for(int j = 0; j < GAME_HEIGHT; j++) {
                swap[i][j] = isAlive(display, i, j) ? 1 : 0;
            }
        }

        int x = -1;
        int y = -1;
        screen.input(swap);


        if(x > -1 && y > -1) {
            swap[x][y] = 1;
        }

        for(int i = 0; i < GAME_WIDTH; i++) {
            for(int j = 0; j < GAME_HEIGHT; j++) {
                if(swap[i][j]) {
                    screen.pixel(i, j);
                }
            }
        }
        std::copy(swap.begin(), swap.end(), display.begin());


        screen.show();
        SDL_Delay(10);
        screen.clear();


    }

}

