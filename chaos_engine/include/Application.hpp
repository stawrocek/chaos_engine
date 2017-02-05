#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Export.hpp"

namespace chaos{

class Window;

class CHAOS_EXPORT Application{
public:
    Application(){}
    Application(Window* w)
    :window(w)
    {};

    virtual void onCreate(){};
    virtual void onDraw(){};
    virtual void onResize(int newWidth, int newHeight){};
    virtual void run(){};

    static std::string const& getDataStorageDirectory(){
        return dataStorageDir;
    }

    static void setDataStorageDirectory(std::string str){
        dataStorageDir = str;
    }

    static std::string dataStorageDir;
    Window* window;
};

}
#endif // APPLICATION_HPP

