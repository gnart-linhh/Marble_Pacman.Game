//
// Created by Nguyễn Trang Linh on 19/3/25.
//
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "game.h"
#include "defs.h"

Game::Game() {
    gRenderer=NULL ;
    gWindow=NULL ;
}

Game::~Game() {
    free() ;
}

void Game::free () {
    if (mTexture!=NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture=NULL ;
    }
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer=NULL ;
    gWindow=NULL ;
    SDL_Quit();
}

void Game::render() {
    SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF,0xFF,0xFF) ;
    SDL_RenderClear(gRenderer) ;
    SDL_RenderPresent(gRenderer) ;
}

bool Game::init(int SCREEEN_WIDTH, int SCREEEN_HEIGHT) {
    bool success=true ;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        success=false ;
    }
    else {
        gWindow = SDL_CreateWindow("Crystals Maze",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEEN_WIDTH, SCREEEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
            success=false ;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
                success=false ;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
                int imgFlags=IMG_INIT_PNG ;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("IMG_Init: %s\n", IMG_GetError());
                    success=false ;
                }
            }
        }
    }
    return success ;
}


