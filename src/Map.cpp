//
// Created by Nguyễn Trang Linh on 17/4/25.
//
#include "Map.h"
#include <queue>

typedef std::pair<int,int> p ;

bool firstInit=true ;
int premanMap[31][28] ;
int color [31][28] ;

Map::Map() {
    if (firstInit) {
        std::ifstream file(mapFile);
        if (file) {
            for (int i=0;i<MAP_HEIGHT;++i) {
                for (int j=0;j<MAP_WIDTH;++j) {
                    file>>premanMap[i][j] ;
                    if (premanMap[i][j]>35||premanMap[i][j]<0) {
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
            if (y>0&&(tile[y-1][x]==26||tile[y-1][x]==27||tile[y-1][x]==30)) markCross[y][x][UP]=true  ; //co the di len
            if (y<30&&(tile[y+1][x]==26||tile[y+1][x]==27||tile[y+1][x]==30)) markCross[y][x][DOWN]=true ; // co the di xuong
            if (x>0&&(tile[y][x-1]==26||tile[y][x-1]==27||tile[y][x-1]==30)) markCross[y][x][LEFT]=true ; // co the di trai
            if (x<27&&(tile[y][x+1]==26||tile[y][x+1]==27||tile[y][x+1]==30)) markCross[y][x][RIGHT]=true ; // co the di phai
        }
    }
}

bool Map::isWall(std::pair<int, int> tileID) {
    if (tileID==p(0,14)||tileID==p(27,14)) return false ;
    if (tileID.first<0||tileID.first>26) return true ;
    if (tileID.second<0||tileID.second>29) return true ;
    return (tile[tileID.second][tileID.first]!=26&&tile[tileID.second][tileID.first]!=27&&tile[tileID.second][tileID.first]!=30) ;
}

bool Map::iscrossRoad(int y, int x) {
    int cnt=0 ;
    if (markCross[y][x][UP]) cnt++ ;
    if (markCross[y][x][DOWN]) cnt++ ;
    if (markCross[y][x][LEFT]) cnt++ ;
    if (markCross[y][x][RIGHT]) cnt++ ;
    if (cnt>=3) return true ;
    if (cnt==2) {
        if (markCross[y][x][UP]&&markCross[y][x][DOWN]) return false ;
        if (markCross[y][x][LEFT]&&markCross[y][x][RIGHT]) return false ;
        return true ;
    }
    return false ;
}


void Map::NextCrossTileID() {
    for (int y=0 ;y<MAP_HEIGHT;++y) {
        nextCrossID[y][0][LEFT]=p(-1,-1) ;
        for (int x=1;x<MAP_WIDTH;++x) {
            nextCrossID[y][x][LEFT]=p(-1,-1) ;
            if (!isWall(std::pair<int,int> (x,y))) {
                if (nextCrossID[y][x-1][LEFT]!=p(-1,-1)) nextCrossID[y][x][LEFT]=nextCrossID[y][x-1][LEFT] ; // luu thong tin giao lo phia truoc do
                if (iscrossRoad(y,x-1)) nextCrossID[y][x][LEFT]=p(x-1,y) ; // neu dung thi ke thua
            }
        }
        nextCrossID[y][MAP_WIDTH-1][RIGHT]=p(-1,-1) ;
        for (int x=MAP_WIDTH-1;x>=0;--x) {
            nextCrossID[y][x][RIGHT]=p(-1,-1) ;
            if (!isWall(std::pair<int,int> (x,y))) {
                if (nextCrossID[y][x+1][RIGHT]!=p(-1,-1)) nextCrossID[y][x][RIGHT]=nextCrossID[y][x+1][RIGHT] ;
                if (iscrossRoad(y,x+1)) nextCrossID[y][x][RIGHT]=p(x+1,y) ;
            }
        }
    }
    for (int x=0;x<MAP_WIDTH;++x) {
        nextCrossID[0][x][UP]=p(-1,-1) ;
        for (int y=1;y<MAP_HEIGHT;++y) {
            nextCrossID[y][x][UP]=p(-1,-1) ;
            if (!isWall(std::pair<int,int> (x,y))) {
                if (nextCrossID[y-1][x][UP]!=p(-1,-1)) nextCrossID[y][x][UP]=nextCrossID[y-1][x][UP] ;
                if (iscrossRoad(y-1,x)) nextCrossID[y][x][UP]=p(x,y-1) ;
            }
        }
        nextCrossID[MAP_HEIGHT-1][x][DOWN]=p(-1,-1) ;
        for (int y=MAP_HEIGHT-1;y>=0;--y) {
            nextCrossID[y][x][DOWN]=p(-1,-1) ;
            if (!isWall(std::pair<int,int> (x,y))) {
                if (nextCrossID[y+1][x][DOWN]!=p(-1,-1)) nextCrossID[y][x][DOWN]=nextCrossID[y+1][x][DOWN] ;
                if (iscrossRoad(y+1,x)) nextCrossID[y][x][DOWN]=p(x,y+1) ;
            }
        }
    }
}
void Map::calculateDistance() { // BFS algorithm
    for (int x=0;x<MAP_WIDTH;++x) {
        for (int y=0;y<MAP_HEIGHT;++y) {
            for (int u=0;u<MAP_WIDTH;++u) {
                for (int v=0;v<MAP_HEIGHT;++v) {
                    for (int dir=0;dir<4;++dir) {
                        dist[x*MAP_HEIGHT+y][u*MAP_HEIGHT+v][dir]=-1 ;
                    }
                }
            }
        }
    }
    int cnt=0 ;
    int moveX[4]={0,1,0,-1} ;
    int moveY[4]={-1,0,1,0} ; // theo thứ tự là UP, RIGHT, DOWN, LEFT
    int dis[MAP_HEIGHT*MAP_WIDTH] ;
    std::queue<std::pair<int ,int>> visitedNode ;
    for (int x=0;x<MAP_WIDTH;++x) {
        for (int y=0;y<MAP_HEIGHT;++y) {
            if (isWall(std::pair<int,int> (x,y))) continue;
            if (y==14&&(x==0||x==27)) continue ;
            for (int startDir=0;startDir<4;++startDir) {
                int xTemp=x+moveX[startDir] ;
                int yTemp=y+moveY[startDir] ;
                if (isWall(std::pair<int,int>(xTemp,yTemp))) continue ;
                for (int i=0;i<MAP_HEIGHT*MAP_WIDTH;++i) dis[i]=-1 ;
                ++cnt ;
                color[yTemp][xTemp]=cnt ;
                dis[xTemp*MAP_HEIGHT+yTemp]=0 ;
                visitedNode.push(std::pair<int,int> (xTemp*MAP_HEIGHT+yTemp,startDir)) ;
                while (!visitedNode.empty()) {
                    int curx=visitedNode.front().first / MAP_HEIGHT ;
                    int cury=visitedNode.front().second % MAP_HEIGHT ;
                    int lasDir=visitedNode.front().second ;
                    visitedNode.pop() ;
                    if (cury==14&&(curx==0||curx==27)) continue ;
                    for (int dir=0;dir<4;++dir) {
                        int u=curx+moveX[dir] ;
                        int v=cury+moveY[dir] ;
                        if (lasDir%2==dir%2&&dir!=lasDir) continue ;// 2 hướng cùng phương ngược chiều
                        if (isWall(std::pair<int,int>(u,v))) continue ;
                        if (color[v][u]!=cnt) {
                            color[v][u]=cnt ;
                            dis [u*MAP_HEIGHT+v]=dis[curx*MAP_HEIGHT+cury]+1 ;
                            visitedNode.push(std::pair<int,int> (u*MAP_HEIGHT+v,dir)) ;
                        }
                    }
                }
                for (int i=0;i<MAP_HEIGHT*MAP_WIDTH;++i)
                    dist[xTemp*MAP_HEIGHT+yTemp][i][startDir]=dis[i];
            }
        }
    }
    std::cout<<"calculate distance has been done" ;
}

int Map::getTileID(int x, int y) {
    return tile[y][x] ;
}

void Map::reset() {
    for (int i=0;i<MAP_HEIGHT;++i) {
        for (int j=0;j<MAP_WIDTH;++j) {
            tile[i][j]=premanMap[i][j];
        }
    }
}

bool Map::canChangeDir(int x, int y, int newDir) {
    return markCross[y][x][newDir] ;
}

bool Map::besideCrossIsWall(std::pair<int, int> Cross, int newDir) {
    if (newDir==UP) Cross.second-=1 ;
    if (newDir==DOWN) Cross.second+=1 ;
    if (newDir==LEFT) Cross.first-=1 ;
    if (newDir==RIGHT) Cross.first+=1 ;
    return isWall(Cross) ;
}

