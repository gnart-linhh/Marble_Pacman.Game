//
// Created by Nguyễn Trang Linh on 19/4/25.
//
#include "WIndow.h"
#include "LogStatus.h"
#include "Map.h"
#include <SDL.h>
#include <SDL_image.h>

Window::Window() {
    window=nullptr ;
    renderer=nullptr ;

}

Window::~Window() {
    if(window!=nullptr) {
        SDL_DestroyWindow(window);
        window=nullptr ;
    }
    if(renderer!=nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer=nullptr ;
    }
}

void Window::initSDL() {
    if(SDL_Init(SDL_INIT_EVERYTHING)<0) {
        Console->Status(SDL_GetError());
    }
    else {
        window=SDL_CreateWindow(WINDOW_TITLE.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        Console->Status("Window opened successfully");
        Running=true;
        if(window==nullptr) {
            Console->Status(SDL_GetError());
        }
        else {
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED||SDL_RENDERER_PRESENTVSYNC);
            Console->Status("Renderer created successfully");
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear"); // cài chất lượng khi scale hình ảnh
            SDL_RenderSetLogicalSize(renderer,SCREEN_WIDTH,SCREEN_HEIGHT); // co giãn sao cho fit screen, không thay đổi pos
        }
    }
}

void Window::quitSDL() {
    SDL_DestroyRenderer(renderer);
    renderer=nullptr ;
    SDL_DestroyWindow(window);
    window=nullptr ;
    SDL_Quit() ;
}

void Window::runGame() {
    map=new Map() ;
    objectTexture= new TextureSrc() ;
    objectTexture->loadTileTexture(renderer) ;
    objectTexture->loadPacmanAndGhostTexture(renderer) ;
    pacman=new Pacman() ;
    SDL_Event e;
    while(Running) {
        while (SDL_PollEvent(&e)!=0) {
            if(e.type==SDL_QUIT) Running=false ;
        }
        SDL_Rect dsRect ;
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        for (int i=0;i<28;++i) {
            for (int j=0;j<31;++j) {
                dsRect={i*16+217,j*16,16,16} ;
                objectTexture->renderTileTexture(renderer,map->getTileID(i,j),&dsRect);
            }
        }
        objectTexture->renderPacmanTexture(renderer, pacman->getPosX(), pacman-> getPosY(),-1) ;
        SDL_RenderPresent(renderer);
    }
}



