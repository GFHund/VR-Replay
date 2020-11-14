#ifndef __CUBE__
#define __CUBE__
#include "Abstract3dObject.h"

class Cube: public Abstract3dObject{
    private:
    ModelData* mModel = nullptr;
    unsigned short* mIndexdata = nullptr;

    public:
    ModelData* getModelData(unsigned int& size);
    unsigned short* getIndexData(unsigned int& size);
};

#endif