#ifndef RUBIK_HPP

#include <sstream>
#include <cstdlib>
#include <cmath>

#include "../../include/Scene.hpp"
#include "../../include/Camera.hpp"
#include "../../include/Primitives.hpp"
#include "../../include/Window.hpp"
#include "../../include/LightCaster.hpp"
#include "../../include/MeshPrefab.hpp"
#include "../../include/Model.hpp"
#include "../../include/Texture.hpp"
#include "../../include/Sprite.hpp"
#include "../../include/Shader.hpp"

class Cube: public chaos::Transform {
public:
    glm::vec4 color1, color2, color3, color4, color5, color6;
    GLfloat idx;
    Cube(){}
    Cube(glm::vec4 c1, glm::vec4 c2, glm::vec4 c3, glm::vec4 c4, glm::vec4 c5, glm::vec4 c6, GLfloat a)
    :color1(c1), color2(c2), color3(c3), color4(c4), color5(c5), color6(c6), idx(a)
    { }


    //compare float
    GLubyte cf(GLfloat x, GLfloat y, GLfloat epsilon=0.01){
        return fabs(x-y) <= epsilon;
    }

    //zwraca odleg³oœæ w rgba
    GLfloat sameColors(GLfloat r, GLfloat g, GLfloat b, GLfloat a, glm::vec4 v){
        //std::cout << r<<" "<<g<<" "<<b<<" "<<a<<" <----> "<<v.r<<" "<<v.g<<" "<<v.b<<" "<<v.a<<"\n";
        if((cf(r,v.r) && cf(g,v.g) && cf(b,v.b) && cf(a,v.a))){
            return sqrt((r-v.r)*(r-v.r)+(g-v.g)*(g-v.g)+(b-v.b)*(b-v.b)+(a-v.a)*(a-v.a));
        }
        return 1000.0;
    }

    //zwraca informacjê o tym czy klocek zosta³ klikniety, je¿eli tak to zwraca odleg³oœæ w przestrzeni kolorów
    GLfloat cubeClicked(GLfloat r, GLfloat g, GLfloat b, GLfloat a, int& face){
        //std::cout << "cc: " << r << " " << g << " " << b << " " << a << "\n";
        glm::vec4 idv=idxVector()/100.0f;
        if(sameColors(r,g,b,a,color1-idv) < 500.0){
            face=1;
            return sameColors(r,g,b,a,color1-idv);
        }
        if(sameColors(r,g,b,a,color2-idv) < 500.0){
            face=2;
            return sameColors(r,g,b,a,color2-idv);
        }
        if(sameColors(r,g,b,a,color3-idv) < 500.0){
            face=3;
            return sameColors(r,g,b,a,color3-idv);
        }
        if(sameColors(r,g,b,a,color4-idv) < 500.0){
            face=4;
            return sameColors(r,g,b,a,color4-idv);
        }
        if(sameColors(r,g,b,a,color5-idv) < 500.0){
            face=5;
            return sameColors(r,g,b,a,color5-idv);
        }
        if(sameColors(r,g,b,a,color6-idv) < 500.0){
            face=6;
            return sameColors(r,g,b,a,color6-idv);
        }
        return 1000.0;
    }

