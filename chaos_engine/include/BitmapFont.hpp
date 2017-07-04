#ifndef BITMAP_FONT_HPP
#define BITMAP_FONT_HPP

#include <vector>
#include <map>
#include <sstream>

#include "Export.hpp"
#include "Utils.hpp"
#include "Resource.hpp"

namespace chaos {

class Texture;
class TextureLoader;

struct CHAOS_EXPORT CharData {
    int id, x, y, width, height, xoffset, yoffset, xadvance, page, chnl;
    CharData(int _id, int _x, int _y, int _width, int _height, int _xoffset, int _yoffset,
             int _xadvance, int _page, int _chnl)
    :id(_id), x(_x), y(_y), width(_width), height(_height), xoffset(_xoffset), yoffset(_yoffset),
    xadvance(_xadvance), page(_page), chnl(_chnl)
    {}
    CharData(){}
};

class CHAOS_EXPORT BitmapFont: public Resource{
public:
    BitmapFont(std::string fpath, TextureLoader* textureLoader);
    virtual ~BitmapFont();
    void load(std::string fpath, TextureLoader* textureLoader);
    int getInt(std::map<std::string, std::string>& m, std::string key);
    std::string getStr(std::map<std::string, std::string>& m, std::string key);
    void readLine(std::string & s, std::string dirPath, TextureLoader* textureLoader);

    /*font data*/
    std::string face="", charset="";
    int size=0, bold=0, italic=0, unicode=0, stretchH=0, smooth=0, aa=0, outline=0, lineHeight=0;
    int base=0, scaleW=0, scaleH=0, pages=0, packed=0;
    int alphaChnl=0, redChnl=0, greenChnl=0, blueChnl=0;
    int charsCount=0;

    std::map<int, CharData> mapChars;
    std::vector<Texture*> vecPages;
};

}

#endif

