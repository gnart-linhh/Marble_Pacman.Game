//
// Created by Nguyễn Trang Linh on 25/4/25.
//
#include "Base.h"
#include <random>

typedef std::pair<int, int> p  ;
typedef std::pair<int, std::pair<int ,int>> IP ;

void Base::init(SDL_Renderer* renderer) {
    map= new Map();
    objectTexture=new TextureSrc() ;
    objectTexture->loadTileTexture(renderer) ;
    objectTexture->loadPacmanAndGhostTexture(renderer) ;
}

void Base::newGame() {
    map->reset() ;
    delete pacman; pacman= new Pacman() ;
    delete blinky ; blinky=new Ghost(13, 11, false) ;
    delete pinky ; pinky= new Ghost(13, 14, true) ;
    delete inky ; inky= new Ghost(11, 14, true) ;
    delete clyde ; clyde= new Ghost(15, 14, true) ;
}

void Base::respawnObject() {
    delete pacman; pacman= new Pacman() ;
    delete blinky ; blinky=new Ghost(13, 11, false) ;
    delete pinky ; pinky= new Ghost(13, 14, true) ;
    delete inky ; inky= new Ghost(11, 14, true) ;
    delete clyde ; clyde= new Ghost(15, 14, true) ;
}

void Base::handleEvent(SDL_Event& e, std::vector<std::string> &scoreData) {
    if (e.type==SDL_KEYDOWN) {
        if (e.key.keysym.sym==SDLK_w||e.key.keysym.sym==SDLK_a
            ||e.key.keysym.sym==SDLK_s||e.key.keysym.sym==SDLK_d) {
            int newDir=-1 ;
            int lastDir=-1 ;
            int pacmanTileX=pacman->getTileX() ;
            int pacmanTileY=pacman->getTileY() ;
            int pacmanPosX=pacman->getPosX() ;
            int pacmanPosY=pacman->getPosY() ;

            if (!pacman->emptyDirStack()) lastDir=pacman->getDir() ;

            if (e.key.keysym.sym==SDLK_w) newDir=0 ;//UP
            if (e.key.keysym.sym==SDLK_a) newDir=3 ; //LEFT
            if (e.key.keysym.sym==SDLK_s) newDir=2 ; // DOWN
            if (e.key.keysym.sym==SDLK_d) newDir=1 ; //RIGHT

            if (lastDir==-1) {
                if (map->canChangeDir(pacmanTileX,pacmanTileY,newDir)) {
                    pacman->eraseSpecial() ;
                    pacman->pushtoStack(newDir) ;
                }
            }
            else {
                if (newDir%2==lastDir%2) {
                    if (map->canChangeDir(pacmanTileX,pacmanTileY,newDir)) {
                        pacman->pushtoStack(newDir) ;
                        pacman->eraseSpecial() ;
                    }
                }
                else {
                    std::pair<int, int> nextCross=map->getnextCrossID(pacmanTileX, pacmanTileY, lastDir) ;
                    if (lastDir%2==1&&newDir%2==0) { // từ ngang sang dọc
                        if (pacmanPosY==pacmanTileY*16) {  // nằm chính xác ở dòng ô vuông
                            if (map->canChangeDir(pacmanTileX,pacmanTileY,newDir)) {
                                pacman->pushSpecialStack(newDir, p(pacmanTileX, pacmanTileY)) ;
                            }
                            else if (nextCross!=p(-1,-1)&&!map->besideCrossIsWall(nextCross,newDir)&&abs(pacmanPosX-nextCross.first*16)<=32) {
                                // có giao lộ, không phải tường, khoảng cách đến đó không quá 2 ô
                                pacman->pushSpecialStack(newDir, nextCross) ;
                            }
                        }
                    }
                    else if (lastDir%2==0&&newDir%2==1) { // từ dọc sang ngang
                        if (pacmanPosX==pacmanTileX*16) {
                            if (map->canChangeDir(pacmanTileX,pacmanTileY,newDir)) {
                                pacman->pushSpecialStack(newDir, p(pacmanTileX, pacmanTileY)) ;
                            }
                            else if (nextCross!=p(-1,-1)&&!map->besideCrossIsWall(nextCross,newDir)&&abs(pacmanPosY-nextCross.second*16)<=32) {
                                pacman->pushSpecialStack(newDir, nextCross) ;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Base::renderGhost(SDL_Renderer *renderer, Ghost* &ghost, int ghostID) {
    if (ghost==nullptr) return  ;
    if (ghost->isDead())
        objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), TextureSrc::GHOST_SPIRIT, ghost->getGhostDir()) ;
    else if (ghost->isFrighten()) {
        if (control->remainFrightenTime()<2.0)
            objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), ghostID, TextureSrc::FRIGHTEN_GHOST_2);
        else
            objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), ghostID, TextureSrc::FRIGHTEN_GHOST_1);
    }
    else
        objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), ghostID, ghost->getGhostDir()) ;
}

void Base::render(SDL_Renderer *renderer, const std::vector<std::string> &scoreData) {
    SDL_Rect dsRect ;
    for (int i=0;i<28;++i) {
        for (int j=0;j<31;++j) {
            dsRect={i*16+217,j*16,16,16} ;
            objectTexture->renderTileTexture(renderer, map->getTileID(i,j),&dsRect) ;
        }
    }
    if (!runningEGBoard) {
        int dir=-1 ;
        if (!pacman->emptyDirStack()) dir=pacman->getDir() ;
        if (!pacman->isDead()) {
            renderGhost(renderer, blinky, TextureSrc::BLINKY) ;
            renderGhost(renderer, pinky, TextureSrc::PINKY) ;
            renderGhost(renderer, inky, TextureSrc::INKY) ;
            renderGhost(renderer, clyde, TextureSrc::CLYDE) ;
        }
        else {
            if (objectTexture->pacmanIsDead()) {

            }
        }
    }
}

