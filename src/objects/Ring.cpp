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
    //std::cout << "ModelSize: " << size << std::endl;
    this->mModelSize = size;
    float inc = (2*pi)/numberSegments;
    int k = 0;
    //std::cout << "Vertices index "<<std::endl;
    float scale = 1.5f;
    float v,v1;

    for(float i = 0;i<2*pi;i+=inc,k+=6){
        //std::cout << i <<std::endl;
        float x = cos(i) * scale;
        float z = sin(i) * scale;
        
        float x1 = cos(i+inc) * scale;
        float z1 = sin(i+inc) * scale;
        float y = 0.0f;
        float y1 = 0.9f;
        /*
        float u = 0.0f;
        float u1 = 0.5f;
        if(k%12 >= 6){
            u = 0.5f;
            u1 = 1.0f;
        }
        */

        //v = floor(k/12.0f) * (1.0f /8.0f);
        //v1 = ceil(k/12.0f) * (1.0f / 8.0f);
        int numSegment = k/6;
        std::cout << "segment: " << numSegment << std::endl;
        //int row = (int)((int)(((float)numSegment) / 4.0f) - (numSegment) % 4);
        int row = (numSegment - numSegment % 4) /4;
        float u = (numSegment % 4)*0.25f;
        float u1 = (numSegment % 4+1)*0.25f;
        v = row * 0.25f;
        v1 = (row+1.0f) * 0.25f;

        ret[k].x = x;
        ret[k].y = y;
        ret[k].z = z;
        ret[k].u = u;
        ret[k].v = v1;
        std::cout << k << std::endl;
        std::cout << u << std::endl;
        std::cout << v1 << std::endl;

        //v = floor((k+1)/12.0f) * (1.0f /8.0f);
        //v1 = ceil((k+1)/12.0f) * (1.0f / 8.0f);

        ret[k+1].x = x1;
        ret[k+1].y = y;
        ret[k+1].z = z1;
        ret[k+1].u = u1;
        ret[k+1].v = v1;
        std::cout << (k+1) << std::endl;
        std::cout << u << std::endl;
        std::cout << v1 << std::endl;

        //v = floor((k+2)/12.0f) * (1.0f /8.0f);
        //v1 = ceil((k+2)/12.0f) * (1.0f / 8.0f);

        ret[k+2].x = x;
        ret[k+2].y = y1;
        ret[k+2].z = z;
        ret[k+2].u = u;
        ret[k+2].v = v;

        std::cout << (k+2) << std::endl;
        std::cout << u << std::endl;
        std::cout << v1 << std::endl;

        //v = floor((k+3)/12.0f) * (1.0f /8.0f);
        //v1 = ceil((k+3)/12.0f) * (1.0f / 8.0f);

        ret[k+3].x = x1;
        ret[k+3].y = y1;
        ret[k+3].z = z1;
        ret[k+3].u = u1;
        ret[k+3].v = v;

        std::cout << (k+3) << std::endl;
        std::cout << u << std::endl;
        std::cout << v1 << std::endl;

        //v = floor((k+4)/12.0f) * (1.0f /8.0f);
        //v1 = ceil((k+4)/12.0f) * (1.0f / 8.0f);

        ret[k+4].x = x;
        ret[k+4].y = y1;
        ret[k+4].z = z;
        ret[k+4].u = u;
        ret[k+4].v = v;

        std::cout << (k+4) << std::endl;
        std::cout << u << std::endl;
        std::cout << v1 << std::endl;

        //v = floor((k+5)/12.0f) * (1.0f /8.0f);
        //v1 = ceil((k+5)/12.0f) * (1.0f / 8.0f);

        ret[k+5].x = x1;
        ret[k+5].y = y;
        ret[k+5].z = z1;
        ret[k+5].u = u1;
        ret[k+5].v = v1;

        std::cout << (k+5) << std::endl;
        std::cout << u << std::endl;
        std::cout << v1 << std::endl;
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
    //std::cout << "index" << std::endl;
    for(int i=0;i<numberSegments*6;i++){
        ret[i] = i;
        //std::cout << i << std::endl;
    }
    mIndexdata = ret;
    //std::cout << "numberSegments " << numberSegments << std::endl;
    mIndexdataSize =  numberSegments*6;
    size = mIndexdataSize;
    return ret;
}
/*
Image* Ring::getImage(unsigned int index){
    return this->images[index];
}
Shader* Ring::getShader(){
    return this->shader;
}
*/