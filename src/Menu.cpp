//
// Created by Nguyễn Trang Linh on 5/5/25.
//
#include "Menu.h"
#include <stdio.h>

Menu::Menu(const int baseSrcPosX, const int baseSrcPosY, const int totalButton, const int buttonWidth, const int buttonHeight) {
    menuTexture=nullptr ;
    TOTAL_BUTTON=1;
    MENU_BUTTON_WIDTH=buttonWidth;
    MENU_BUTTON_HEIGHT=buttonHeight;
    this->baseScrPosX= baseSrcPosX;
    this->baseScrPosY= baseSrcPosY;
}

Menu::~Menu() {
    Mix_FreeChunk(navigationSound) ;
    SDL_DestroyTexture(menuTexture);
    menuTexture=nullptr ;
    menuButton.clear() ;
}

SDL_Texture *Menu::loadImage(SDL_Renderer *&renderer, const std::string imgPath) {
    SDL_Surface* Image = IMG_Load(imgPath.c_str());
    SDL_Texture *loadTexture = SDL_CreateTextureFromSurface(renderer, Image);
    SDL_FreeSurface(Image);
    return loadTexture ;
}

void Menu::init(SDL_Renderer *&renderer, const std::string imgPath, std::vector<std::string> &buttonText) {
    SDL_Surface* Image= IMG_Load(imgPath.c_str());
    if (Image==nullptr) {
        console->Status(IMG_GetError());
    }
    else {
        menuTexture=SDL_CreateTextureFromSurface(renderer, Image);
        SDL_FreeSurface(Image);
        menuButton.push_back(new Button(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, baseScrPosX-MENU_BUTTON_WIDTH/2, baseScrPosY));
        menuButton.at(0)->loadButton(renderer, buttonText); // lỗi gì ý không dùng [0] được nên thay bằng at(0)
        menuButton.at(0)->setStatus(Button::BUTTON_IN) ;
        currentButtonID=0 ;
        currentMenuStatus=RUNNING ;

    }
}

void Menu::render(SDL_Renderer *&renderer,const std::vector<std::string> &scoreData) {
    SDL_RenderCopy(renderer, menuTexture, nullptr, nullptr);
    menuButton.at(0)->renderButton(renderer) ;
}

void Menu::handleEvent(SDL_Event &e, SDL_Renderer* &renderer) {
    if (e.type==SDL_KEYDOWN&&e.key.keysym.sym==SDLK_RETURN) {
        Mix_PlayChannel(7, navigationSound,0) ;
        currentMenuStatus=PLAY_BUTTON_PRESSED ;
    }
}

bool Menu::isRunning() const {
    return currentMenuStatus==RUNNING ;
}

int Menu::getStatus() const {
    return currentMenuStatus ;
}

void Menu::reOpen() {
    currentMenuStatus=RUNNING ;
    menuButton.at(currentButtonID)->setStatus(Button::BUTTON_IN) ;
}

void Menu::changeRunStatus() {
    running=!running ;
}
