//
// Created by Nguyễn Trang Linh on 19/3/25.
//
#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "Ghost.h"
#include "TextManager.h"
#include "Button.h"

class Game {
    public:
        const int TOTAL_COINS=244 ;
        static const int normalCoin=26 ;
        static const int superCoin=27 ;
        static const int notCoin=0 ;
        static const int pauseGame=1 ;
        static const int AGAIN=2 ;
        static const int QUIT=3 ;
        static const int WAITING=4 ;
        Game(SDL_Renderer* renderer);
        ~Game();
        void reset() ;
        void nextLevel() ;
        void eatCoin(const int typeOfCoin) ;
        void eatGhost(const int ghostTileX, const int ghostTileY) ;
        void lostALife() ;
        int getEatenGhostStreak() const ;
        int getEatenGhostPosX() const ;
        int getEatenGhostPosY() const ;
        int getRemainLife() const  ;
        bool clearAllCoins() const ;
        int getLevel() const ;
        int getPlayerDecision() const ;
        int getRemainCoin() const ;
        void handleGhostPos(Ghost* pinky, Ghost* &inky, Ghost* &clyde) ;
        void handleEGBoard(SDL_Event* e, std::vector <std::string>& scoreData) ;
        void renderHUD(SDL_Renderer* &renderer) ;
        void runEGBoard(SDL_Renderer* &renderer) ;
        void checkScoreData(const std::vector<std::string> &scoreData);
    private:
        int level ;
        int life ;
        int eatenCoins;
        int eatenGhost ;
        int scores ;
        int pos=-1 ;
        std::string playername="" ;
        int playerDecision ;
        int currentButton ;
        int ghostEatenPosX ;
        int ghostEatenPosY ;
        int PINKY_COIN_LIMIT ;
        int INKY_COIN_LIMIT ;
        int CLYDE_COIN_LIMIT ;
        TextManager* levelText ;
        TextManager* scoreText ;
        TextManager* liveText ;
        TextManager* playerName ;
        SDL_Texture* endGameBoard ;
        SDL_Texture* hightScoreBoard ;
        Button* yesButton ;
        Button* noButton ;
        bool newRecord=false ;
    protected:
        SDL_Texture* loadImage(SDL_Renderer* &renderer,const std::string imgPath ) ;
};

#endif //GAME_H
