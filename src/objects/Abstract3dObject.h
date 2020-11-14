#ifndef __ABSTRACT_3D_OBJECT__
#define __ABSTRACT_3D_OBJECT__
#include "../shader/AbstractShaderParam.h"
#include "../ModelData.h"
#include "../Image.h"
#include "../shader/Shader.h"
#include "../VertexData.h"
#include "../IndexData.h"
#include "../Exceptions/IndexOutOfBoundsException.h"

#include "../math/vector.h"
#include "../math/quaternion.h"
#include "../math/matrix.h"
#include <map>

class Abstract3dObject{
    
    protected:
    int vertexBuffer;
    int indiceBuffer;

    Image* images[2];
    Shader* shader = nullptr;

    dogEngine::CVector3 mPos;
    dogEngine::CVector3 mScale;
    dogEngine::CQuaternion mRotation;
    std::map<std::string,AbstractShaderParam*> mShaderParam;

    public:
    Abstract3dObject(){
        images[0] = nullptr;
        images[1] = nullptr;
    }

    virtual ModelData* getModelData(unsigned int& size) = 0;
    virtual unsigned short* getIndexData(unsigned int& size) = 0;

    Image* getImage(unsigned int index);
    void setImage(unsigned int index,Image* image);

    Shader* getShader();
    void setShader(Shader* shader);

    void addShaderParam(std::string shaderParamName,AbstractShaderParam* param);
    AbstractShaderParam* getShaderParam(std::string shaderParamName);
    std::map<std::string,AbstractShaderParam*> getShaderParamMap();


    

    void setVertexBuffer(int vertexBuffer);
    int getVertexBuffer();

    void setIndiceBuffer(int indexBuffer);
    int getIndiceBuffer();
    dogEngine::CVector3d getPos();
    void setPos(dogEngine::CVector3d pos);
    dogEngine::CVector3d getScale();
    void setScale(dogEngine::CVector3d scale);
    dogEngine::CQuaternion getRotation();
    void setRotation(dogEngine::CQuaternion rotation);

    dogEngine::CMatrix4 getTransformationMatrix();
};

#endif