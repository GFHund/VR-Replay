#ifndef __RENDER_FONT__
#define __RENDER_FONT__

#include "../Image.h"
#include "../pixelFormat/RGBA.h"
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

class RenderFont{
private:
    RGBA fontColor;
    RGBA bgColor;

    FT_Library library;
    FT_Face face;
public:
    RenderFont();
    ~RenderFont();

    void init();

    void setFontColor(unsigned char r,unsigned char g, unsigned char b,unsigned char a);
    void setBgColor(unsigned char r,unsigned char g, unsigned char b,unsigned char a);
    void setFontFamily(std::string fontfile);
    void setFontSize(unsigned int size);

    Image* renderFont(std::string text);
};

#endif