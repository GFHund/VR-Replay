#ifndef __ABSTRACT_3D_OBJECT__
#define __ABSTRACT_3D_OBJECT__
#include "ModelData.h"
#include "Image.h"
#include "Shader.h"

class Abstract3dObject{
    
    public:
    virtual ModelData* getModelData(unsigned int& size) = 0;
    virtual Image* getImage(unsigned int index) = 0;
    virtual Shader* getShader() = 0;
    virtual void setVertexBuffer(int vertexBuffer) = 0;
    virtual int getVertexBuffer() = 0;
};

#endif