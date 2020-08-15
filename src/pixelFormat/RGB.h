#ifndef __RGB__
#define __RGB__
#include "AbstractPixelFormat.h"
class RGB: public AbstractPixelFormat{
    public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

#endif