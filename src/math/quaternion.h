/*
Description:
	
*/

#ifndef __QUATERNION__
#define __QUATERNION__
#include "matrix.h"
#include "vector.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace dogEngine
{
	class CQuaternion
	{
		private:
			float components[4];
			
		public:
			CQuaternion();
			CQuaternion(float x0,float x1,float x2,float x3);
			CQuaternion(CVector3 rotationAxis,float angle);
			CQuaternion operator +(CQuaternion sum);
			CQuaternion operator *(CQuaternion quat);
			CVector3 operator *(CVector3 vec);
			float& operator [](int index);
			CQuaternion conjugate();
			CQuaternion inverse();
			CMatrix4 getMatrix();
			void getAxisAngle(CVector3& axis,float& angle);
			float getW();
			float getX();
			float getY();
			float getZ();
			void setW(float w);
			void setX(float x);
			void setY(float y);
			void setZ(float z);
	};
}

#ifdef __cplusplus
}
#endif

#endif