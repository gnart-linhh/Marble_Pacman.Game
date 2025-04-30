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

void Base::handleEvent(SDL_Event& e) {
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

void Base::render(SDL_Renderer *renderer,const std::vector<std::string> &scoreData) {
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
            objectTexture->renderPacmanTexture(renderer, pacman->getPosX(), pacman->getPosY(), dir) ;
        }
        else {
            if (objectTexture->pacmanIsDead()) {
                if (game->getRemainLife()>0) respawnObject() ;
                else {
                    runningEGBoard = true ;
                    game->checkScoreData(scoreData) ;
                }
            }
            else objectTexture->renderPacmanTexture(renderer, pacman->getPosX(), pacman->getPosY(), TextureSrc::DEAD_PACMAN) ;
        }
        game->renderHUD(renderer) ;
    }
}

void Base::pacmanMeatGhost(Ghost *&ghost) {
    if (ghost->isDead()) return  ;
    int distance=(pacman->getPosX()-ghost->getPosX())*(pacman->getPosX()-ghost->getPosX())+(pacman->getPosY()-ghost->getPosY())*(pacman->getPosY()-ghost->getPosY()) ;
    if (distance<=9) {
        if (ghost->isFrighten()) {
            game->eatGhost(ghost->getPosX(),ghost->getPosY()) ;
            ghost->setDead(true) ;
            ghost->setFrighten(false) ;
        }
        else {
            pacman->setDead(true,1) ;
            game->lostALife() ;
            control->pauseTick(true) ;
        }
    }
}

void Base::ghostMove(Ghost* &ghost) {
    if (ghost==nullptr) return ;
    int  ghostTileX=ghost->getTileX() ;
    int  ghostTileY=ghost->getTileY() ;
    int  ghostPosX=ghost->getPosX() ;
    int  ghostPosY=ghost->getPosY() ;
    int ghostOldDir=ghost->getGhostDir() ;
    int ghostNextTileX=ghost->getNextTileX() ;
    int ghostNextTileY=ghost->getNextTileY() ;

    if (ghostTileX*16==ghostPosX&&ghostTileY*16==ghostPosY) {
        if (map->iscrossRoad(ghostTileX, ghostTileY)) {
            if (ghost->isFrighten()) {
                // if frighten
                std::stack<int> whichDir ;
                if (ghostOldDir%2==1) { // left/right
                    if (map->canChangeDir(ghostTileX, ghostTileY, Map::UP)) whichDir.push(0) ;
                    if (map->canChangeDir(ghostTileX, ghostTileY, Map::DOWN)) whichDir.push(2) ;
                    if (map->canChangeDir(ghostTileX, ghostTileY, ghostOldDir)) whichDir.push(ghostOldDir) ;
                }
                else {
                    if (map->canChangeDir(ghostTileX, ghostTileY, Map::LEFT)) whichDir.push(3) ;
                    if (map->canChangeDir(ghostTileX, ghostTileY, Map::RIGHT)) whichDir.push(1) ;
                    if (map->canChangeDir(ghostTileX, ghostTileY, ghostOldDir)) whichDir.push(ghostOldDir) ;
                }
                int dir=rand()%(int) whichDir.size() +1;
                while (dir>1) {
                    whichDir.pop() ;
                    --dir ;
                }
                ghost->setDir(whichDir.top()) ;
                while (!whichDir.empty()) whichDir.pop() ;
            }
            else { // if not frighten -> choose min dir
                int distanceUP, distanceDOWN, distanceLEFT, distanceRIGHT ;
                distanceUP=distanceDOWN=distanceLEFT=distanceRIGHT=1e9 ;
                if (map->canChangeDir(ghostTileX, ghostTileY, Map::UP)) {
                    distanceUP=map->getDist(p(ghostTileX,ghostTileY-1),p(ghostNextTileX,ghostNextTileY),Map::UP) ;
                }
                if (map->canChangeDir(ghostTileX, ghostTileY, Map::DOWN)) {
                    distanceDOWN=map->getDist(p(ghostTileX,ghostTileY+1),p(ghostNextTileX,ghostNextTileY),Map::DOWN) ;
                }
                if (map->canChangeDir(ghostTileX, ghostTileY, Map::LEFT)) {
                    distanceLEFT=map->getDist(p(ghostTileX-1,ghostTileY),p(ghostNextTileX,ghostNextTileY),Map::LEFT) ;
                }
                if (map->canChangeDir(ghostTileX, ghostTileY, Map::RIGHT)) {
                    distanceRIGHT=map->getDist(p(ghostTileX+1, ghostTileY),p(ghostNextTileX,ghostNextTileY),Map::RIGHT) ;
                }

                int distanceMIN ;
                if (ghostOldDir==Map::UP) {
                    distanceMIN=std::min(distanceUP,std::min(distanceRIGHT, distanceLEFT)) ;
                    if (distanceMIN==distanceUP) ghost->setDir(Map::UP) ;
                    else if (distanceMIN==distanceRIGHT) ghost->setDir(Map::RIGHT) ;
                    else ghost->setDir(Map::LEFT) ;
                }
                else if (ghostOldDir==Map::DOWN) {
                    distanceMIN=std::min(distanceDOWN, std::min(distanceLEFT, distanceRIGHT)) ;
                    if (distanceMIN==distanceDOWN) ghost->setDir(Map::DOWN) ;
                    else if (distanceMIN==distanceLEFT) ghost->setDir(Map::LEFT) ;
                    else ghost->setDir(Map::RIGHT) ;
                }
                else if (ghostOldDir==Map::LEFT) {
                    distanceMIN=std::min(distanceLEFT, std::min(distanceUP, distanceDOWN)) ;
                    if (distanceMIN==distanceLEFT) ghost->setDir(Map::LEFT) ;
                    else if (distanceMIN==distanceUP) ghost->setDir(Map::UP) ;
                    else ghost->setDir(Map::DOWN) ;
                }
                else {
                    distanceMIN=std::min(distanceRIGHT, std::min(distanceDOWN, distanceUP)) ;
                    if (distanceMIN == distanceRIGHT) ghost->setDir(Map::RIGHT);
                    else if (distanceMIN == distanceDOWN) ghost->setDir(Map::DOWN);
                    else ghost->setDir(Map::UP);
                }
            }
        }
        if (map->canChangeDir(ghostTileX, ghostTileY, ghost->getGhostDir())) ghost->moving() ;
    }
    else {
        // khong nam tron trong 1 tile
        if (map->canChangeDir(ghostTileX, ghostTileY, ghost->getGhostDir())) ghost->moving() ;
        else {
            if (ghostTileX*16==ghostPosX&&ghostTileY*16!=ghostPosY&&ghost->getGhostDir()%2==0) ghost->moving() ;
            else if (ghostTileX*16!=ghostPosX&&ghostTileY*16==ghostPosY&&ghost->getGhostDir()%2==1) ghost->moving() ;
        }
    }
    ghost->goThroughTunnel() ;
    if (ghostPosX==ghostNextTileX*16&&ghostPosY==ghostNextTileY*16) {
        if (ghost->isDead()) {
            ghost->setDead(false) ;
        }
    }
    pacmanMeatGhost(ghost) ;
}


