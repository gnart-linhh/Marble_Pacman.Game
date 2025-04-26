//
// Created by Nguyễn Trang Linh on 26/4/25.
//
#pragma once

#ifndef CONTROL_H
#define CONTROL_H

#include <SDL.h>
#include <stack>

typedef std::pair<const int, double> CID ;

class Control {
    private:
      Uint32 lastTick ;
      Uint32 lastFrame=0 ;
      double FRIGHTEN_TIME=5.0 ;
      double SCATTERING_TIME=7.0 ;
      double CHASING_TIME=20.0 ;
      std::stack<CID> mode ;
      int lastStatus ;
    public:
      const int FPS=60 ;
      const int FRIGHTEN_MODE=0 ;
      const int SCATTERING_MODE=1;
      const int CHASING_MODE=2;
      const double oo=-1 ;
      Control();
      double remainFrightenTime() const ;
      bool isFrightenTime() const ;
      void setFrightenTime() ;
      void stablizeFPS() ;
      void updateStatus() ;

} ;

#endif //CONTROL_H
