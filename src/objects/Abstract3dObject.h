#ifndef __ABSTRACT_3D_OBJECT__
#define __ABSTRACT_3D_OBJECT__
#include "../ModelData.h"
#include "../Image.h"
#include "../Shader.h"
#include "../VertexData.h"
#include "../IndexData.h"
#include "../Exceptions/IndexOutOfBoundsException.h"

#include "../math/vector.h"
#include "../math/quaternion.h"
#include "../math/matrix.h"

class Abstract3dObject{
    
    protected:
    int vertexBuffer;
    int indiceBuffer;

    Image* images[2];
    Shader* shader = nullptr;

    dogEngine::CVector3 mPos;
    dogEngine::CVector3 mScale;
    dogEngine::CQuaternion mRotation;

    public:
    virtual ModelData* getModelData(unsigned int& size) = 0;
    virtual unsigned short* getIndexData(unsigned int& size) = 0;

    Image* getImage(unsigned int index){
        if(index > 1){
            throw IndexOutOfBoundsException();
        }
        /*I don't know at the moment if the images[index] is no defined. The result may be undefined*/
        return this->images[index];
    }
    void setImage(unsigned int index,Image* image){
        if(index > 1){
            throw IndexOutOfBoundsException();
        }
        this->images[index] = image;
    }

    Shader* getShader(){
        return this->shader;
    }
    void setShader(Shader* shader){
        this->shader = shader;
    }
    

    void setVertexBuffer(int vertexBuffer){
        this->vertexBuffer = vertexBuffer;
    }
    int getVertexBuffer(){
        return this->vertexBuffer;
    }

    void setIndiceBuffer(int indexBuffer){
        this->indiceBuffer = indexBuffer;
    }
    int getIndiceBuffer(){
        return this->indiceBuffer;
    }
    dogEngine::CVector3d getPos(){
        return this->mPos;
    }
    void setPos(dogEngine::CVector3d pos){
        this->mPos = pos;
    }
    dogEngine::CVector3d getScale(){
        return this->mScale;
    }
    void setScale(dogEngine::CVector3d scale){
        this->mScale = scale;
    }
    dogEngine::CQuaternion getRotation(){
        return this->mRotation;
    }
    void setRotation(dogEngine::CQuaternion rotation){
        this->mRotation = rotation;
    }

    dogEngine::CMatrix4 getTransformationMatrix(){
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
};

#endif