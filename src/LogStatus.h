//
// Created by Nguyễn Trang Linh on 18/4/25.
//

#ifndef LOGSTATUS_H
#define LOGSTATUS_H

#include <iostream>
#include <string>
class LogStatus {
    public :
      LogStatus(){}
      LogStatus(std::string area){
        this->area = area;
      }
      void Status(const std::string msg) {
        std::cout <<area<< " : "<<msg << std::endl;
      }
    private :
      std::string area;
} ;
#endif //LOGSTATUS_H
