#include "Abstract3dObject.h"

Image* Abstract3dObject::getImage(unsigned int index){
    if(index > 1){
        throw IndexOutOfBoundsException();
    }
    /*I don't know at the moment if the images[index] is no defined. The result may be undefined*/
    return this->images[index];
}
void Abstract3dObject::setImage(unsigned int index,Image* image){
    if(index > 1){
        throw IndexOutOfBoundsException();
    }
    this->images[index] = image;
}

Shader* Abstract3dObject::getShader(){
    return this->shader;
}
void Abstract3dObject::setShader(Shader* shader){
    this->shader = shader;
    
}

void Abstract3dObject::addShaderParam(std::string shaderParamNo,AbstractShaderParam* param){
    this->mShaderParam.insert(std::pair<std::string,AbstractShaderParam*>(shaderParamNo,param));
}
AbstractShaderParam* Abstract3dObject::getShaderParam(std::string shaderParamNo){
    return this->mShaderParam.at(shaderParamNo);
}
std::map<std::string,AbstractShaderParam*> Abstract3dObject::getShaderParamMap(){
    return this->mShaderParam;
}


void Abstract3dObject::setVertexBuffer(int vertexBuffer){
    this->vertexBuffer = vertexBuffer;
}
int Abstract3dObject::getVertexBuffer(){
    return this->vertexBuffer;
}

void Abstract3dObject::setIndiceBuffer(int indexBuffer){
    this->indiceBuffer = indexBuffer;
}
int Abstract3dObject::getIndiceBuffer(){
    return this->indiceBuffer;
}
dogEngine::CVector3d Abstract3dObject::getPos(){
    return this->mPos;
}
void Abstract3dObject::setPos(dogEngine::CVector3d pos){
    this->mPos = pos;
}
dogEngine::CVector3d Abstract3dObject::getScale(){
    return this->mScale;
}
void Abstract3dObject::setScale(dogEngine::CVector3d scale){
    this->mScale = scale;
}
dogEngine::CQuaternion Abstract3dObject::getRotation(){
    return this->mRotation;
}
void Abstract3dObject::setRotation(dogEngine::CQuaternion rotation){
    this->mRotation = rotation;
}

dogEngine::CMatrix4 Abstract3dObject::getTransformationMatrix(){
    dogEngine::CMatrix4 translationMat = dogEngine::CMatrix4::getTranslationMatrix(dogEngine::CVector4d(this->mPos));
    dogEngine::CQuaternion rotation = this->getRotation();
    dogEngine::CMatrix4 rotationMatrix = rotation.getMatrix();
    dogEngine::CMatrix4 worldTransformationsMatrix = dogEngine::CMatrix4::getIdentity();
    /*
    if(this->mParent != NULL)
    {
        worldTransformationsMatrix = this->mParent->getWorldTransformationsMatrix();
    }
    */
    return worldTransformationsMatrix * rotationMatrix * translationMat;
}