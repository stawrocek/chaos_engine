#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

#include "Export.hpp"

namespace chaos{

class CHAOS_EXPORT Timer{
public:
    Timer();
    void restart();
    GLuint getTime();
    GLfloat getTimeAsSeconds();
private:
    std::chrono::system_clock::time_point startTime;
};

}

#endif //TIMER_HPP
