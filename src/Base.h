//
// Created by Nguyễn Trang Linh on 25/4/25.
//

#ifndef BASE_H
#define BASE_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"
#include "TextureSrc.h"
#include "Control.h"

class Base{
  public:
    Base(){
      map=nullptr;
      pacman=nullptr;
      blinky=nullptr;
      pinky=nullptr;
      inky=nullptr;
      clyde=nullptr ;
      objectTexture=nullptr;
    }
    ~Base() {
      delete map ; map=nullptr;
      delete pacman ; pacman=nullptr;
      delete blinky ; blinky=nullptr;
      delete pinky ; pinky=nullptr;
      delete inky ; inky=nullptr;
      delete clyde ; clyde=nullptr;
      delete objectTexture ; objectTexture=nullptr;
    }
    void init(SDL_Renderer* renderer);
    void newGame() ;
    void handleEvent(SDL_Event &e, std::vector<std::string> &scoreData);
    void loop(bool &exitToMenu) ;
    void render(SDL_Renderer* renderer, const std::vector<std::string> &scoreData);
  private:
    Map* map ;
    Pacman* pacman=nullptr;
    Ghost* blinky=nullptr ;
    Ghost* pinky=nullptr ;
    Ghost* inky=nullptr ;
    Ghost* clyde=nullptr ;
    TextureSrc* objectTexture ;
    Control* control ;
    bool runningEGBoard=false ;

  protected:
    void renderGhost(SDL_Renderer* renderer, Ghost* &ghost, int ghostID) ;
    void respawnObject() ;
} ;

#endif //BASE_H
