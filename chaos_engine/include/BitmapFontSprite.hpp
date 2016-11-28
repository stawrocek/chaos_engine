#ifndef BITMAP_FONT_SPRITE_HPP
#define BITMAP_FONT_SPRITE_HPP

#include "Export.hpp"
#include "BitmapFont.hpp"
#include "GameObject.hpp"

#include <SDL/SDL.h>
#include <string>

namespace chaos{

class CHAOS_EXPORT BitmapFontSprite: public DrawableGameObject{
public:
    BitmapFontSprite(Renderer* ren, BitmapFont* b, std::string str="")
    :DrawableGameObject(ren,"Rectangle:Pos_Id", "Shader_Font2d")
    {
        setBitmapFont(b);
        setText(str);
    }

    virtual void draw(){
        draw(text);
    }

    virtual void drawChar(int c, int x, int y) {
        if(bitmapFont->mapChars.find(c) == bitmapFont->mapChars.end())return;
        CharData data = bitmapFont->mapChars[c];
        bitmapFont->vecPages[data.page]->bind(GL_TEXTURE_2D);
        shader->run();
        GLint winWidth, winHeight;
        SDL_GetWindowSize(renderer->getTargetWindow()->getWindowHandle(), &winWidth, &winHeight);
        glm::mat4 mx = glm::mat4();
        if(fitToScreen){
            //-> punkt(0,0) jest w lewym dolnym rogu, os y dodatnia do gory
            mx = glm::translate(mx, glm::vec3(-1.0f, -1.0f, 0.0f));
            mx = glm::translate(mx, glm::vec3((2.0f*x)/winWidth, (2.0f*y)/winHeight, 0.0f));
            mx = glm::scale(mx, glm::vec3((2.0f*data.width)/winWidth, (2.0f*data.height)/winHeight, 1.0));
            mx = getGlobalTransformMatrix() * mx;
        }
        else{
            mx = glm::translate(mx, glm::vec3((2.0f*x)/winWidth, (2.0f*y)/winHeight, 0.0f));
            mx = glm::scale(mx, glm::vec3((2.0f*data.width)/winWidth, (2.0f*data.height)/winHeight, 1.0));
            mx = getGlobalTransformMatrix() * mx;
            mx = renderer->getCamCombined()*mx;
        }


        shader->setUniform("mvp", mx);
        shader->setUniform("minx", data.x/(float)bitmapFont->scaleW);
        shader->setUniform("maxx", (data.x+data.xadvance)/(float)bitmapFont->scaleW);
        shader->setUniform("miny", (bitmapFont->scaleH-data.y-bitmapFont->lineHeight)/(float)bitmapFont->scaleH);
        shader->setUniform("maxy", (bitmapFont->scaleH-data.y)/(float)bitmapFont->scaleH);
        shader->setUniform("uniColor", color);
        vao->bind();
        glDrawArrays(GL_TRIANGLES, 0, vao->countVertices());
        vao->unbind();
    }

    virtual void draw(std::string str) {
        int tmpY = getY(), tmpX = getX();
        for(GLuint i = 0; i < str.size(); i++) {
            if(str[i] == '\n') {
                tmpX = getX();
                tmpY -= bitmapFont->lineHeight;
            }
            else {
                if(bitmapFont->mapChars.find(str[i]) == bitmapFont->mapChars.end())
                    continue;
                CharData data = bitmapFont->mapChars[str[i]];
                drawChar(str[i], tmpX, tmpY);
                tmpX += data.xadvance;
            }
        }
    }

    void setBitmapFont(BitmapFont* b){
        bitmapFont = b;
    }

    void setFitToScreen(GLboolean b){
        fitToScreen = b;
    }

    GLboolean isFitToScreen(){
        return fitToScreen;
    }

    void setText(std::string str){
        text = str;
    }

    std::string getText(){
        return text;
    }

protected:
    BitmapFont* bitmapFont;
    GLboolean fitToScreen=false;
    std::string text="";
};

}

#endif //BITMAP_FONT_SPRITE_HPP




