#include "Rectangle.h"
#include "Exceptions/IndexOutOfBoundsException.h"
/*
{ -1.0f, -1.0f,  1.f, 0.0f, 0.f,  0.f,1.f },
{  1.0f, -1.0f,  0.f, 0.5f, 0.f,  1.f,1.f },
{ -1.0f,  1.0f,  0.f, 0.0f, 1.f,  0.f,0.f },

{  1.0f, -1.0f,  0.5f,0.5f,0.5f,  1.f,1.f},
{  1.0f,  1.0f,  0.5f,0.5f,0.5f,  1.f,0.f},
{ -1.0f,  1.0f,  0.5f,0.5f,0.5f,  0.f,0.f}
*/

Rectangle::Rectangle(){
    //this->images[0];
}

Rectangle::~Rectangle(){
    delete mModel;
}

ModelData* Rectangle::getModelData(unsigned int& size){
    size = 6;
    if(mModel != nullptr){
        return mModel;
    }
    ModelData* model= new ModelData[6];
    
    model[0] = ModelData();
    model[0].x = -1.0f;
    model[0].y = -1.0f;
    model[0].z = -1.0f;
    model[0].u =  0.0f;
    model[0].v =  1.0f;

    model[1] = ModelData();
    model[1].x =  1.0f;
    model[1].y = -1.0f;
    model[1].z = -1.0f;
    model[1].u =  1.0f;
    model[1].v =  1.0f;

    model[2] = ModelData();
    model[2].x = -1.0f;
    model[2].y =  1.0f;
    model[2].z = -1.0f;
    model[2].u =  0.0f;
    model[2].v =  0.0f;

    model[3] = ModelData();
    model[3].x =  1.0f;
    model[3].y = -1.0f;
    model[3].z = -1.0f;
    model[3].u =  1.0f;
    model[3].v =  1.0f;

    model[4] = ModelData();
    model[4].x =  1.0f;
    model[4].y =  1.0f;
    model[4].z = -1.0f;
    model[4].u =  1.0f;
    model[4].v =  0.0f;

    model[5] = ModelData();
    model[5].x = -1.0f;
    model[5].y =  1.0f;
    model[5].z = -1.0f;
    model[5].u =  0.0f;
    model[5].v =  0.0f;

    mModel = model;

    return model;
}

Image* Rectangle::getImage(unsigned int index){
    if(index > 1){
        throw IndexOutOfBoundsException();
    }
    /*I don't know at the moment if the images[index] is no defined. The result may be undefined*/
    return this->images[index];
}
void Rectangle::setImage(unsigned int index,Image* image){
    if(index > 1){
        throw IndexOutOfBoundsException();
    }
    this->images[index] = image;
}

Shader* Rectangle::getShader(){
    return this->shader;
}
void Rectangle::setShader(Shader* shader){
    this->shader = shader;
}

void Rectangle::setVertexBuffer(int vertexBuffer){
    this->vertexBuffer = vertexBuffer;
}
int Rectangle::getVertexBuffer(){
    return this->vertexBuffer;
}