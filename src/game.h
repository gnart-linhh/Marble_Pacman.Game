//
// Created by Nguyễn Trang Linh on 19/3/25.
//
#ifndef GAME_H
#define GAME_H
#include <SDL.h>

class Game{
    public:
        Game() ;
        ~Game() ;
        bool init(int SCREEN_WIDTH, int SCREEN_HEIGHT);
        void render();
        void free() ;
    private:
        SDL_Texture* mTexture ;
        SDL_Renderer* gRenderer;
        SDL_Window* gWindow;

} ;

#endif //GAME_H
