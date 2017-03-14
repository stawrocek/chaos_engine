#ifndef BITMAP_FONT_HPP
#define BITMAP_FONT_HPP

#include "Export.hpp"
#include "ShaderProgram.hpp"
#include "Utils.hpp"
#include "Resource.hpp"
#include "Texture.hpp"

#include <vector>
#include <map>
#include <sstream>

namespace chaos {

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
    BitmapFont(std::string fpath)
    :Resource(fpath)
    {
        load(fpath);
    }
    virtual ~BitmapFont(){
        for(GLuint i = 0; i < vecPages.size(); i++){
            delete vecPages[i];
        }
        std::cout << "Destructor of BitmapFont(" << face << ")\n";
    }
    void load(std::string fpath) {
        std::cout << "load\n";
        vecPages.clear();
        mapChars.clear();
        std::string file = getFileAsString(fpath);
        std::string tmp="";
        std::string dir = fpath.substr(0,fpath.find_last_of("/\\"));
        if(dir == fpath)dir="";
        for(GLuint i = 0; i < file.size(); i++){
            if(file[i]=='\n'){
                readLine(tmp, dir);
                tmp="";
            }
            else
                tmp += file[i];
        }
        if(tmp.size() > 1)
            readLine(tmp, dir);
    }

    int getInt(std::map<std::string, std::string>& m, std::string key) {
        if(m.find(key) == m.end())return 0;
        int retVal;
        std::istringstream iss(m[key]);
        iss >> retVal;
        return retVal;
    }

    std::string getStr(std::map<std::string, std::string>& m, std::string key) {
        if(m.find(key) == m.end())
            return"";
        return m[key];
    }

    void readLine(std::string & s, std::string dirPath) {
        if(s[s.size()-1] == '\r')s.pop_back();
        s+=" ";
        std::string typeId="";
        GLuint i=0;
        for(i = 0; i < s.size(); i++) {
            if(s[i] == ' ')
                break;
            typeId += s[i];
        }
        std::map<std::string, std::string> data;
        std::string tmpKey="", tmpValue="";
        bool apo=false, key=true;
        for(++i; i < s.size(); i++) {
            if(s[i] == '"') {
                apo = !apo;
                continue;
            }
            if(s[i] == '=' && !apo) {
                key=!key;
                continue;
            }

            if(s[i] == ' ') {
                if(apo) {
                    if(key) tmpKey += ' ';
                    if(!key) tmpValue += ' ';
                }
                else {
                    if(key) {
                        continue;
                    }
                    if(!key) {
                        if((tmpValue.size() >= 0 && tmpValue != " ") || (i>=2 && s[i-1] == '"' && s[i-2] == '"')) {
                            data.insert(make_pair(tmpKey, tmpValue));
                            tmpKey="", tmpValue="";
                        }
                        key = true;
                    }
                }
            }
            else {
                if(key)tmpKey += s[i];
                if(!key)tmpValue += s[i];
            }
        }
        if(typeId == "chars") {
            charsCount = getInt(data, "count");
        }
        if(typeId == "info") {
            face=getStr(data,"face");
            size=getInt(data,"size");
            bold=getInt(data,"bold");
            italic=getInt(data,"italic");
            charset = getStr(data,"charset");
            unicode=getInt(data,"unicode");
            stretchH=getInt(data,"stretchH");
            smooth=getInt(data,"smooth");
            aa=getInt(data,"aa");
            outline=getInt(data,"outline");
        }
        if(typeId == "common") {
            lineHeight = getInt(data, "lineHeight");
            base=getInt(data,"base");
            scaleW=getInt(data,"scaleW");
            scaleH=getInt(data,"scaleH");
            pages=getInt(data,"pages");
            packed=getInt(data,"packed");
            alphaChnl=getInt(data,"alphaChnl");
            redChnl=getInt(data,"redChnl");
            greenChnl=getInt(data,"greenChnl");
            blueChnl=getInt(data,"blueChnl");
        }
        if(typeId == "page") {
            std::string fpath = ((dirPath=="")?(getStr(data, "file")) : (dirPath+"/"+getStr(data, "file")));
            vecPages.push_back(new Texture(fpath));
            std::cout << fpath << "\n";
        }
        //char id=0    x=254   y=0     width=0     height=32    xoffset=0     yoffset=0     xadvance=0     page=0  chnl=15

        if(typeId == "char") {
            CharData d(getInt(data, "id"), getInt(data,"x"), getInt(data,"y"),
                       getInt(data,"width"),getInt(data,"height"),getInt(data,"xoffset"), getInt(data,"yoffset"),
                       getInt(data,"xadvance"),getInt(data,"page"), getInt(data,"chnl"));
            mapChars.insert(std::make_pair(getInt(data, "id"), d));
        }
    }

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

