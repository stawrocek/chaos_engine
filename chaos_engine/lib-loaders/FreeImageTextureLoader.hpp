#include <FreeImage.h>

#ifndef FREEIMAGE_TEXTURE_LOADER_HPP
#define FREEIMAGE_TEXTURE_LOADER_HPP

class CHAOS_EXPORT TextureLoader{
public:
    TextureLoader()=delete;
    ~TextureLoader(){
        FreeImage_Unload(bitmap32);
        if(bpp != 32) {
            FreeImage_Unload(bitmap);
        }
    }
    TextureLoader(std::string fpath){
        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fpath.c_str(), 0);
        if(format == FIF_UNKNOWN) {
            #ifdef ANDROID
            LOGI("Failed to read format %s", fpath.c_str());
            #endif // ANDROID
            std::cout << "Failed to read format @ " << fpath.c_str() << "\n";
        }
        bitmap = FreeImage_Load(format, fpath.c_str());
        bitmap32 = nullptr;

        bpp = FreeImage_GetBPP(bitmap);
        if(bpp == 32)
            bitmap32 = bitmap;
        else
            bitmap32 = FreeImage_ConvertTo32Bits(bitmap);

        width = FreeImage_GetWidth(bitmap32);
        height = FreeImage_GetHeight(bitmap32);
        //SwapRedBlue32(bitmap32);
        textureData = NULL;
        textureData = FreeImage_GetBits(bitmap32);
        for(int i = 0; i < width*height; i++){
            char r = textureData[i*4+2];
            char g = textureData[i*4+1];
            char b = textureData[i*4];
            char a = textureData[i*4+3];
            textureData[i*4+0] = r;
            textureData[i*4+1] = g;
            textureData[i*4+2] = b;
            textureData[i*4+3] = a;
        }
    }

    GLuint width, height;
    GLubyte* textureData;
    FIBITMAP* bitmap;
    FIBITMAP* bitmap32;
    int bpp;
};

#endif // FREEIMAGE_TEXTURE_LOADER_HPP
