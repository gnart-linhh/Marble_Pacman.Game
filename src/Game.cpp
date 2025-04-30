//
// Created by Nguyễn Trang Linh on 19/3/25.
//
#include "Game.h"
#include <iostream>
#include <vector>
#include <string>

Game::Game(SDL_Renderer *renderer) {
    level=1 ;
    life=3 ;
    scores=0 ;
    eatenCoins=0 ;
    eatenGhost=-1;
    playername="Unnamed";
    playerDecision=WAITING ;
    currentButton=1 ;
    PINKY_COIN_LIMIT=5 ; // ăn được 5 coin thì mới được thả
    INKY_COIN_LIMIT=30 ;
    CLYDE_COIN_LIMIT=90 ;
    liveText=new TextManager(28) ;
    liveText->loadRenderText(renderer, "Lives: 3 ", {255, 255, 255, 255}) ;
    scoreText=new TextManager(28) ;
    scoreText->loadRenderText(renderer, "Scores: 0", {255, 255, 255, 255}) ;
    levelText=new TextManager(28) ;
    levelText->loadRenderText(renderer, "Level: 1", {255, 255, 255, 255}) ;
    playerName=new TextManager(20) ;
    playerName->loadRenderText(renderer, playername.c_str(), {255, 255, 255, 255}) ;


}

void Game::reset() {
    level=1 ;
    life=3 ;
    scores=0 ;
    eatenCoins=0 ;
    eatenGhost=-1 ;
    currentButton=1 ;
    PINKY_COIN_LIMIT=5 ;
    INKY_COIN_LIMIT=30 ;
    CLYDE_COIN_LIMIT=90 ;
    playerDecision=WAITING ;
    pos=-1 ;

}


Game::~Game() {
    delete liveText; liveText=nullptr ;
    delete scoreText; scoreText=nullptr ;
    delete levelText; levelText=nullptr ;
    delete playerName; playerName=nullptr ;
}

SDL_Texture *Game::loadImage(SDL_Renderer *&renderer, const std::string imgPath) {
    SDL_Surface* Image=IMG_Load(imgPath.c_str());
    SDL_Texture* loadTexture=SDL_CreateTextureFromSurface(renderer, Image);
    SDL_FreeSurface(Image);
    return loadTexture ;
}

void Game::eatCoin(const int typeOfCoin) {
    ++eatenCoins ;
    if(typeOfCoin==normalCoin) scores+=10 ;
    else if (typeOfCoin==superCoin) {
        eatenGhost=-1 ; // reset lại chuỗi đớp ghost
        scores+=50 ;
    }
}

void Game::eatGhost(const int ghostPosX, const int ghostPosY) {
    ++eatenGhost ;
    eatenGhost=eatenGhost%4 ;
    switch (eatenGhost) {
        case 0 :
            scores+=200 ; break ;
        case 1 :
            scores+=400 ; break ;
        case 2 :
            scores+=800 ; break ;
        case 3 :
            scores+=1600 ; break ;
    }
    ghostEatenPosX=ghostPosX;
    ghostEatenPosY=ghostPosY;
}

void Game::lostALife() {
    --life ;
}

int Game::getEatenGhostStreak() const {
    return eatenGhost ;
}

int Game::getEatenGhostPosX() const {
    return ghostEatenPosX ;
}

int Game::getEatenGhostPosY() const {
    return ghostEatenPosY ;
}

int Game::getRemainLife() const {
    return life ;
}

int Game::getRemainCoin() const {
    return TOTAL_COINS-eatenCoins ;
}

void Game::nextLevel() {
    ++level ;
    eatenCoins=0 ;
    eatenGhost=-1 ;
    currentButton=1 ;
    playerDecision=WAITING ;
    if (level<=3) {
        PINKY_COIN_LIMIT=5 ;
        INKY_COIN_LIMIT=30 ;
        CLYDE_COIN_LIMIT=90 ;
    }
    else {
        PINKY_COIN_LIMIT=0 ;
        INKY_COIN_LIMIT=5 ;
        CLYDE_COIN_LIMIT=10 ;
    }
}

bool Game::clearAllCoins() const {
    return eatenCoins==TOTAL_COINS ;
}

int Game::getLevel() const {
    return level ;
}

void Game::checkScoreData(const std::vector<std::string> &scoreData) {
    for (int i = 0; i < scoreData.size(); ++i) {
        int t = 0;
        int j = 0;
        while (j< scoreData.at(i).length()  && scoreData.at(i).at(j) != ':') ++j;
        j += 2; // skip :
        while (j < scoreData.at(i).length())
            t = t * 10 + scoreData.at(i).at(j) - '0',
            ++j;
        if (scores > t) {
            newRecord=true ;
            SDL_StartTextInput();
            pos = i;
            break;
        }
    }
    // dùng at thay vì [] do bị lỗi gì ý huhu
}

void Game::renderHUD(SDL_Renderer *&renderer) {
    levelText->loadRenderText(renderer, "Level: "+ std::to_string(level),{255, 255, 255, 255}) ;
    levelText->renderText(renderer, 0, 0, TextManager::LEFT ) ;
    liveText->loadRenderText(renderer, " Life: "+ std::to_string(life),{255, 255, 255, 255}) ;
    liveText->renderText(renderer,0, 50, TextManager::LEFT ) ;
    scoreText->loadRenderText(renderer, "Scores: "+ std::to_string(scores),{255, 255, 255, 255}) ;
    scoreText->renderText(renderer, 0, 100, TextManager::LEFT ) ;
}

int Game::getPlayerDecision() const {
    return playerDecision ;
}

void Game::handleGhostPos(Ghost *pinky, Ghost *&inky, Ghost *&clyde) {
    if (pinky->isInCage()&&eatenCoins>=PINKY_COIN_LIMIT) pinky->repawn(Ghost::GHOST_START_TILE_X, Ghost::GHOST_START_TILE_Y, false) ;
    if (inky->isInCage()&&eatenCoins>=INKY_COIN_LIMIT) inky->repawn(Ghost::GHOST_START_TILE_X, Ghost::GHOST_START_TILE_Y, false) ;
    if (clyde->isInCage()&&eatenCoins>=CLYDE_COIN_LIMIT) clyde->repawn(Ghost::GHOST_START_TILE_X, Ghost::GHOST_START_TILE_Y, false) ;
}













