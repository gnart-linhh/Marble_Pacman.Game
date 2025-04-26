//
// Created by Nguyễn Trang Linh on 19/4/25.
//
#pragma once
#ifndef TEXTURESRC_H
#define TEXTURESRC_H

#include <SDL.h>
#include <SDL_image.h>
#include "LogStatus.h"

class TextureSrc{
    public:
        static const int UP=0 ;
        static const int DOWN=2 ;
        static const int LEFT=3 ;
        static const int RIGHT=1 ;
        static const int TOTAL_GHOST=4 ;
        static const int FRIGHTEN_GHOST_1=4 ;
        static const int FRIGHTEN_GHOST_2=5 ;
        static const int DEAD_PACMAN=5 ;
        static const int GHOST_SPIRIT=6 ;
        static const int BLINKY=0 ;
        static const int PINKY=1 ;
        static const int INKY=2 ;
        static const int CLYDE=3 ;
        TextureSrc();
        ~TextureSrc();
        bool pacmanIsDead() ;
        void loadTileTexture(SDL_Renderer* renderer) ;
        void renderTileTexture(SDL_Renderer* renderer, int tileID, SDL_Rect* dstRect);
        void loadPacmanAndGhostTexture(SDL_Renderer* &renderer) ;
        void renderPacmanTexture(SDL_Renderer* &renderer, int posX, int posY, int status) ;
        void renderGhostTexture(SDL_Renderer* &renderer, int posX, int posY,int ghostID, int status) ;
    private:
        LogStatus* Console=new LogStatus("TextureSrc");
        SDL_Texture* tileTexture;
        SDL_Rect tileSprite[36] ;
        SDL_Texture* entityTexture ;
        SDL_Texture* ghostScore ;
        SDL_Rect pacmanUp[3] ;
        SDL_Rect pacmanDown[3] ;
        SDL_Rect pacmanLeft[3] ;
        SDL_Rect pacmanRight[3] ;
        SDL_Rect pacmanDEAD[11] ;
        SDL_Rect ghost[7][6][2] ;
        int pacmanFrame ;
        int ghostFrame[7] ;
} ;
#endif //TEXTURESRC_H
