//
// Created by Nguyễn Trang Linh on 17/4/25.
//
#include "Map.h"
#include <queue>
#include <SDL_rect.h>

typedef std::pair<int,int> p ;

bool firstInit=true ;
int premanMap[31][28] ;
int color [31][28] ;

Map::Map() {
    if (firstInit) {
        std::ifstream file("map.txt");
        if (file) {
            for (int i=0;i<MAP_HEIGHT;++i) {
                for (int j=0;j<MAP_WIDTH;++j) {
                    file>>premanMap[i][j] ;
                    if (premanMap[i][j]>31||premanMap[i][j]<0) {
                        Console->Status("Wrong Tile") ;
                        return ;
                    }
                }
            }
            Console->Status("Map Loaded") ;
        }
        else Console -> Status("Error reading file") ;
    }
    for (int i=0;i<MAP_HEIGHT;++i) {
        for (int j=0;j<MAP_WIDTH;++j) {
            tile[i][j]=premanMap[i][j];
        }
    }
    findingCrossRoad() ;
    NextCrossTileID() ;
    calculateDistance() ;
}

void Map::findingCrossRoad() {
    for (int x=0;x<MAP_WIDTH;++x) {
        for (int y=0;y<MAP_HEIGHT;++y) {
            for (int dir=0;dir<4;++dir) markCross[y][x][dir]=false  ;
            if (tile[y][x]!=26&&tile[y][x]!=27&&tile[y][x]!=30) continue ;
            if (y>0&&(tile[y-1][x]==26||tile[y-1][x]==27||tile[y-1][x]==30)) markCross[y][x][0]=true  ;
            if (y<30&&(tile[y+1][x]==26||tile[y+1][x]==27||tile[y+1][x]==30)) markCross[y][x][2]=true ;
            if (x>0&&(tile[y][x-1]==26||tile[y][x-1]==27||tile[y][x-1]==30)) markCross[y][x][3]=true ;
            if (x<27&&(tile[y][x+1]==26||tile[y][x+1]==27||tile[y][x+1]==30)) markCross[y][x][1]=true ;
        }
    }
}

int Map::getTileID(int x, int y) {
    return tile[x][y] ;
}
void Map::NextCrossTileID() {

}
void Map::calculateDistance() {

}
void Map::reset() {
    for (int i=0;i<MAP_HEIGHT;++i) {
        for (int j=0;j<MAP_WIDTH;++j) {
            tile[i][j]=premanMap[i][j];
        }
    }
}

