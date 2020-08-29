#ifndef __RGBA__
#define __RGBA__
#include "AbstractPixelFormat.h"
class RGBA: public AbstractPixelFormat{
    public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

#endif