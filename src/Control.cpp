//
// Created by Nguyễn Trang Linh on 26/4/25.
//
#include "Control.h"
#include <iostream>

Control::Control() {
    lastTick=SDL_GetTicks();
    mode.push(CID(CHASING_MODE,oo)) ;
    mode.push(CID(SCATTERING_MODE, SCATTERING_TIME)) ;
    mode.push(CID(CHASING_MODE, CHASING_TIME)) ;
    mode.push(CID(SCATTERING_MODE, SCATTERING_TIME)) ;
    mode.push(CID(CHASING_MODE, CHASING_TIME)) ;
    mode.push(CID(SCATTERING_MODE, SCATTERING_TIME)) ;
    mode.push(CID(CHASING_MODE, CHASING_TIME)) ;
    mode.push(CID(SCATTERING_MODE, SCATTERING_TIME)) ;
}

void Control::setFrightenTime() {
    lastStatus=mode.top().first ;
    mode.pop() ;
    if (lastStatus==CHASING_MODE)
        mode.push(CID(CHASING_MODE,CHASING_TIME-(SDL_GetTicks()-lastTick))) ;
    else if (lastStatus==SCATTERING_MODE)
        mode.push(CID(SCATTERING_MODE,SCATTERING_TIME-(SDL_GetTicks()-lastTick))) ;
    mode.push(CID(FRIGHTEN_MODE,FRIGHTEN_TIME)) ;
    lastTick=SDL_GetTicks();
}


double Control::remainFrightenTime() const {
    return FRIGHTEN_TIME-(SDL_GetTicks()-lastTick)/1000.0;
}

void Control::stablizeFPS() {
    if (SDL_GetTicks()-lastFrame<1000/FPS) {
        SDL_Delay(1000/FPS+lastFrame-SDL_GetTicks());
    }
    lastFrame=SDL_GetTicks();
}

bool Control::isFrightenTime() const {
    return mode.top().first==FRIGHTEN_MODE ;
}

bool Control::isScatteringTime() const {
    return mode.top().first==SCATTERING_MODE ;
}

bool Control::pauseTick(const bool status) {
    return pause=status ;
}

void Control::resetTick(const int level) {
    while (!mode.empty()) mode.pop() ;
    if (level==1) {
        mode.push(CID(CHASING_MODE,oo)) ;
        mode.push(CID(SCATTERING_MODE, SCATTERING_TIME)) ;
        mode.push(CID(CHASING_MODE, CHASING_TIME)) ;
        mode.push(CID(SCATTERING_MODE, SCATTERING_TIME)) ;
        mode.push(CID(CHASING_MODE, CHASING_TIME)) ;
        mode.push(CID(SCATTERING_MODE, SCATTERING_TIME)) ;
        mode.push(CID(CHASING_MODE, CHASING_TIME)) ;
        mode.push(CID(SCATTERING_MODE, SCATTERING_TIME)) ;
        FRIGHTEN_TIME=5.0 ;
    }
    else {
        mode.push(CID(CHASING_MODE,oo)) ;
        mode.push(CID(SCATTERING_MODE,1.0 )) ;
        mode.push(CID(CHASING_MODE,1033.0 )) ;
        mode.push(CID(SCATTERING_MODE,5.0 )) ;
        mode.push(CID(CHASING_MODE, CHASING_TIME)) ;
        mode.push(CID(SCATTERING_MODE, SCATTERING_TIME)) ;
        mode.push(CID(CHASING_MODE, CHASING_TIME)) ;
        mode.push(CID(SCATTERING_MODE, SCATTERING_TIME)) ;
        FRIGHTEN_TIME = 3.0;
    }
}

void Control::updateStatus() {
    if (pause==true) {
        lastTick=SDL_GetTicks();
        return ;
    }
    double timePass=(SDL_GetTicks()-lastTick)/1000.0;
    if (!mode.empty()) {
        if (timePass>mode.top().second&&mode.top().second!=oo) {
            mode.pop() ;
            lastTick=SDL_GetTicks();
        }
    }
}





