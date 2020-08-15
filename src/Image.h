#ifndef __IMAGE__
#define __IMAGE__
#include <array>
#include "pixelFormat/AbstractPixelFormat.h"
#include "pixelFormat/RGB.h"


class Image{
    private: 
        RGB* mPixels;
        unsigned int mWidth;
        unsigned int mHeight;
        unsigned int glTexId;

    public:
    enum PIXEL_FORMAT{
        PX_RGB,
        PX_Grey
    };
    Image(unsigned int width,unsigned int height){
        this->mHeight = height;
        this->mWidth = width;
        
        mPixels = new RGB[width*height];
        
    }
    ~Image(){
        /*
        for(int i=0;i<mWidth*mHeight;i++){
            delete mPixels[i];
        }
        */
        delete[] mPixels;
    }

    unsigned int getWidth(){
        return this->mWidth;
    }
    unsigned int getHeight(){
        return this->mHeight;
    }
    unsigned char* getPixels(){
        return (unsigned char*)this->mPixels;
    }

    void setPixel(unsigned int x,unsigned int y,unsigned int r,unsigned int g,unsigned int b){
        RGB pixel = RGB();
        pixel.r = r;
        pixel.g = g;
        pixel.b = b;
        int index = y*mWidth +x;
        if(index > mWidth*mHeight) return;
        this->mPixels[index] = pixel;
    }

    unsigned int getGlTexId(){
        return this->glTexId;
    }
    void setGlTexId(unsigned int glTexId){
        this->glTexId = glTexId;
    }

    static Image* getDefaultImage(unsigned int width,unsigned int height,unsigned int r,unsigned int g,unsigned int b){
        Image* img = new Image(512,512);
        for(int i=0; i < width;i++){
            for(int k=0;k < height;k++){
                img->setPixel(i,k,r,g,b);
            }        
        }
        return img;
    }
};

#endif