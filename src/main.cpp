#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Window.h"

using namespace std ;

int main(int argc, char *argv[]) {
    Window* window=new Window() ;
    window->initSDL() ;
    window->runGame() ;
    window->quitSDL() ;
    return 0;
}
