#ifndef EXPORT_HPP
#define EXPORT_HPP

//comment DEVELOPMENT_MODE if you want to build .dll
#define DEVELOPMENT_MODE

#include <string>

#ifdef ANDROID
#include <GLES2/gl2.h>
#else
    #ifdef DEVELOPMENT_MODE
        #define GLEW_STATIC
    #else
        #define GLEW_STATIC
    #endif
#include <GL/glew.h>
#endif // ANDROID

#ifndef ANDROID
    #define VAO_ENABLED
    #define GEOMETRY_SHADER_ENABLED
#endif // ANDROID

#if !defined(ANDROID) && !defined(__EMSCRIPTEN__)
    #define LAYOUT_LOCATION
#endif

namespace chaos{

#ifndef DEVELOPMENT_MODE
    #ifdef _WIN32
        //add -DDLL_EXPORT to g++ arguments
        #ifdef DLL_EXPORT
            #define CHAOS_EXPORT __declspec(dllexport)
        #else
            #define CHAOS_EXPORT __declspec(dllimport)
        #endif
    #else
        #define CHAOS_EXPORT
    #endif
#else
    #define CHAOS_EXPORT
#endif
}

#endif // EXPORT_HPP
