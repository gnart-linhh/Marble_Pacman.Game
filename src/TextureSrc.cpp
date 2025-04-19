//
// Created by Nguyễn Trang Linh on 19/4/25.
//
#include "TextureSrc.h"

TextureSrc::TextureSrc() {
    tileTexture = nullptr;
}

TextureSrc::~TextureSrc() {
    SDL_DestroyTexture(tileTexture);
    tileTexture = nullptr;
}

void TextureSrc::loadTileTexture(SDL_Renderer *renderer) {
    SDL_Surface *Image=IMG_Load("Assets/Images/Pacman Tile Labyrinth.png") ;
    if (Image==nullptr) {
        Console->Status(IMG_GetError());
    }
    else {
        tileTexture = SDL_CreateTextureFromSurface(renderer, Image);
        int x=0,y=0 ;
        for (int i=0;i<32;++i) {
            tileSprite[i]={x,y,16,16} ;
            y+=17 ;
            if (i%4==3) x+=17,y=0 ;
        }
        Console->Status("Loaded Tile Texture");
    }
    SDL_FreeSurface(Image);
    Image = nullptr;
}

void TextureSrc::renderTileTexture(SDL_Renderer *renderer, int tileID, SDL_Rect *dstRect) {
    SDL_RenderCopy(renderer,tileTexture,&tileSprite[tileID],dstRect);
}


