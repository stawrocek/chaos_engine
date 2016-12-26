#ifndef EXPORT_HPP
#define EXPORT_HPP

namespace chaos{

//uncomment DEVELOPMENT_MODE if you want to build dll
#define DEVELOPMENT_MODE


#ifndef DEVELOPMENT_MODE
    #ifdef _WIN32
        //add -DDLL_EXPORT to g+ +arguments
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
