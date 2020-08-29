#include "Rectangle.h"

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
    if(mModel != nullptr){
        delete[] mModel;
    }
    if(mIndexdata != nullptr){
        delete[] mIndexdata;
    }
    
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


unsigned short* Rectangle::getIndexData(unsigned int& size){
    size = 6;
    if(mIndexdata != nullptr){
        return mIndexdata;
    }
    unsigned short* indexData = new unsigned short[6];

    indexData[0] = 0;
    indexData[1] = 1;
    indexData[2] = 2;
    indexData[3] = 3;
    indexData[4] = 4;
    indexData[5] = 5;

    mIndexdata = indexData;

    return indexData;
}


