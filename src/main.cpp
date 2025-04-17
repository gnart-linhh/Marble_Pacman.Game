#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "game.h"

using namespace std ;

const int SCREEN_WIDTH = 640 ;
const int SCREEN_HEIGHT = 480 ;

void waitUntilKeyPressed() {
    SDL_Event e ; bool quit=false ;
    while (!quit) {
        while (SDL_PollEvent(&e)!=0) {
            if (e.type == SDL_KEYDOWN||e.type == SDL_QUIT) {
                quit=true ;
            }
        }
    }
}
int main(int argc, char *argv[]) {
    Game game ;
    if (game.init(SCREEN_WIDTH,SCREEN_HEIGHT)) {
        game.render() ;
        waitUntilKeyPressed() ;
    }
    return 0;
}
