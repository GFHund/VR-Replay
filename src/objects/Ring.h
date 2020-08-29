#ifndef __RING__
#define __RING__

#include "Abstract3dObject.h"
#include "../Image.h"

class Ring: public Abstract3dObject{
private:
    Image* images[2];
    Shader* shader;
    ModelData* mModel = nullptr;
    unsigned short* mIndexdata = nullptr;
    int mModelSize;
    int mIndexdataSize;
    int vertexBuffer;

    public:
    ~Ring();
    ModelData* getModelData(unsigned int& size);
    unsigned short* getIndexData(unsigned int& size);
    Image* getImage(unsigned int index);
    Shader* getShader();
    void setVertexBuffer(int vertexBuffer);
    int getVertexBuffer();
};

#endif