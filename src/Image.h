#ifndef __IMAGE__
#define __IMAGE__
#include <array>
#include <string>
#include "pixelFormat/AbstractPixelFormat.h"
#include "pixelFormat/RGBA.h"
#include "Font.h"


class Image{
    private: 
        RGBA* mPixels;
        unsigned int mWidth;
        unsigned int mHeight;
        unsigned int glTexId;

    public:
    enum PIXEL_FORMAT{
        PX_RGB,
        PX_Grey
    };
    Image(unsigned int width,unsigned int height);
    ~Image();

    unsigned int getWidth();
    unsigned int getHeight();
    unsigned char* getPixels();

    void setPixel(unsigned int x,unsigned int y,unsigned char r,unsigned char g,unsigned char b,unsigned char a);

    unsigned int getGlTexId();
    void setGlTexId(unsigned int glTexId);

    static Image* getDefaultImage(
        unsigned int width,
        unsigned int height,
        unsigned char r,
        unsigned char g,
        unsigned char b, 
        unsigned char a);

    static Image* getImageFromText(std::string text,Font font);
};

#endif