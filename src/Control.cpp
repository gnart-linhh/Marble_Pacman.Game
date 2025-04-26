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