    //zwraca unikatowy wektor dla ka¿dego klocka (dzieki temu ka¿dy ma inny kolor) -> color-picking
    glm::vec4 idxVector(){
        if(idx==0)return glm::vec4(0,0,0,0);
        if(idx==1)return glm::vec4(0,0,1,0);
        if(idx==2)return glm::vec4(0,0,2,0);
        if(idx==3)return glm::vec4(0,0,3,0);
        if(idx==4)return glm::vec4(0,1,0,0);
        if(idx==5)return glm::vec4(0,1,1,0);
        if(idx==6)return glm::vec4(0,1,2,0);
        if(idx==7)return glm::vec4(0,1,3,0);
        if(idx==8)return glm::vec4(0,2,0,0);
        if(idx==9)return glm::vec4(0,2,1,0);
        if(idx==10)return glm::vec4(0,2,2,0);
        if(idx==11)return glm::vec4(0,2,3,0);
        if(idx==12)return glm::vec4(0,3,0,0);
        if(idx==13)return glm::vec4(0,3,1,0);
        if(idx==14)return glm::vec4(0,3,2,0);
        if(idx==15)return glm::vec4(0,3,3,0);
        if(idx==16)return glm::vec4(1,0,0,0);
        if(idx==17)return glm::vec4(1,0,1,0);
        if(idx==18)return glm::vec4(1,0,2,0);
        if(idx==19)return glm::vec4(1,0,3,0);
        if(idx==20)return glm::vec4(1,1,0,0);
        if(idx==21)return glm::vec4(1,1,1,0);
        if(idx==22)return glm::vec4(1,1,2,0);
        if(idx==23)return glm::vec4(1,1,3,0);
        if(idx==24)return glm::vec4(1,2,0,0);
        if(idx==25)return glm::vec4(1,2,1,0);
        if(idx==26)return glm::vec4(1,2,2,0);
        if(idx==27)return glm::vec4(1,2,3,0);
        return glm::vec4(-1,-1,-1,0);
    }

