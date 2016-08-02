#ifndef TIMER_HPP
#define TIMER_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL/SDL.h>

namespace chaos{

class Timer{
public:
    Timer(){}
    void restart(){
        startTime = SDL_GetTicks();
    }
    GLuint getTime(){
        return SDL_GetTicks() - startTime;
    }
    GLfloat getTimeAsSeconds(){
        return getTime()/1000.0f;
    }
private:
    GLuint startTime=0;
};

}

#endif //TIMER_HPP
