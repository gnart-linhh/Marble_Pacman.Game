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
        TextureSrc();
        ~TextureSrc();
        void loadTileTexture(SDL_Renderer* renderer) ;
        void renderTileTexture(SDL_Renderer* renderer, int tileID, SDL_Rect* dstRect);
    private:
        LogStatus* Console=new LogStatus("TextureSrc");
        SDL_Texture* tileTexture;
        SDL_Rect tileSprite[32] ;
} ;
#endif //TEXTURESRC_H
