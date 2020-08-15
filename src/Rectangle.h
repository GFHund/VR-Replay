#ifndef __RECTANGLE__
#define __RECTANGLE__
#include "Abstract3dObject.h"
#include "Image.h"

class Rectangle: public Abstract3dObject{
    private:
    Image* images[2];
    Shader* shader;
    ModelData* mModel = nullptr;
    int vertexBuffer;

    public:
    Rectangle();
    ~Rectangle();
    ModelData* getModelData(unsigned int &size);
    Image* getImage(unsigned int index);
    void setImage(unsigned int index,Image* image);

    Shader* getShader();
    void setShader(Shader* shader);

    void setVertexBuffer(int vertexBuffer);
    int getVertexBuffer();
};

#endif