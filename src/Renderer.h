#ifndef __RENDERER__
#define __RENDERER__

#include "Abstract3dObject.h"

class Renderer{
    private: 
    int mWidth;
    int mHeight;
    public:
        void init(int width,int height);
        void init3DObject(Abstract3dObject* obj);
        void render();
        void render3DObject(Abstract3dObject* obj);
};

#endif