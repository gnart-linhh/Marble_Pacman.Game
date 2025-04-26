//
// Created by Nguyễn Trang Linh on 19/4/25.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <string>
#include "LogStatus.h"
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"
#include "TextureSrc.h"
class Window {
    public:
        static const int SCREEN_WIDTH=882 ;
        static const int SCREEN_HEIGHT=496 ;
        const std::string WINDOW_TITLE="Pacman_Marble_vers" ;
        Window();
        ~Window();
        void initSDL() ;
        void quitSDL() ;
        void runGame() ;
    private:
        Map* map ;
        Pacman* pacman=nullptr ;
        Ghost* blinky=nullptr ;
        Ghost* inky=nullptr ;
        Ghost* pinky=nullptr ;
        Ghost* clyde=nullptr ;
        SDL_Window *window=nullptr ;
        SDL_Renderer *renderer=nullptr ;
        LogStatus* Console=new LogStatus("Window") ;
        bool Running=false ;
        TextureSrc* objectTexture ;
    protected:
        void renderGhost(SDL_Renderer* renderer, Ghost* &ghost, int ghostID) ;
};
#endif //WINDOW_H
