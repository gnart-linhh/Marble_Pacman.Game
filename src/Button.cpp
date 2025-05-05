//
// Created by Nguyễn Trang Linh on 18/4/25.
//
#include "Button.h"

Button::Button(int Width, int Height, int scrPosX, int scrPosY) {
    buttonRect={scrPosX, scrPosY, Width, Height};
    normalText= new TextManager(24) ;
    selectText= new TextManager(24) ;
    buttonStatus=BUTTON_OUT ;
}

void Button::loadButton(SDL_Renderer* &renderer,const std::string& text) {
    if(text=="") return ;
    normalText->loadRenderText(renderer, text, normalColor) ;
    selectText->loadRenderText(renderer, text, selectColor) ;
    bText=text ;
}

void Button::renderButton(SDL_Renderer* &renderer) {
    if (buttonStatus==BUTTON_IN) { // chuot tren button
        // pastel pink
        SDL_SetRenderDrawColor(renderer, 251, 69, 152, 255) ;
        SDL_RenderFillRect(renderer, &buttonRect);
        selectText->renderText(renderer, buttonRect.x+ buttonRect.w/2, buttonRect.y+ buttonRect.h/2, TextManager::CENTER) ; // ve chinh giua nut
    }
    else {
        normalText->renderText(renderer, buttonRect.x+buttonRect.w/2, buttonRect.y+buttonRect.h/2, TextManager::CENTER) ;
    }
}

void Button::getStatus(const int status) {
    buttonStatus=status ;
}

bool Button::checkMousePos(const int &x, const int &y) const {
    if (x<buttonRect.x||x>buttonRect.x+buttonRect.w) return false;
    if (y<buttonRect.y||y>buttonRect.y+buttonRect.h) return false;
    return true ;
}

std::string Button::getText() const {
    return bText ;
}

