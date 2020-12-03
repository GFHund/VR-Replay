#include "matrix.h"

namespace dogEngine
{
	CMatrix2::CMatrix2()
	:CSquareMatrix()
	{
	}

	//CMatrix2::CMatrix2(bool column,float* arr)
	CMatrix2::CMatrix2(bool column,std::array<float,4> arr)
	: CSquareMatrix(column,arr)
	{
	}

	CMatrix2::CMatrix2(CMatrix<2u,2u> mat)
	{
		for(int i = 0;i<getColumnNum();i++)
		{
			for(int k =0;k<getRowNum();k++)
			{
				setEntity(i,k,mat.getEntity(i,k));
			}
		}
	}

	CMatrix2 CMatrix2::inverse()
	{
		CMatrix2 ret;
		float det = 1.0f/determinant();
		ret.setEntity(0,0,getEntity(1,1));
		ret.setEntity(1,0,-getEntity(1,0));
		ret.setEntity(0,1,-getEntity(0,1));
		ret.setEntity(1,1,getEntity(0,0));
		ret = ret * det;
		return ret;
	}

	float CMatrix2::determinant()
	{
		return getEntity(0,0)*getEntity(1,1) - getEntity(1,0) * getEntity(0,1);
	}

	//-------------------------------------

	CMatrix3::CMatrix3()
	: CSquareMatrix()
	{
	}

	//CMatrix3::CMatrix3(bool column,float* arr)
	CMatrix3::CMatrix3(bool column,std::array<float,9> arr)
	: CSquareMatrix(column,arr)
	{
	}

	CMatrix3::CMatrix3(CMatrix<3u,3u> mat)
	{
		for(int i = 0;i<getColumnNum();i++)
		{
			for(int k =0;k<getRowNum();k++)
			{
				setEntity(i,k,mat.getEntity(i,k));
			}
		}
	}

	CMatrix3 CMatrix3::inverse()
	{
		//float A,B,C,D,E,F,G,H,I;
		float det = 1.0f/determinant();
		CMatrix3 ret;
		ret.setEntity(0,0,getEntity(1,1)*getEntity(2,2)-getEntity(2,1)*getEntity(1,2));
		ret.setEntity(1,0,-(getEntity(0,1)*getEntity(2,2)-getEntity(2,1)*getEntity(0,2)));
		ret.setEntity(2,0,(getEntity(0,1)*getEntity(1,2)-getEntity(1,1)*getEntity(0,2)));

		ret.setEntity(0,1,-(getEntity(1,0)*getEntity(2,2) - getEntity(2,0)*getEntity(1,2)));
		ret.setEntity(1,1,getEntity(0,0)*getEntity(2,2) - getEntity(2,0)*getEntity(0,2));
		ret.setEntity(2,1,-(getEntity(0,0)*getEntity(1,2) - getEntity(1,0)*getEntity(0,2)));

		ret.setEntity(0,2,getEntity(1,0)*getEntity(2,1) - getEntity(2,0)*getEntity(1,1));
		ret.setEntity(1,2,-(getEntity(0,0)*getEntity(2,1) - getEntity(2,0)*getEntity(0,1)));
		ret.setEntity(2,2,getEntity(0,0)*getEntity(1,1) - getEntity(1,0)*getEntity(0,1));

		ret = ret.transpose();
		ret = ret*det;
		return ret;
	}
	float CMatrix3::determinant()
	{
		return getEntity(0,0)*getEntity(1,1)*getEntity(2,2)+
				getEntity(1,0)*getEntity(2,1)*getEntity(0,2)+
				getEntity(2,1)*getEntity(0,1)*getEntity(1,2)-
				getEntity(2,0)*getEntity(1,1)*getEntity(0,2)-
				getEntity(1,0)*getEntity(0,1)*getEntity(2,2)-
				getEntity(0,0)*getEntity(2,1)*getEntity(1,2);
	}
	//-------------------------------------
	CMatrix4::CMatrix4()
	: CSquareMatrix()
	{
	}

	//CMatrix4::CMatrix4(bool column,float* arr)
	CMatrix4::CMatrix4(bool column,std::array<float,16> arr)
	: CSquareMatrix(column,arr)
	{
	}

	CMatrix4::CMatrix4(CMatrix<4u,4u> mat)
	{
		for(int i = 0;i<getColumnNum();i++)
		{
			for(int k =0;k<getRowNum();k++)
			{
				setEntity(i,k,mat.getEntity(i,k));
			}
		}
	}

	CVector3 CMatrix4::multiplyVec3(CVector3 vec)
	{
		CVector4 vec4 = CVector4(vec);
		CMatrix4 mat = (*this);
		CVector4 ret4 =  mat * vec4;
		return CVector3(ret4.getX(),ret4.getY(),ret4.getZ());
	}

	CMatrix3 CMatrix4::getRotationMatrix()
	{
		CMatrix3 ret;
		ret.setEntity(0,0,getEntity(0,0));
		ret.setEntity(0,1,getEntity(0,1));
		ret.setEntity(0,2,getEntity(0,2));

		ret.setEntity(1,0,getEntity(1,0));
		ret.setEntity(1,1,getEntity(1,1));
		ret.setEntity(1,2,getEntity(1,2));

		ret.setEntity(2,0,getEntity(2,0));
		ret.setEntity(2,1,getEntity(2,1));
		ret.setEntity(2,2,getEntity(2,2));

		return ret;
	}
	/*
	CMatrix4 CMatrix4::getTranslationMatrix(CVector3 vec)
	{

	}
	*/
	CMatrix4 CMatrix4::getOrtho(float left,float right,float bottom,float top,float zNear,float zFar){
		float xx = 2/(right - left);
			float yy = 2/(top - bottom);
			float zz = -2/(zFar - zNear);
			float wx = -(right + left)/(right - left);
			float wy = -(top + bottom)/(top - bottom);
			float wz = -(zFar - zNear)/(zFar - zNear);
			std::array<float,16> orthoMatrixArr = {xx,0,0,wx,
											0,yy,0,wy,
											0,0,zz,wz,
											0,0,0,1};
		return CMatrix4(false,orthoMatrixArr);
	}
  
  CMatrix4 CMatrix4::getPerspective(float fovy,float aspect,float zNear,float zFar){
    const float PI = 3.14159;
			float pi360 = PI / 360.0f;
			float fovRad = fovy * pi360;
			auto cot = [](float alpha){return 1 / tan(alpha); };
			float f = cot(fovRad / 2);
			float xx = f / aspect;
			
			float yy = f;
			float zz = -((zFar + zNear)/(zFar - zNear));
			
			float wz = -((2 * zFar * zNear) / (zFar - zNear));
			/*
      float perspectiveMatrixArr[16] = {xx,0,0,0,
											0,yy,0,0,
											0,0,zz,wz,
											0,0,-1,0};
			*/
      std::array<float,16> perspectiveMatrixArr = {xx,0,0,0,
											0,yy,0,0,
											0,0,zz,wz,
											0,0,-1,0};
			return CMatrix4(false,perspectiveMatrixArr);
  }
}
