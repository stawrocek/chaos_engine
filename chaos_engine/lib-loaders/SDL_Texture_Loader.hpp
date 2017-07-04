#ifndef SDL_IMAGE_TEXTURE_LOADER_HPP
#define SDL_IMAGE_TEXTURE_LOADER_HPP

#define TEXTURES_SDLIMAGE

#include <SDL2/SDL_image.h>

class CHAOS_EXPORT SDLTextureLoader: public chaos::TextureLoader{
public:
    SDLTextureLoader(){
        initializeTextureLoader();
    }
    ~SDLTextureLoader(){
        SDL_FreeSurface(image);
    }
    SDLTextureLoader(std::string& fpath){
        loadTexture(fpath);
    }

    void loadTexture(std::string& fpath) override {
        SHOUT("sdlimage is trying to read texture from %s\n", fpath.c_str());
        image=IMG_Load(fpath.c_str());
        if (image==NULL) {
            printf("IMG_Load: %s\n", IMG_GetError());
        }
        image=SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_ABGR8888,0);
        width=image->w;
        height=image->h;

        textureData=(GLubyte*)image->pixels;
    }

    GLboolean initializeTextureLoader() override {
        int flags=IMG_INIT_JPG|IMG_INIT_PNG;
        int initted=IMG_Init(flags);
        if((initted&flags) != flags) {
            printf("IMG_Init: Failed to init required jpg and png support! %s\n", IMG_GetError());
            return false;
        }
        else{
            return true;
        }
    }

protected:
    SDL_Surface *image;
};

#endif // SDL_IMAGE_TEXTURE_LOADER_HPP


