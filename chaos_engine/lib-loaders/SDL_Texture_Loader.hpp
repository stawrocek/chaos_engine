#ifndef SDL_IMAGE_TEXTURE_LOADER_HPP
#define SDL_IMAGE_TEXTURE_LOADER_HPP

#include <SDL2/SDL_image.h>

class CHAOS_EXPORT TextureLoader{
public:
    TextureLoader()=delete;
    ~TextureLoader(){
        SDL_FreeSurface(image);
    }
    TextureLoader(std::string fpath){
        image=IMG_Load(fpath.c_str());
        if (image==NULL) {
            printf("IMG_Load: %s\n", IMG_GetError());
        }
        image=SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_ABGR8888,0);
        width=image->w;
        height=image->h;

        textureData=(GLubyte*)image->pixels;
    }

    GLuint width, height;
    GLubyte* textureData;

    SDL_Surface *image;
};

#endif // SDL_IMAGE_TEXTURE_LOADER_HPP


