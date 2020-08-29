#include "Image.h"

#include "renderer/RenderFont.h"
#include "Exceptions/RenderingFontException.h"
#include "Exceptions/InitFontException.h"
#include "Exceptions/LoadingFontException.h"
#include "Exceptions/SetFontSizeException.h"

Image::Image(unsigned int width,unsigned int height){
    this->mHeight = height;
    this->mWidth = width;
    
    mPixels = new RGBA[width*height];   
}
Image::~Image(){
    /*
    for(int i=0;i<mWidth*mHeight;i++){
        delete mPixels[i];
    }
    */
    delete[] mPixels;
}

unsigned int Image::getWidth(){
    return this->mWidth;
}
unsigned int Image::getHeight(){
    return this->mHeight;
}
unsigned char* Image::getPixels(){
    return (unsigned char*)this->mPixels;
}

void Image::setPixel(unsigned int x,unsigned int y,unsigned char r,unsigned char g,unsigned char b,unsigned char a){
    RGBA pixel = RGBA();
    pixel.r = r;
    pixel.g = g;
    pixel.b = b;
    pixel.a = a;
    int index = y*mWidth +x;
    if(index > mWidth*mHeight) return;
    this->mPixels[index] = pixel;
}

unsigned int Image::getGlTexId(){
    return this->glTexId;
}

void Image::setGlTexId(unsigned int glTexId){
    this->glTexId = glTexId;
}

Image* Image::getDefaultImage(unsigned int width,unsigned int height,unsigned char r,unsigned char g,unsigned char b, unsigned char a){
    Image* img = new Image(512,512);
    for(int i=0; i < width;i++){
        for(int k=0;k < height;k++){
            img->setPixel(i,k,r,g,b,a);
        }        
    }
    return img;
}

Image* Image::getImageFromText(std::string text,Font font){
    RenderFont fontRenderer;
    try{
        fontRenderer.init();
        int fontSize = font.getFontSize();
        std::string fontFamily = font.getFontFamily();
        RGBA fontColor = font.getFontColor();
        RGBA backgroundColor = font.getBackgroundColor();
        fontRenderer.setFontFamily(fontFamily);
        fontRenderer.setFontSize(fontSize);
        fontRenderer.setFontColor(fontColor.r,fontColor.g,fontColor.b,fontColor.a);
        fontRenderer.setBgColor(backgroundColor.r,backgroundColor.g,backgroundColor.b,backgroundColor.a);
        Image* fontImg = fontRenderer.renderFont(text);
        return fontImg;
    }
    catch(InitFontException e){
        //std::cout << e.what()<<std::endl;
        //return;
        throw RenderingFontException(e.what());
    }
    catch(LoadingFontException e){
        //std::cout << e.what() << std::endl;
        //return;
        throw RenderingFontException(e.what());
    }
    catch(SetFontSizeException e){
        //std::cout << e.what() << std::endl;
        //return;
        throw RenderingFontException(e.what());
    }
}