//
// Created by Nguyễn Trang Linh on 5/5/25.
//
#pragma once
#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "LogStatus.h"
#include "Button.h"

class Menu{
    public:
      static const int RUNNING=1 ;
      static const int PLAY_BUTTON_PRESSED=2 ;
      Menu(const int baseScrPosX, const int baseScrPosY, const int totalButton, const int buttonWidth, const int buttonHeight) ;
      ~Menu() ;
      void init(SDL_Renderer* &renderer, const std::string imgPath, std::vector<std::string> &buttonText) ;
      void render(SDL_Renderer* &renderer, const std::vector<std::string> &scoreData) ;
      void handleEvent(SDL_Event &e, SDL_Renderer* &renderer) ;
      bool isRunning() const ;
      int getStatus() const ;
      void reOpen() ;
      void changeRunStatus() ;
    private:
      int currentButtonID ;
      int currentMenuStatus ;
      int TOTAL_BUTTON ;
      int MENU_BUTTON_WIDTH ;
      int MENU_BUTTON_HEIGHT ;
      int baseScrPosX ;
      int baseScrPosY ;
      Mix_Chunk* navigationSound= Mix_LoadWAV("Assets/Sound/button.wav") ;
      SDL_Texture* menuTexture ;
      std::vector<Button*> menuButton ;
      LogStatus* console= new LogStatus("Menu") ;
      bool running=false ;
      SDL_Texture* loadImage(SDL_Renderer* &renderer, const std::string imgPath) ;
} ;

#endif //MENU_H
