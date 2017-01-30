#ifndef TIMER_HPP
#define TIMER_HPP

#include "Export.hpp"

#include <chrono>

namespace chaos{

class CHAOS_EXPORT Timer{
public:
    Timer(){
        startTime = std::chrono::system_clock::now();
    }
    void restart(){
        startTime = std::chrono::system_clock::now();
    }
    GLuint getTime(){
        auto diff = std::chrono::system_clock::now()-startTime;
        return std::chrono::duration_cast <std::chrono::milliseconds> (diff).count();
    }
    GLfloat getTimeAsSeconds(){
        return getTime()/1000.0f;
    }
private:
    std::chrono::system_clock::time_point startTime;
};

}

#endif //TIMER_HPP
