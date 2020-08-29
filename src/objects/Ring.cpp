#include "Ring.h"
#include <math.h>

Ring::~Ring(){
    if(this->mModel != nullptr){
        delete[] mModel;
    }
    if(this->mIndexdata != nullptr){
        delete[] mIndexdata;
    }
}

ModelData* Ring::getModelData(unsigned int& size){
    if(mModel != nullptr){
        size = this->mModelSize;
        return this->mModel;
    }
    const float pi = 3.14159f;
    const float numberSegments = 16.0f;
    int iNumberSegments = (int)numberSegments;
    ModelData* ret = new ModelData[iNumberSegments*6];
    size = numberSegments*6;
    this->mModelSize = size;
    float inc = (2*pi)/numberSegments;
    int k = 0;
    for(float i = 0;i<2*pi;i+=inc,k+=6){
        float x = cos(i);
        float z = sin(i);
        
        float x1 = cos(i+inc);
        float z1 = sin(i+inc);
        float u = 0.0f;
        float u1 = 0.5f;
        if(k%12 >= 6){
            u = 0.5f;
            u1 = 1.0f;
        }
        float v = floor(k/12.0f) * (1.0f /8.0f);
        float v1 = ceil(k/12.0f) * (1.0f / 8.0f);

        ret[k].x = x;
        ret[k].y = -1.0f;
        ret[k].z = z;
        ret[k].u = u;
        ret[k].v = v1;

        ret[k+1].x = x1;
        ret[k+1].y = -1.0f;
        ret[k+1].z = z1;
        ret[k+1].u = u1;
        ret[k+1].v = v1;

        ret[k+2].x = x;
        ret[k+2].y = 1.0f;
        ret[k+2].z = z;
        ret[k+2].u = u;
        ret[k+2].v = v;

        ret[k+3].x = x1;
        ret[k+3].y = 1.0f;
        ret[k+3].z = z1;
        ret[k+3].u = u1;
        ret[k+3].v = v;

        ret[k+4].x = x;
        ret[k+4].y = 1.0f;
        ret[k+4].z = z;
        ret[k+4].u = u;
        ret[k+4].v = v;

        ret[k+5].x = x1;
        ret[k+5].y = -1.0f;
        ret[k+5].z = z1;
        ret[k+5].u = u1;
        ret[k+5].v = v1;
    }
    this->mModel = ret;
    return ret;
}

unsigned short* Ring::getIndexData(unsigned int& size){
    if(mIndexdata != nullptr){
        size = mIndexdataSize;
        return mIndexdata;
    }
    const float numberSegments = 16.0f;
    int iNumberSegments = numberSegments;
    unsigned short* ret = new unsigned short[iNumberSegments*6];
    for(int i=0;i<numberSegments*6;i++){
        ret[i] = i;
    }
    mIndexdata = ret;
    mIndexdataSize =  numberSegments*6;
    return ret;
}

Image* Ring::getImage(unsigned int index){}
Shader* Ring::getShader(){}