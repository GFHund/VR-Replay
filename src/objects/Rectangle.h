#ifndef __RECTANGLE__
#define __RECTANGLE__
#include "Abstract3dObject.h"
#include "../Image.h"

class Rectangle: public Abstract3dObject{
    private:
    
    ModelData* mModel = nullptr;
    unsigned short* mIndexdata = nullptr;

    public:
    Rectangle();
    ~Rectangle();
    ModelData* getModelData(unsigned int &size);
    unsigned short* getIndexData(unsigned int& size);

    
};

#endif