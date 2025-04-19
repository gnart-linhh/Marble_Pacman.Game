//
// Created by Nguyễn Trang Linh on 19/4/25.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <string>
#include "LogStatus.h"
#include "Map.h"
#include "TextureSrc.h"
class Window {
    public:
        static const int SCREEN_WIDTH=882 ;
        static const int SCREEN_HEIGHT=496 ;
        const std::string WINDOW_TITLE="Crystal Maze" ;
        Window();
        ~Window();
        void initSDL() ;
        void quitSDL() ;
        void runGame() ;
    private:
        Map* map ;
        SDL_Window *window=nullptr ;
        SDL_Renderer *renderer=nullptr ;
        LogStatus* Console=new LogStatus("Window") ;
        bool Running=false ;
        TextureSrc* objectTexture ;
};
#endif //WINDOW_H
