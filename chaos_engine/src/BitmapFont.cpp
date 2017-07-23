#include "../include/BitmapFont.hpp"

#include "../include/Texture.hpp"

using namespace chaos;

BitmapFont::BitmapFont(std::string fpath, TextureLoader* textureLoader)
:Resource(fpath)
{
    load(getFilePath(), textureLoader);
}

BitmapFont::~BitmapFont(){
    for(GLuint i = 0; i < vecPages.size(); i++){
        delete vecPages[i];
    }
    std::cout << "Destructor of BitmapFont(" << face << ")\n";
}

void BitmapFont::load(std::string fpath, TextureLoader* textureLoader) {
    std::cout << "load\n";
    vecPages.clear();
    mapChars.clear();
    std::string file = getFileAsString(fpath);
    std::string tmp="";
    std::string dir = fpath.substr(0,fpath.find_last_of("/\\"));
    if(dir == fpath)dir="";
    for(GLuint i = 0; i < file.size(); i++){
        if(file[i]=='\n'){
            readLine(tmp, dir, textureLoader);
            tmp="";
        }
        else
            tmp += file[i];
    }
    if(tmp.size() > 1)
        readLine(tmp, dir, textureLoader);
}

int BitmapFont::getInt(std::map<std::string, std::string>& m, std::string key) {
    if(m.find(key) == m.end())return 0;
    int retVal;
    std::istringstream iss(m[key]);
    iss >> retVal;
    return retVal;
}

std::string BitmapFont::getStr(std::map<std::string, std::string>& m, std::string key) {
    if(m.find(key) == m.end())
        return"";
    return m[key];
}

void BitmapFont::readLine(std::string & s, std::string dirPath, TextureLoader* textureLoader) {
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
                    if((tmpValue.size() > 0 && tmpValue != " ") || (i>=2 && s[i-1] == '"' && s[i-2] == '"')) {
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
        vecPages.push_back(new Texture(fpath, textureLoader));
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
