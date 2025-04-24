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
    SDL_Surface *Image=IMG_Load("Assets/Images/MapTile.png") ;
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
        x=0 ;y= 68 ;
        for (int i=32;i<36;++i) {
            tileSprite[i]={x,y,16,16} ;
            x+=17 ;
        }
        Console->Status("Loaded Tile Texture");
    }
    SDL_FreeSurface(Image);
    Image = nullptr;
}

void TextureSrc::renderTileTexture(SDL_Renderer *renderer, int tileID, SDL_Rect *dstRect) {
    SDL_RenderCopy(renderer,tileTexture,&tileSprite[tileID],dstRect);
}

void TextureSrc::loadPacmanAndGhostTexture(SDL_Renderer* &renderer) {
    SDL_Surface* Image=IMG_Load("Assets/Images/PacmanAndGhost.png") ;
    if (Image==nullptr) {
        Console->Status(IMG_GetError());
    }
    else {
        entityTexture=SDL_CreateTextureFromSurface(renderer, Image);
        int posTexX=0 , posTexY=0;
        for (int i=0;i<3;i++) {
            pacmanUp[i]={posTexX, posTexY, 30, 30} ;
            posTexX+=31 ;
        }
        for (int i=0;i<3;i++) {
            pacmanDown[i]={posTexX, posTexY, 30, 30} ;
            posTexX+=31 ;
        }
        for (int i=0;i<3;i++) {
            pacmanLeft[i]={posTexX, posTexY, 30, 30} ;
            posTexX+=31 ;
        }
        for (int i=0;i<3;i++) {
            pacmanRight[i]={posTexX, posTexY, 30, 30} ;
            posTexX+=31 ;
        }
        posTexX = 0 ;
        for (int i=0;i<11;++i) {
            pacmanDEAD[i]={posTexX, 155, 30, 30} ;
            posTexX+=31 ;
        }
        Console->Status("Loaded Pacman Texture");
        posTexX = 0 ; posTexY=0;
        for (int i=0;i<TOTAL_GHOST-1;++i) {
            ghost[i][UP][0]={posTexX, posTexY, 30, 30} ; posTexX+=31 ;
            ghost[i][UP][1]={posTexX, posTexY, 30, 30} ; posTexX+=31 ;
            ghost[i][DOWN][0]={posTexX, posTexY, 30, 30} ; posTexX+=31 ;
            ghost[i][DOWN][1]={posTexX, posTexY, 30, 30} ; posTexX+=31 ;
            ghost[i][LEFT][0]={posTexX, posTexY, 30, 30} ; posTexX+=31 ;
            ghost[i][LEFT][1]={posTexX, posTexY, 30, 30} ; posTexX+=31 ;
            ghost[i][RIGHT][0]={posTexX, posTexY, 30, 30} ; posTexX+=31 ;
            ghost[i][RIGHT][1]={posTexX, posTexY, 30, 30} ; posTexX+=31 ;
            ghost[i][FRIGHTEN_GHOST_1][0]={posTexX, 31, 30, 30} ; posTexX+=31 ;
            ghost[i][FRIGHTEN_GHOST_1][1] = {posTexX, 31, 30, 30} ; posTexX+=31 ;
            ghost[i][FRIGHTEN_GHOST_2][0]={posTexX, 31, 30, 30} ; posTexX+=31 ;
            ghost[i][FRIGHTEN_GHOST_2][1]={posTexX, 31, 30, 30} ; posTexX=0  ;
            posTexY+=31 ;
            if (i==3) posTexY+=31 ;
        }
        posTexX = 248 ; posTexY=62 ;
        ghost[GHOST_SPIRIT][UP][0]={posTexX, posTexY, 30, 30} ;
        ghost[GHOST_SPIRIT][UP][1]={posTexX, 30, 30, 30} ; posTexX+=31 ;
        ghost[GHOST_SPIRIT][DOWN][0]={posTexX, 30, 30, 30} ;
        ghost[GHOST_SPIRIT][DOWN][1]={posTexX, 30, 30, 30} ; posTexX=248 ; posTexY+=31 ;
        ghost[GHOST_SPIRIT][LEFT][0]={posTexX, posTexY, 30, 30} ;
        ghost[GHOST_SPIRIT][LEFT][1]={posTexX, 30, 30, 30} ; posTexX+=31 ;
        ghost[GHOST_SPIRIT][RIGHT][0]={posTexX, 30, 30, 30} ;
        ghost[GHOST_SPIRIT][RIGHT][1]={posTexX, 30, 30, 30} ; posTexX=posTexY=0 ;
        SDL_FreeSurface(Image);
        Image = IMG_Load("Assets/Images/GhostScore.png");
        ghostScore=SDL_CreateTextureFromSurface(renderer, Image) ;
        Console->Status("Loaded Ghost Texture");
    }
    SDL_FreeSurface(Image);
    Image = nullptr;
}

void TextureSrc::renderPacmanTexture(SDL_Renderer *&renderer, int posX, int posY, int status) {
    SDL_Rect srcRect, dsRect ;
    dsRect={posX-7+217, posY-7, 30 ,30};
    ++pacmanFrame ;
    if (status!=DEAD_PACMAN&&pacmanFrame==30) pacmanFrame=0 ;
    switch (status) {
        case -1:
            srcRect=pacmanUp[0] ; break;
        case UP :
            srcRect=pacmanRight[pacmanFrame/10] ; break;
        case DOWN :
            srcRect=pacmanDown[pacmanFrame/10] ; break;
        case LEFT :
            srcRect=pacmanLeft[pacmanFrame/10] ; break;
        case RIGHT :
            srcRect=pacmanRight[pacmanFrame/10] ; break;
        case DEAD_PACMAN :
            srcRect=pacmanDEAD[pacmanFrame/10] ; break;
    }
    SDL_RenderCopy(renderer,entityTexture,&srcRect,&dsRect);
}

void TextureSrc::renderGhostTexture(SDL_Renderer *&renderer, int posX, int posY, int ghostID, int status) {
    SDL_Rect srcRect, dsRect ;
    dsRect={posX-7+217, posY-7, 30 ,30};
    ++ghostFrame[ghostID] ;
    if (ghostFrame[ghostID]==14) ghostFrame[ghostID]=0;
    switch (status) {
        case UP:
            srcRect=ghost[ghostID][UP][ghostFrame[ghostID]/7] ; break;
        case RIGHT:
            srcRect=ghost[ghostID][RIGHT][ghostFrame[ghostID]%7] ; break;
        case DOWN:
            srcRect=ghost[ghostID][DOWN][ghostFrame[ghostID]%7] ; break ;
        case LEFT:
            srcRect=ghost[ghostID][LEFT][ghostFrame[ghostID]%7] ; break;
        case FRIGHTEN_GHOST_1:
            srcRect=ghost[ghostID][FRIGHTEN_GHOST_1][ghostFrame[ghostID]/7] ; break;
        case FRIGHTEN_GHOST_2:
            if (ghostFrame[ghostID]/7==0) srcRect=ghost[ghostID][FRIGHTEN_GHOST_1][ghostFrame[ghostID]%7] ;
            else srcRect=ghost[ghostID][FRIGHTEN_GHOST_2][ghostFrame[ghostID]%7] ;
            break ;
    }
    SDL_RenderCopy(renderer,entityTexture,&srcRect,&dsRect);
}


