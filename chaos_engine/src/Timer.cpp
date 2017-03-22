#include "../include/Timer.hpp"

chaos::Timer::Timer(){
    startTime = std::chrono::system_clock::now();
}
void chaos::Timer::restart(){
    startTime = std::chrono::system_clock::now();
}
GLuint chaos::Timer::getTime(){
    auto diff = std::chrono::system_clock::now()-startTime;
    return std::chrono::duration_cast <std::chrono::milliseconds> (diff).count();
}
GLfloat chaos::Timer::getTimeAsSeconds(){
    return getTime()/1000.0f;
}
