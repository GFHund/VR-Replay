#ifndef __RENDERER__
#define __RENDERER__

#include "../objects/Abstract3dObject.h"
#include "../math/vector.h"
#include "../math/quaternion.h"

class Renderer{
    private: 
    int mWidth;
    int mHeight;

    dogEngine::CVector3 mCameraPos;
    dogEngine::CQuaternion mCameraRot;
    public:
        void init(int width,int height);
        void init3DObject(Abstract3dObject* obj);
        void render3DObject(Abstract3dObject* obj);

        void setCameraPos(dogEngine::CVector3 pos);
        void setCameraRot(dogEngine::CQuaternion rot);
        void setCameraToPos(dogEngine::CVector3 pos, float angleX,float angleY, float distance);
};

#endif