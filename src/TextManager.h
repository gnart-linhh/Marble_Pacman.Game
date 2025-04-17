//
// Created by Nguyễn Trang Linh on 17/4/25.
//
#pragma once

#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <SDL_ttf.h>
#include <string>

class TextManager {
    public :
        const std::string  FONT_NAME="Assets/Font/Blogger Sans-Bold.tff" ;
        static const int CENTER=0  ;
        static const int LEFT  =1  ;
        TextManager(int fontSize);
        ~TextManager();
        int getTextWidth() const;
        void loadRenderText(SDL_Renderer* renderer, std::string text,SDL_Color textColor);
        void renderText(SDL_Renderer* renderer, int x, int y, const int type) ;
    private:
        SDL_Rect dsRect ;
        TTF_Font* font;
        SDL_Texture *textTexture ;
        SDL_Surface *textSurface ;
} ;

#endif //TEXTMANAGER_H
