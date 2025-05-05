//
// Created by Nguyễn Trang Linh on 18/4/25.
//
#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SDL.h>
#include "TextManager.h"

class Button {
    public:
        static const int BUTTON_OUT=0 ;
        static const int BUTTON_IN=1 ;
        static const int BUTTON_PRESSED=2 ;
        const SDL_Color normalColor={0,0,0,255} ;
        const SDL_Color selectColor={254,233,0,255} ;
        Button(int Width, int Height, int scrPosX, int scrPosY);
        void loadButton(SDL_Renderer* &renderer,const std::string& text) ;
        void renderButton(SDL_Renderer* &renderer) ;
        void getStatus(const int status) ;
        bool checkMousePos(const int&x, const int&y) const;
        std::string getText() const;
    private:
        SDL_Rect buttonRect ;
        TextManager *normalText ;
        TextManager *selectText ;
        int buttonStatus ;
        std::string bText ;
} ;
#endif //BUTTON_H
