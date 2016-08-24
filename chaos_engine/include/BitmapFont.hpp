#ifndef BITMAP_FONT_HPP
#define BITMAP_FONT_HPP

#include <glm/gtx/string_cast.hpp>

#include <vector>
#include "ShaderProgram.hpp"
#include <map>
#include <sstream>

namespace chaos {

struct CharData {
    int id, x, y, width, height, xoffset, yoffset, xadvance, page, chnl;
    CharData(int _id, int _x, int _y, int _width, int _height, int _xoffset, int _yoffset,
             int _xadvance, int _page, int _chnl)
    :id(_id), x(_x), y(_y), width(_width), height(_height), xoffset(_xoffset), yoffset(_yoffset),
    xadvance(_xadvance), page(_page), chnl(_chnl)
    {}
    CharData(){}
};

class BitmapFont{
public:
    BitmapFont(std::string fpath, Renderer* shr, Window* _win)
    {
        load(fpath, shr, _win);
    }
    virtual ~BitmapFont(){
        for(GLuint i = 0; i < vecPages.size(); i++){
            delete vecPages[i];
        }
    }
    long get_file_size(FILE* f) {
        long size = 0;
        fseek(f, 0L, SEEK_END), size = ftell(f), fseek(f, 0L, SEEK_SET);
        return size;
    };

    std::string get_file_as_string(const std::string& path) {
        FILE* f = fopen(path.c_str(), "rb");
        long size_bytes = 0;

        if(!f) {
            printf("Failed to open file %s\n", path.c_str());
            exit(0);
        }
        size_bytes = get_file_size(f);

        std::vector<GLchar> code;
        code.resize(size_bytes + 1);

        if(fread(&code[0], size_bytes, 1, f) != 1) {
            printf("Unable to read %s\n", path.c_str());
            exit(0);
        }

        code[size_bytes] = 0;
        return std::string(code.begin(), code.end());
    }
    void load(std::string fpath, Renderer* shr, Window* _win) {
        std::cout << "load\n";
        vecPages.clear();
        mapChars.clear();
        std::string file = get_file_as_string(fpath);
        std::string tmp="";
        std::string dir = fpath.substr(0,fpath.find_last_of("/\\"));
        if(dir == fpath)dir="";
        for(int i = 0; i < file.size(); i++){
            if(file[i]=='\n'){
                readLine(tmp, dir);
                tmp="";
            }
            else
                tmp += file[i];
        }
        if(tmp.size() > 1)
            readLine(tmp, dir);


        std::cout << "ld vao\n";
        loadVAO(shr);
        std::cout << "ld vao2\n";
        win = _win;
        std::cout << "woo!\n";
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
        int i=0;
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

    void loadVAO(Renderer* ren) {
        shr = ren->getShader("Shader_Font2d");

        /*
        1    2
        *----*
        |    *
        |    *
        *----*
        4    3
        */

        std::vector<glm::vec4> verts {
            {0.0f,  0.0f, 0.0f, 4.0f},
            {1.0f,  0.0f, 0.0f, 3.0f},
            {0.0f,  1.0f, 0.0f, 1.0f},
            {0.0f,  1.0f, 0.0f, 1.0f},
            {1.0f,  0.0f, 0.0f, 3.0f},
            {1.0f,  1.0f, 0.0f, 2.0f}
        };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(glm::vec4), verts.data() , GL_STATIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    void drawChar(int c, int x, int y) {
        if(mapChars.find(c) == mapChars.end())return;
        CharData data = mapChars[c];
        vecPages[data.page]->bind(GL_TEXTURE_2D);
        shr->run();
        GLint winWidth, winHeight;
        SDL_GetWindowSize(win->getWindowHandle(), &winWidth, &winHeight);
        glm::mat4 mx = glm::mat4();
        mx = glm::translate(mx, glm::vec3(-1.0f, -1.0f, 0.0f));
        //-> punkt(0,0) jest w lewym dolnym rogu, os y dodatnia do gory
        mx = glm::translate(mx, glm::vec3((2.0f*x)/winWidth, (2.0f*y)/winHeight, 0.0f));
        mx = glm::scale(mx, glm::vec3((2.0f*data.width)/winWidth, (2.0f*data.height)/winHeight, 1.0));
        shr->setUniform("mvp", mx);
        shr->setUniform("minx", data.x/(float)scaleW);
        shr->setUniform("maxx", (data.x+data.xadvance)/(float)scaleW);
        shr->setUniform("miny", (scaleH-data.y-lineHeight)/(float)scaleH);
        shr->setUniform("maxy", (scaleH-data.y)/(float)scaleH);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    void drawString(std::string str, int x, int y) {
        int tmpY = y, tmpX = x;
        for(int i = 0; i < str.size(); i++) {
            if(str[i] == '\n') {
                tmpX = x;
                tmpY -= lineHeight;
            }
            else {
                if(mapChars.find(str[i]) == mapChars.end())
                    continue;
                CharData data = mapChars[str[i]];
                drawChar(str[i], tmpX, tmpY);
                tmpX += data.xadvance;
            }
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

protected:
    GLuint vao;
    GLuint vbo;
    ShaderProgram* shr;
    Window * win;
};

}

#endif