    //rysuje, œciana po œcianie kostkê
    void draw(GLuint shaderProgram, GLuint vbo){
        glm::vec4 idv=idxVector()/100.0f;
        glUseProgram (shaderProgram);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        GLint mxLocation = glGetUniformLocation(shaderProgram, "mx");
        GLint colorLocation = glGetUniformLocation(shaderProgram, "uniColor");
        glm::mat4 mx = getGlobalTransformMatrix();
        glUniformMatrix4fv(mxLocation, 1, GL_FALSE, glm::value_ptr(mx));

        glm::vec4 c1 = color1-idv;
        glUniform4fv(colorLocation, 1, glm::value_ptr(c1));
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glm::vec4 c2 = color2-idv;
        glUniform4fv(colorLocation, 1, glm::value_ptr(c2));
        glDrawArrays(GL_TRIANGLES, 6, 6);

        glm::vec4 c3 = color3-idv;
        glUniform4fv(colorLocation, 1, glm::value_ptr(c3));
        glDrawArrays(GL_TRIANGLES, 12, 6);

        glm::vec4 c4 = color4-idv;
        glUniform4fv(colorLocation, 1, glm::value_ptr(c4));
        glDrawArrays(GL_TRIANGLES, 18, 6);

        glm::vec4 c5 = color5-idv;
        glUniform4fv(colorLocation, 1, glm::value_ptr(c5));
        glDrawArrays(GL_TRIANGLES, 24, 6);

        glm::vec4 c6 = color6-idv;
        glUniform4fv(colorLocation, 1, glm::value_ptr(c6));
        glDrawArrays(GL_TRIANGLES, 30, 6);

        glUseProgram (0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};


struct RotationAction{
    RotationAction(){}
    RotationAction(int rs, char a, int h)
            :rotSign(rs), axis(a), height(h)
    {}
    int rotSign=1;      // w któr¹ stronê obracamy (-1,1}
    char axis='x';      // {'x','y','z'}
    int height=0;       // {0,1,...,cubeSize}
    int progress=0;     // [0,(pi/2)/rotSpeed], rotSpeed=0.03 => [0,~52]
};

struct TouchDownAction{
    TouchDownAction(){}
    TouchDownAction(GLfloat _x, GLfloat _y)
    :x(_x), y(_y)
    {}
    GLfloat x;
    GLfloat y;
};

struct ScrollAction{
    ScrollAction(){}
    ScrollAction(float _x, float _y, float tX, float tY, float dX, float dY)
    :x(_x), y(_y), targetX(tX), targetY(tY), distX(dX), distY(dY)
    {}
    float x;
    float y;
    float targetX;
    float targetY;
    float distX;
    float distY;
};

struct InputState{
    bool active=false;
    int cube1X, cube1Y, cube1Z;
    int cube2X, cube2Y, cube2Z;
    int face1, face2;
    int mouseX, mouseY;

    InputState(){
        reset();
    }

    void reset(){
        active=false;
        cube1X=-1;
        cube1Y=-1;
        cube1Z=-1;
        cube2X=-1;
        cube2Y=-1;
        cube2Z=-1;
        mouseX=-1000000;
        mouseY=-1000000;
        face1=-1;
        face2=-1;
    }
};

template <typename T>
std::string numberToString ( T Number ) {
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

class Rubik: public chaos::Scene{
public:
    Rubik(std::string _name)
    :Scene(_name)
    {}

    void onSceneLoadToMemory(){
        camera = new chaos::Camera(renderer, chaos::PERSPECTIVE, glm::perspective(glm::radians(45.0f), (GLfloat)window->getStyle().width/window->getStyle().height, 0.1f, 100.0f));
        camera->moveZ(5);
        renderer->setActiveCamera(camera);
        window->setRelativeMode(true);



            //region vShaderStr
        vShaderStr =    "#version 330 core\n"
                        "layout (location = 0) in vec3 position;\n"
                        "uniform mat4 mx;\n"
                        "void main()\n"
                        "{\n"
                        "   gl_Position = mx*vec4(position, 1.0);\n"
                        "}\n";
        //endregion
        //region fShaderStr
        fShaderStr =    "#version 330 core\n"
                        "uniform vec4 uniColor;\n"
                        "out vec4 color;\n"
                        "void main()\n"
                        "{\n"
                        "   color = uniColor;\n"
                        "}\n";
        //endregion
        //region vx
        vecCube = {
                -1.f, -1.f, -1.f,
                1.f, -1.f, -1.f,
                1.f,  1.f, -1.f,
                1.f,  1.f, -1.f,
                -1.f,  1.f, -1.f,
                -1.f, -1.f, -1.f,

                -1.f, -1.f,  1.f,
                1.f, -1.f,  1.f,
                1.f,  1.f,  1.f,
                1.f,  1.f,  1.f,
                -1.f,  1.f,  1.f,
                -1.f, -1.f,  1.f,

                -1.f,  1.f,  1.f,
                -1.f,  1.f, -1.f,
                -1.f, -1.f, -1.f,
                -1.f, -1.f, -1.f,
                -1.f, -1.f,  1.f,
                -1.f,  1.f,  1.f,

                1.f,  1.f,  1.f,
                1.f,  1.f, -1.f,
                1.f, -1.f, -1.f,
                1.f, -1.f, -1.f,
                1.f, -1.f,  1.f,
                1.f,  1.f,  1.f,

                -1.f, -1.f, -1.f,
                1.f, -1.f, -1.f,
                1.f, -1.f,  1.f,
                1.f, -1.f,  1.f,
                -1.f, -1.f,  1.f,
                -1.f, -1.f, -1.f,

                -1.f,  1.f, -1.f,
                1.f,  1.f, -1.f,
                1.f,  1.f,  1.f,
                1.f,  1.f,  1.f,
                -1.f,  1.f,  1.f,
                -1.f,  1.f, -1.f
        };
        //endregion
        //tworzenie shaderów
        //vertexShader = loadShader ( GL_VERTEX_SHADER, vShaderStr.c_str() );
        //fragmentShader = loadShader ( GL_FRAGMENT_SHADER, fShaderStr.c_str() );

        chaos::Shader shrVertex;
        shrVertex.loadFromString(vShaderStr, GL_VERTEX_SHADER);
        chaos::Shader shrFragment;
        shrFragment.loadFromString(fShaderStr, GL_FRAGMENT_SHADER);
        shr = new chaos::ShaderProgram({shrVertex, shrFragment});
        /*g_ProgramObject = glCreateProgram ( );
        glAttachShader ( g_ProgramObject, vertexShader );
        glAttachShader ( g_ProgramObject, fragmentShader );
        glLinkProgram ( g_ProgramObject );
        GLint linked;
        glGetProgramiv ( g_ProgramObject, GL_LINK_STATUS, &linked );
        GLsizei Length    = 0;
        GLsizei MaxLength = 0;
        glGetProgramiv( g_ProgramObject, GL_INFO_LOG_LENGTH, &MaxLength );
        char* InfoLog = new char[MaxLength];
        glGetProgramInfoLog( g_ProgramObject, MaxLength, &Length, InfoLog );
        SHOUT( "InfoLog: %s", InfoLog );*/

        //potrzebne w color-pickingu
        glDisable(GL_DITHER);

        //tworzenie vecCubes i rootTransform
        vecCubes.resize(cubeSize);
        rootTransforms.resize(cubeSize);
        GLint a=0;
        for(int i = 0; i < cubeSize; i++){
            vecCubes[i].resize(cubeSize);
            rootTransforms[i].resize(cubeSize);
            for(int j = 0; j < cubeSize; j++){
                vecCubes[i][j].resize(cubeSize);
                rootTransforms[i][j].resize(cubeSize);
                for(int k = 0; k < cubeSize; k++){
                    rootTransforms[i][j][k].setScale(0.1,0.1,0.1);
                    rootTransforms[i][j][k].setParent(&cubeTransform);
                    vecCubes[i][j][k] = Cube(glm::vec4(1.0f,0.03f,0.03f,1.0f),glm::vec4(1.0f,1.0f,0.03f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(0.03f,0.03f,1.0f,1.0f), glm::vec4(0.03f,1.0f,0.03f,1.0f),glm::vec4(1.0f,0.55f,0.03f,1.0f), a);
                    vecCubes[i][j][k].setParent(&rootTransforms[i][j][k]);
                    vecCubes[i][j][k].setPosition(((GLfloat)i)*2.05f-2.05f, ((GLfloat)j)*2.05f-2.05f,((GLfloat)k)*2.05f-2.05f);
                    a++;
                }
            }
        }

        //poczatkowy obrót kostki
        cubeTransform.setRotZ(3.1415/4.0f);
        cubeTransform.setRotY(3.1415/4.0f);
        cubeTransform.setRotX(3.1415/4.0f);

        //uzupe³nianie vecRotations wszyskimi mo¿liwymi rotacjami
        for(int axis = 0; axis < 3; axis++){
            for(int sign = -1; sign < 2; sign+=2){
                for(int i = 0; i < cubeSize; i++){
                    vecRotations.push_back(RotationAction(sign, 'x'+axis, i));
                }
            }
        }
        actRotation = vecRotations[0];

        //tworzenie vbo
        pos1 = glGetAttribLocation( shr->getId(), "position" );
        glGenBuffers(1, &vbo1);
        glBindBuffer(GL_ARRAY_BUFFER, vbo1);
        glBufferData(GL_ARRAY_BUFFER, vecCube.size()*sizeof(GLfloat), vecCube.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(pos1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
        glEnableVertexAttribArray(pos1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glEnable(GL_DEPTH_TEST);

        srand(time(NULL));
        restartGame();
    }

    void onSceneActivate(){

    }

    void draw(GLfloat deltaTime){
        GLfloat moveSpeed = 1.0;
        if(window->isKeyDown(chaos::KeyboardEvent::KeyA)) camera->processKeyboard(chaos::LEFT, deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyD)) camera->processKeyboard(chaos::RIGHT, deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyW)) camera->processKeyboard(chaos::FORWARD, deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyS)) camera->processKeyboard(chaos::BACKWARD, deltaTime*moveSpeed);

        renderer->setCamCombined(camera->getProjectionMatrix()*camera->getViewMatrix());

        window->clearColor(0.7, 0.2, 0.2, 1.0);
        r += 0.01;

        //fizyczne obracanie kostekw obrêbie aktualnej rotacji
        if(isRotating) {
            if (actRotation.axis == 'x') {
                for (int i = 0; i < cubeSize; i++)
                    for (int j = 0; j < cubeSize; j++)
                        vecCubes[actRotation.height][i][j].getParent()->rotateX(
                                rotSpeed * actRotation.rotSign);
            }
            if (actRotation.axis == 'y') {
                for (int i = 0; i < cubeSize; i++)
                    for (int j = 0; j < cubeSize; j++)
                        vecCubes[i][actRotation.height][j].getParent()->rotateY(
                                rotSpeed * actRotation.rotSign);
            }
            if (actRotation.axis == 'z') {
                for (int i = 0; i < cubeSize; i++)
                    for (int j = 0; j < cubeSize; j++)
                        vecCubes[i][j][actRotation.height].getParent()->rotateZ(
                                rotSpeed * actRotation.rotSign);
            }
            //resetowanie fizycznej rotacji i obroty kolorów
            if (actRotation.progress >= ((3.1415 / 2.0) / rotSpeed)) {//52.35
                actRotation.progress = 0;
                for (int i = 0; i < cubeSize; i++)
                    for (int j = 0; j < cubeSize; j++)
                        for (int k = 0; k < cubeSize; k++)
                            rootTransforms[i][j][k].setRotation(0.0f, 0.0f, 0.0f);
                rotateColors();
                //actRotation = vecRotations[0 + rand() % 18];
                isRotating=false;
            }
            actRotation.progress++;
        }
        //renderowanie kostki
        //glUseProgram ( g_ProgramObject );
        shr->run();
        for(int i = 0; i < cubeSize; i++){
            for(int j = 0; j < cubeSize; j++){
                for(int k = 0; k < cubeSize; k++) {
                    vecCubes[i][j][k].draw(shr->getId(), vbo1);
                }
            }
        }
        //wywo³ywanie color-pickingu je¿eli gracz wykona³ odpowiedni¹ akcjê
        if(isTouchDown){
            completeGestureTouchDown();
            isTouchDown=false;
        }
        if(isScroll){
            completeGestureScroll();
            isScroll=false;
        }
    }

    void deliverEvent(chaos::Event* event){
        if(event->type == chaos::Event::MouseMotion){
            camera->processMouse(event->motionEvent.relX, -event->motionEvent.relY);
        }
    }

    void restartGame(){
        RotationAction bp;
        int restartCount = 4;
        for(int i = 0; i < restartCount; i++){
            actRotation = vecRotations[rand()%vecRotations.size()];
            rotateColors();
        }
        actRotation = bp;
        timer=0;
    }
    std::string getTimerString(){
        timer++;
        return " time: " + numberToString<int>(timer) +"s";
    }

    void completeGestureTouchDown(){
        GLint minX=-1, minY=-1, minZ=-1;
        int face=findClickedCube(minX, minY, minZ, actTouchDown.x, screenHeight-actTouchDown.y);
        if(minX!=-1){
            if(!isRotating && actInputState.cube1X==-1){
                actInputState.cube1X = minX;
                actInputState.cube1Y = minY;
                actInputState.cube1Z = minZ;
                actInputState.face1 = face;
                SHOUT("found vec1: (%d,%d,%d)\n", minX, minY, minZ);
                //vecCubes[minX][minY][minZ].buildBackup();
                //vecCubes[minX][minY][minZ].setColor();
            }
        }
        else{
            if(actInputState.cube1X == -1){
                actInputState.mouseX=actTouchDown.x;
                actInputState.mouseY=actTouchDown.y;
                actInputState.active=true;
            }
        }
    }
    void completeGestureScroll(){
        if(actInputState.active){
            cubeTransform.rotateY(actScroll.distX*0.005);
            cubeTransform.rotateX(actScroll.distY*0.005);
        }
        else if(actInputState.cube1X != -1){
            GLint minX=-1, minY=-1, minZ=-1;
            int face = findClickedCube(minX, minY, minZ, actScroll.targetX, screenHeight-actScroll.targetY);
            if(!(minX == -1 || minY == -1 || minZ == -1)){
                if(actInputState.cube2X==-1 && (actInputState.cube1X != minX || actInputState.cube1Y != minY || actInputState.cube1Z != minZ)){
                    actInputState.cube2X = minX;
                    actInputState.cube2Y = minY;
                    actInputState.cube2Z = minZ;
                    actInputState.face2 = face;
                    //vecCubes[minX][minY][minZ].buildBackup();
                    //vecCubes[minX][minY][minZ].setColor(glm::vec4(0.3f,0.3f,0.3f,1.0f),glm::vec4(0.3f,0.3f,0.3f,1.0f),glm::vec4(0.3f,0.3f,0.3f,1.0f),
                    //                                        glm::vec4(0.3f,0.3f,0.3f,1.0f),glm::vec4(0.3f,0.3f,0.3f,1.0f),glm::vec4(0.3f,0.3f,0.3f,1.0f));
                    makeNewRotation();
                }
            }
        }
    }

    void rotateColors(){
        int h = actRotation.height;
        int s = actRotation.rotSign;
        if(actRotation.axis == 'x'){
            std::vector<std::vector<std::vector<glm::vec4> > > backup;
            backup.resize(cubeSize);
            for(int i = 0; i < cubeSize; i++){
                backup[i].resize(cubeSize);
                for(int j = 0; j < cubeSize; j++){
                    backup[i][j].resize(6);
                    backup[i][j][0]=vecCubes[h][i][j].color1;
                    backup[i][j][1]=vecCubes[h][i][j].color2;
                    backup[i][j][2]=vecCubes[h][i][j].color3;
                    backup[i][j][3]=vecCubes[h][i][j].color4;
                    backup[i][j][4]=vecCubes[h][i][j].color5;
                    backup[i][j][5]=vecCubes[h][i][j].color6;
                }
            }
            for(int i = 0; i < cubeSize; i++)
                for(int j = 0; j < cubeSize; j++){
                    vecCubes[h][i][j].color6 = (s==-1 ? backup[j][2-i][1] : backup[2-j][i][0]);
                    vecCubes[h][i][j].color1 = (s==-1 ? backup[j][2-i][5] : backup[2-j][i][4]);
                    vecCubes[h][i][j].color5 = (s==-1 ? backup[j][2-i][0] : backup[2-j][i][1]);
                    vecCubes[h][i][j].color2 = (s==-1 ? backup[j][2-i][4] : backup[2-j][i][5]);

                    vecCubes[h][i][j].color3 = (s==-1 ? backup[j][2-i][2] : backup[2-j][i][2]);
                    vecCubes[h][i][j].color4 = (s==-1 ? backup[j][2-i][3] : backup[2-j][i][3]);
                }
        }
        if(actRotation.axis == 'y'){
            std::vector<std::vector<std::vector<glm::vec4> > > backup;
            backup.resize(cubeSize);
            for(int i = 0; i < cubeSize; i++){
                backup[i].resize(cubeSize);
                for(int j = 0; j < cubeSize; j++){
                    backup[i][j].resize(6);
                    backup[i][j][0]=vecCubes[i][h][j].color1;
                    backup[i][j][1]=vecCubes[i][h][j].color2;
                    backup[i][j][2]=vecCubes[i][h][j].color3;
                    backup[i][j][3]=vecCubes[i][h][j].color4;
                    backup[i][j][4]=vecCubes[i][h][j].color5;
                    backup[i][j][5]=vecCubes[i][h][j].color6;
                }
            }
            for(int i = 0; i < cubeSize; i++)
                for(int j = 0; j < cubeSize; j++){
                    vecCubes[i][h][j].color1 = (s==1 ? backup[j][2-i][3] : backup[2-j][i][2]);
                    vecCubes[i][h][j].color3 = (s==1 ? backup[j][2-i][0] : backup[2-j][i][1]);
                    vecCubes[i][h][j].color2 = (s==1 ? backup[j][2-i][2] : backup[2-j][i][3]);
                    vecCubes[i][h][j].color4 = (s==1 ? backup[j][2-i][1] : backup[2-j][i][0]);

                    vecCubes[i][h][j].color5 = (s==1 ? backup[j][2-i][4] : backup[2-j][i][4]);
                    vecCubes[i][h][j].color6 = (s==1 ? backup[j][2-i][5] : backup[2-j][i][5]);
                }
        }
        if(actRotation.axis == 'z'){
            std::vector<std::vector<std::vector<glm::vec4> > > backup;
            backup.resize(cubeSize);
            for(int i = 0; i < cubeSize; i++){
                backup[i].resize(cubeSize);
                for(int j = 0; j < cubeSize; j++){
                    backup[i][j].resize(6);
                    backup[i][j][0]=vecCubes[i][j][h].color1;
                    backup[i][j][1]=vecCubes[i][j][h].color2;
                    backup[i][j][2]=vecCubes[i][j][h].color3;
                    backup[i][j][3]=vecCubes[i][j][h].color4;
                    backup[i][j][4]=vecCubes[i][j][h].color5;
                    backup[i][j][5]=vecCubes[i][j][h].color6;
                }
            }
            for(int i = 0; i < cubeSize; i++)
                for(int j = 0; j < cubeSize; j++){
                    vecCubes[i][j][h].color6 = (s==1 ? backup[j][2-i][3] : backup[2-j][i][2]);
                    vecCubes[i][j][h].color3 = (s==1 ? backup[j][2-i][5] : backup[2-j][i][4]);
                    vecCubes[i][j][h].color5 = (s==1 ? backup[j][2-i][2] : backup[2-j][i][3]);
                    vecCubes[i][j][h].color4 = (s==1 ? backup[j][2-i][4] : backup[2-j][i][5]);

                    vecCubes[i][j][h].color1 = (s==1 ? backup[j][2-i][0] : backup[2-j][i][0]);
                    vecCubes[i][j][h].color2 = (s==1 ? backup[j][2-i][1] : backup[2-j][i][1]);
                }
        }
    }

    int findClickedCube(GLint &minX, GLint &minY, GLint& minZ, GLint posX, GLint posY){
        GLfloat pixel[4];
        GLubyte pixel2[4];
        glReadPixels(posX, posY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel2);
        pixel[0] = ((GLfloat)pixel2[0])/255.0f;
        pixel[1] = ((GLfloat)pixel2[1])/255.0f;
        pixel[2] = ((GLfloat)pixel2[2])/255.0f;
        pixel[3] = ((GLfloat)pixel2[3])/255.0f;
        //LOGI("colors: (%f,%f,%f,%f)", pixel[0],pixel[1],pixel[2],pixel[3]);
        GLfloat mini = 1000.0;
        int retFace=-1;
        for(int i = 0; i < cubeSize; i++){
            for(int j = 0; j < cubeSize; j++){
                for(int k = 0; k < cubeSize; k++){
                    int bp=retFace;
                    if(vecCubes[i][j][k].cubeClicked(pixel[0],pixel[1],pixel[2],pixel[3], retFace) < mini){
                        mini = vecCubes[i][j][k].cubeClicked(pixel[0],pixel[1],pixel[2],pixel[3], retFace);
                        minX=i;
                        minY=j;
                        minZ=k;
                    }
                    else
                        retFace=bp;
                }
            }
        }
        return retFace;
    }

    void makeNewRotation() {
        SHOUT("vec1: (%d,%d,%d), vec2: (%d,%d,%d)\n", actInputState.cube1X,actInputState.cube1Y,actInputState.cube1Z,
             actInputState.cube2X,actInputState.cube2Y,actInputState.cube2Z);
        SHOUT("face1: %d, face2: %d", actInputState.face1, actInputState.face2);
        //actRotation = vecRotations[rand() % vecRotations.size()];
        GLint sum1 = actInputState.cube1X+actInputState.cube1Y + actInputState.cube1Z;
        GLint sum2 = actInputState.cube2X+actInputState.cube2Y + actInputState.cube2Z;
        if(abs(sum1-sum2) != 1 || actInputState.face1 != actInputState.face2)     //shouldn't happen!
            return;
        actRotation.progress=0;
        actRotation.rotSign=1;

        if(actInputState.face1 == 5 || actInputState.face1 == 6){
            if(abs(actInputState.cube2X-actInputState.cube1X)==1){
                actRotation.axis = 'z';
                actRotation.height = actInputState.cube1Z;
                if(actInputState.cube2X < actInputState.cube1X)
                    actRotation.rotSign=-1;

            }
            if(abs(actInputState.cube2Z-actInputState.cube1Z)==1){
                actRotation.axis = 'x';
                actRotation.height = actInputState.cube1X;
                if(actInputState.cube2Z < actInputState.cube1Z)
                    actRotation.rotSign=-1;
            }
            isRotating=true;
            if(actInputState.face1 == 6)
                actRotation.rotSign *= -1;
        }
        if(actInputState.face1 == 1 || actInputState.face1 == 2){
            if(abs(actInputState.cube2X-actInputState.cube1X)==1) {
                actRotation.axis = 'y';
                actRotation.height = actInputState.cube1Y;
                if (actInputState.cube2X < actInputState.cube1X)
                    actRotation.rotSign = -1;
                actRotation.rotSign *= -1;
            }
            if(abs(actInputState.cube2Y-actInputState.cube1Y)==1){
                SHOUT("YYYYY");
                actRotation.axis = 'x';
                actRotation.height = actInputState.cube1X;
                if(actInputState.cube2Y < actInputState.cube1Y)
                    actRotation.rotSign=-1;
            }
            isRotating=true;
            if(actInputState.face1 == 2)
                actRotation.rotSign *= -1;
        }
        if(actInputState.face1 == 3 || actInputState.face1 == 4) {
            if (abs(actInputState.cube2Y - actInputState.cube1Y) == 1) {
                actRotation.axis = 'z';
                actRotation.height = actInputState.cube1Z;
                if (actInputState.cube2Y < actInputState.cube1Y)
                    actRotation.rotSign = -1;
                actRotation.rotSign *= -1;
            }
            if (abs(actInputState.cube2Z - actInputState.cube1Z) == 1) {
                actRotation.axis = 'y';
                actRotation.height = actInputState.cube1Y;
                if (actInputState.cube2Z < actInputState.cube1Z)
                    actRotation.rotSign = -1;
                actRotation.rotSign *= -1;
            }
            isRotating=true;
            if(actInputState.face1 == 4)
                actRotation.rotSign *= -1;
        }
    }

    std::string vShaderStr;
    std::string fShaderStr;
    //wierzcho³ki kostki
    std::vector<GLfloat> vecCube;

    const int cubeSize = 3;
    //27 kostek
    std::vector<std::vector<std::vector<Cube> > > vecCubes;
    //odpowiada za obroty wzglêdem (0,0,0)
    std::vector<std::vector<std::vector<chaos::Transform> > > rootTransforms;

    //odpowiada za obracanie ca³ej kostki
    chaos::Transform cubeTransform;
    //zawiera wszyskie mozliwe rotacje
    std::vector<RotationAction> vecRotations;

    //obecna rotacja
    RotationAction actRotation;
    bool isRotating=false;

    //szerokoœæ i wysokoœc ekranu, uaktualniane w onSurfaceChanged
    GLuint screenWidth, screenHeight;
    bool isTouchDown=false;
    TouchDownAction actTouchDown;
    bool isScroll=false;
    ScrollAction    actScroll;
    InputState actInputState;
    int timer=0;

private:
    chaos::Camera* camera;

    GLfloat r=0.0;
    //GLuint vertexShader;
    //GLuint fragmentShader;
    chaos::ShaderProgram* shr=nullptr;
    //GLuint g_ProgramObject = 0;

    GLuint vbo1;
    GLuint pos1;
    double rotSpeed=0.03;

    static GLuint loadShader(GLenum type, const char* shaderSrc){
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &shaderSrc, NULL);
        glCompileShader(shader);
        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        GLsizei maxLength=0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength];
        glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);
        SHOUT("Shader info log: %s\n", infoLog);
        return shader;
    }
};

#endif // RUBIK_HPP
