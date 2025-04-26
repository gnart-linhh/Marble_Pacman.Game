//
// Created by Nguyễn Trang Linh on 21/4/25.
//

#ifndef PACMAN_H
#define PACMAN_H

#include "Object.h"
#include <stack>

class Pacman : public Object {
    public:
        static const int pacmanVelocity=2 ;
        static const int PACMAN_START_TILE_X=13 ;
        static const int PACMAN_START_TILE_Y=23 ;
        Pacman() ;
        ~Pacman() {
            while (!Direction.empty()) Direction.pop() ;
        }
        bool emptyDirStack() {
            return Direction.empty() ;
        }
        void pushtoStack(int newDir) ;
        int getDir() const {
            return Direction.top();
        }
        void moving() ;
        void stopmoving() ;
        void turn() ;
        void respawn() {
            resetObjectTile(PACMAN_START_TILE_X, PACMAN_START_TILE_Y) ;
            while (!Direction.empty()) Direction.pop() ;
        }// hồi sinh
        bool emtySpecial() {
            return Special.empty() ;
        }
        void pushSpecialStack(int newDir, std::pair<int,int> nextCross) ;
        std::pair<int, int> getSpecial() {
            return Special.top().second ;
        }
        void eraseSpecial()  ;
    private:
        std::stack<int> Direction ;
        std::stack<std::pair<int, std::pair<int,int>>> Special ;
} ;

#endif //PACMAN_H
