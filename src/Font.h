#ifndef __FONT__
#define __FONT__
#include "pixelFormat/RGBA.h"
class Font{
    protected:
    int mFontSize;
    std::string mFontFamily;
    RGBA mFontColor;
    RGBA mBgColor;

    public:
    void setFontSize(int size){
        this->mFontSize = size;
    }
    void setFontFamily(std::string family){
        this->mFontFamily = family;
    }
    void setFontColor(RGBA color){
        this->mFontColor = color;
    }
    void setBackgroundColor(RGBA color){
        this->mBgColor = color;
    }

    int getFontSize(){
        return this->mFontSize;
    }
    std::string getFontFamily(){
        return this->mFontFamily;
    }
    RGBA getFontColor(){
        return this->mFontColor;
    }
    RGBA getBackgroundColor(){
        return this->mBgColor;
    }
};

#endif