void Base::loop(bool &exitToMenu) {
    if (game->clearAllCoins()) { // an het so coin
        if (waitTime>0) --waitTime ;
        else {
            game->nextLevel() ;
            respawnObject() ;
            map->reset() ;
        }
        return ;
    }
    if (pacman->isDead()) {
        if (runningEGBoard) {
            switch (game->getPlayerDecision()) {
                case Game::AGAIN:
                    newGame() ;
                    break ;
                case Game::QUIT:
                    exitToMenu = true ;
                    break ;
            }
        }
        return ;
    }
    int pacmanTileX=pacman->getTileX() ;
    int pacmanTileY=pacman->getTileY() ;
    int pacmanPosX=pacman->getPosX() ;
    int pacmanPosY=pacman->getPosY() ;
    int lastDir=-1 ;
    if (!pacman->emptyDirStack()) lastDir=pacman->getDir() ;
    if (!pacman->isDead()&&lastDir!=-1) {
        if (pacmanTileX*16==pacmanPosX&&pacmanTileY*16==pacmanPosY) {
            if (map->iscrossRoad(pacmanTileX,pacmanTileY)) {
                if (!pacman->emtySpecial()&&pacman->getSpecial()==p(pacmanTileX,pacmanTileY)) pacman->turn() ;
            }
            if (map->canChangeDir(pacmanTileX, pacmanTileY, pacman->getDir())) pacman->moving() ;
            else pacman->stopmoving() ;
        }
        else {
            if (map->canChangeDir(pacmanTileX, pacmanTileY, lastDir)) pacman->moving() ;
            else {
                if (pacmanTileX*16==pacmanPosX&&pacmanTileY*16!=pacmanPosY) pacman->moving() ;
                else if (pacmanTileX*16!=pacmanPosX&&pacmanTileY*16==pacmanTileY) pacman->moving() ;
                else pacman->stopmoving() ;
            }
        }
    }
    int remainCoin=game->getRemainCoin() ;
    pacmanTileX=pacman->getTileX() ;
    pacmanTileY=pacman->getTileY() ;
    int typeOfCoin=map->eatCoins(pacmanTileX,pacmanTileY) ;
    if (typeOfCoin!=Game::notCoin) {
        game->eatCoin(typeOfCoin) ;
        if (typeOfCoin==Game::superCoin) {
            if (!blinky->isDead()) blinky->setFrighten(true) ;
            if (!pinky->isDead()) pinky->setFrighten(true) ;
            if (!inky->isDead()) inky->setFrighten(true) ;
            if (!clyde->isDead()) clyde->setFrighten(true) ;
        }
    }
    if (!control->isFrightenTime()) {
        blinky->setFrighten(false ) ;
        pinky->setFrighten(false ) ;
        inky->setFrighten(false ) ;
        clyde->setFrighten(false ) ;
    }
    bool scatter=control->isScatteringTime() ;
    blinky->setFrighten(scatter ) ;
    pinky->setFrighten(scatter ) ;
    inky->setFrighten(scatter ) ;
    clyde->setFrighten(scatter ) ;

    pacmanPosX=pacman->getPosX() ;
    pacmanPosY=pacman->getPosY() ;
    lastDir=-1 ;
    if (!pacman->emptyDirStack()) lastDir=pacman->getDir() ;

    if (!pacman->isDead()) {
        control->pauseTick((false )) ;
        if (blinky->isDead()) blinky->setDestination(13,11) ;
        else if (!blinky->isScattering())
            blinky->setDestination(pacmanTileX,pacmanTileY) ; // đuổi pacman
        else blinky->setDestination(Ghost::DEFAULT_BLINKY_TILE_X,Ghost::BLINKY_START_TILE_Y) ; // đi về góc mặc định

        if (pinky->isDead()) pinky->setDestination(13,11) ;
        else if (!pinky->isScattering()) {
            // dựa vào hướng đang đi để chặn đầu
            switch (lastDir) {
                case Map::UP :
                    pinky->setDestination(pacmanTileX,pacmanTileY-4) ; break ;
                case Map::DOWN :
                    pinky->setDestination(pacmanTileX,pacmanTileY+4) ; break ;
                case Map::LEFT :
                    pinky->setDestination(pacmanTileX-4,pacmanTileY) ; break ;
                case Map::RIGHT :
                    pinky->setDestination(pacmanTileX+4,pacmanTileY) ; break ;
            }
        }
        else pinky->setDestination(Ghost::DEFAULT_PINKY_TILE_X, Ghost::DEFAULT_PINKY_TILE_Y) ;

        if (inky->isDead()) inky->setDestination(13,11) ;
        else if (!inky->isScattering())
            // dựa vào pos pacman và blinky
            inky->setDestination(2*pacmanTileX-blinky->getTileX(),2*pacmanTileY-blinky->getTileY()) ;
        else inky->setDestination(Ghost::DEFAULT_INKY_TILE_X,Ghost::DEFAULT_INKY_TILE_Y) ;

        if (clyde->isDead())
            clyde->setDestination(13,11) ;
        else if (!clyde->isScattering()) {
            // gần chạy xa đuổi
            if ((pacmanTileX-clyde->getTileX())*(pacmanTileX-clyde->getTileX())+(pacmanTileY-clyde->getTileY())*(pacmanTileY-clyde->getTileY())<=64)
                clyde->setDestination(Ghost::DEFAULT_CLYDE_TILE_X,Ghost::DEFAULT_CLYDE_TILE_Y) ;
            else
                clyde->setDestination(pacmanTileX, pacmanTileY) ;
        }
        else clyde->setDestination(Ghost::DEFAULT_PINKY_TILE_X, Ghost::DEFAULT_PINKY_TILE_Y) ;
    }

    pacman->goThroughTunnel() ;
    ghostMove(blinky) ;
    ghostMove(pinky) ;
    ghostMove(inky) ;
    ghostMove(clyde) ;

    game->handleGhostPos(pinky,inky,clyde) ;
    if (game->clearAllCoins()) {
        waitTime=100 ;
    }
}
