#ifndef BITMAP_FONT_SPRITE_HPP
#define BITMAP_FONT_SPRITE_HPP

#include <string>

#include "Export.hpp"
#include "GameObject.hpp"

namespace chaos{

class Renderer;
class BitmapFont;

class CHAOS_EXPORT BitmapFontSprite: public GameObject{
public:
    BitmapFontSprite(Renderer* ren, BitmapFont* b, std::string str="");
    virtual void draw();
    virtual void drawChar(int c, int x, int y);
    virtual void draw(std::string str);
    void setBitmapFont(BitmapFont* b);
    void setFitToScreen(GLboolean b);
    GLboolean isFitToScreen();
    void setText(std::string str);
    std::string getText();

protected:
    BitmapFont* bitmapFont;
    GLboolean fitToScreen=false;
    std::string text="";
};

}

#endif //BITMAP_FONT_SPRITE_HPP




