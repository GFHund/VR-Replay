
#ifndef __MATRIX__
#define __MATRIX__

#include <stdarg.h>
//#include <array>
#include <iostream>
#include <array>

#include "vector.h"
#include "../Exceptions/IndexOutOfBoundsException.h"

namespace dogEngine
{
	template<std::size_t N,std::size_t M>//N = Spalten M = Zeilen
	class CMatrix;

	template<std::size_t N,std::size_t M>
	std::ostream& operator<<(std::ostream& input,const CMatrix<N,M>& matrix);

	template<std::size_t N,std::size_t M>
	bool operator==(CMatrix<N,M> matrix1,CMatrix<N,M> matrix2);

	template<std::size_t N,std::size_t M>//N = Spalten M = Zeilen
	class CMatrix
	{
	friend std::ostream& operator<< <>(std::ostream& input,const CMatrix<N,M>& matrix);
	protected:
		//std::array<std::array<float,M>,N> mMat;
		float mMat[N][M];

	public:
		CMatrix();

		//CMatrix(const char* matrix);
		//toDo arr first,second size,last column
		//CMatrix(bool column,float* arr,int size);
		CMatrix(bool column,std::array<float,N*M> arr,int size);

		float getEntity(int column,int row) const;
		void setEntity(int column,int row,float value);

		//std::array<float,M*N> getArray();
		void getArray(float* arr,bool rowFirst);

		CMatrix<M,N> transpose();

		CMatrix<N,M> operator+(CMatrix<N,M> matrix);

		template <std::size_t O>
		CMatrix<O,M> operator*(CMatrix<O,N> matrix);

		CVector<N> operator*(CVector<N> vector);
		CMatrix<N,M> operator*(float skalar);

		bool operator==(CMatrix<N,M> mat);
		bool operator!=(CMatrix<N,M> mat);

		//void operator= (CMatrix<N,M> mat);

		int getRowNum();
		int getColumnNum();

		CMatrix<N,M> clone();

	};

	template<std::size_t N>
	class CSquareMatrix:public CMatrix<N,N>
	{
		public:
		CSquareMatrix();
		//CSquareMatrix(bool column,float* arr);
		CSquareMatrix(bool column,std::array<float,N*N> arr);
		CSquareMatrix(const CMatrix<N,N>& mat);
		CSquareMatrix<N> inverse();
		static CSquareMatrix<N> getIdentity();
		static CSquareMatrix<N> getTranslationMatrix(CVector<N> vec);
	};


	class CMatrix2:public CSquareMatrix<2u>
	{
		public:
		CMatrix2();
		//CMatrix2(bool column,float* arr);
		CMatrix2(bool column,std::array<float,4> arr);/**if column is true than the first column of the row will contain the first four values*/
		CMatrix2(CMatrix<2u,2u> mat);
		CMatrix2 inverse();
		float determinant();
	};
	class CMatrix3:public CSquareMatrix<3>
	{
		public:
		CMatrix3();
		//CMatrix3(bool column,float* arr);
		CMatrix3(bool column,std::array<float,9> arr);/**if column is true than the first column of the row will contain the first four values*/
		CMatrix3(CMatrix<3u,3u> mat);
		CMatrix3 inverse();
		float determinant();

	};

	class CMatrix4:public CSquareMatrix<4>
	{
		public:
		CMatrix4();
		//CMatrix4(bool column,float* arr);/**if column is true than the first column of the row will contain the first four values*/
		CMatrix4(bool column,std::array<float,16> arr);/**if column is true than the first column of the row will contain the first four values*/
		CMatrix4(CMatrix<4u,4u> mat);

		CVector3 multiplyVec3(CVector3 vec);
		//CMatrix4 inverse();
		CMatrix3 getRotationMatrix();
		//static CMatrix4 getTranslationMatrix(CVector3 vec);
		static CMatrix4 getOrtho(float left,float right,float bottom,float top,float znear,float zfar);
	};


	template<std::size_t N,std::size_t M>
	std::ostream& operator <<(std::ostream& input,const CMatrix<N,M>& matrix)
	{
		auto precisionRound = [](float value)->float{return round(value*pow(10,6))/pow(10,6);};
		//return (input << "[" << vector.getX()<< "\t" << vector.getY()<<"\t" << vector.getZ() <<"]");
		for(int i=0;i<M;i++)
		{
			for(int j=0;j<N;j++)
			{
				float value = precisionRound(matrix.getEntity(j,i));
				input << value << "\t";
			}
			input << std::endl;
		}
		return input;
	}
	/*
	std::ostream& operator <<(std::ostream& input,const Vector3& vector)
	{
		return (input << "[" << vector.getX()<< "\t" << vector.getY()<<"\t" << vector.getZ() <<"]");
	}
	*/

	template<std::size_t N,std::size_t M>
	bool operator==(CMatrix<N,M> matrix1,CMatrix<N,M> matrix2)
	{
		auto precisionRound = [](float value)->float{return round(value*pow(10,6))/pow(10,6);};
		bool ret=true;
		for(int i=0;i<N;i++)
		{
			for(int k=0;k<M;k++)
			{
				float value1 = precisionRound(matrix1.getEntity(i,k));
				float value2 = precisionRound(matrix2.getEntity(i,k));
				if(std::abs(value1-value2) > FLT_EPSILON)
				{
					ret = false;
					break;
				}
			}
			if(!ret)
			{
				break;
			}
		}
		return ret;
	}

	template<std::size_t N,std::size_t M>
	CMatrix<N,M>::CMatrix()
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				mMat[i][j] = 0;
				/*
				if(i==j)
				{
					mat[i][j] = 1;
				}
				else
				{
					mat[i][j] = 0;
				}
				*/
			}
		}
	}
/*
	template<std::size_t N,std::size_t M>
	CMatrix<N,M>::CMatrix(const char* matrix)
	{

	}
	*/
	template<std::size_t N,std::size_t M>
	//CMatrix<N,M>::CMatrix(bool column,float* arr,int size)
	CMatrix<N,M>::CMatrix(bool column,std::array<float,N*M> arr,int size)
	{
		int counter=0;
		if(column)
		{
			for(int i=0;i<N;i++)
			{
				for(int j = 0;j<M;j++)
				{
					if(counter<size)
					{
						mMat[i][j] = arr[i*M+j];
						counter++;
					}
					else
					{
						mMat[i][j] = 0;
					}
				}
			}
		}
		else
		{
			for(int j = 0;j<M;j++)
			{
				for(int i=0;i<N;i++)
				{
					if(counter<size)
					{
						mMat[i][j] = arr[i+j*N];
						counter++;
					}
					else
					{
						mMat[i][j] = 0;
					}
				}
			}
		}
	}
	/*
	template<std::size_t N,std::size_t M>
	CMatrix<N,M>::CMatrix(bool column,std::array<float,N*M> arr)
	{
		if(column)
		{
			for(int i=0;i<N;i++)
			{
				for(int j = 0;j<M;j++)
				{
					mMat[i][j] = arr[i*M+j];
				}
			}
		}
		else
		{
			for(int j = 0;j<M;j++)
			{
				for(int i=0;i<N;i++)
				{
					mMat[i][j] = arr[i+j*N];
				}
			}
		}
	}
	*/
	template<std::size_t N,std::size_t M>
	float CMatrix<N,M>::getEntity(int column,int row) const
	{
		if(column >= N || column < 0 || row >= M || row < 0){
			throw IndexOutOfBoundsException();
		}
		return mMat[column][row];
	}
	template<std::size_t N,std::size_t M>
	void CMatrix<N,M>::setEntity(int column,int row,float value)
	{
		if(column >= N || column < 0 || row >= M || row < 0){
			throw IndexOutOfBoundsException();
		}
		mMat[column][row] = value;
	}
	/*
	template<std::size_t N,std::size_t M>
	std::array<float,M*N> CMatrix<N,M>::getArray()
	{
		std::array<float,M*N> ret;
		for(int i=0;i<N;i++)//spalten
		{
			for(int j=0;j<M;j++)//zeilen
			{
				ret[i+j*N] = mMat[i][j];
			}
		}
		return ret;
	}
	*/
	template<std::size_t N,std::size_t M>
	void CMatrix<N,M>::getArray(float* arr,bool rowFirst)
	{
		for(int i=0;i<N;i++)//spalten
		{
			for(int j=0;j<M;j++)//zeilen
			{
				if(rowFirst)
				{
					arr[j+i*N] = mMat[i][j];
				}
				else
				{
					arr[i+j*N] = mMat[i][j];
				}
			}
		}
	}

	template<std::size_t N,std::size_t M>
	CMatrix<M,N> CMatrix<N,M>::transpose()
	{
		CMatrix<M,N> ret;
		for(int i = 0;i<getColumnNum();i++)
		{
			for(int k =0;k<getRowNum();k++)
			{
				ret.setEntity(k,i,getEntity(i,k));
			}
		}
		return ret;
	}

	template<std::size_t N,std::size_t M>
	CMatrix<N,M> CMatrix<N,M>::operator+(CMatrix<N,M> matrix)
	{
		CMatrix<N,M> ret;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				ret.setEntity(i,j,matrix.getEntity(i,j)+getEntity(i,j));
			}
		}
		return ret;
	}


	template<std::size_t N,std::size_t M>
	template <std::size_t O>
	CMatrix<O,M> CMatrix<N,M>::operator*(CMatrix<O,N> matrix)
	{
		CMatrix<O,M> ret;
		if(getColumnNum() != matrix.getRowNum())
		{
			//failure
			return ret;
		}
		for(int i=0;i<M;i++)
		{
			for(int j=0;j<matrix.getColumnNum();j++)
			{
				for(int k = 0;k<N;k++)
				{
					float temp = ret.getEntity(j,i) + getEntity(k,i) * matrix.getEntity(j,k);
					ret.setEntity(j,i,temp);
				}
			}
		}
		return ret;
	}
	//Multiply CMatrix and Vector.
	//toDo: check vector rowSize==CMatrix columnSize
	template<std::size_t N,std::size_t M>
	CVector<N> CMatrix<N,M>::operator*(CVector<N> vector)
	{
		CVector<N> ret;
		for(int i=0;i<N;i++)
		{
			for(int k=0;k<N;k++)
			{
				ret[i] += getEntity(k,i) * vector[k];
			}
		}
		return ret;
	}

	template<std::size_t N,std::size_t M>
	CMatrix<N,M> CMatrix<N,M>::operator*(float skalar)
	{
		CMatrix<N,M> ret;
		for(int i = 0;i<getColumnNum();i++)
		{
			for(int k =0;k<getRowNum();k++)
			{
				ret.setEntity(i,k,getEntity(i,k)*skalar);
			}
		}
		return ret;
	}
	//--------------------------------------
	template<std::size_t N,std::size_t M>
	bool CMatrix<N,M>::operator==(CMatrix<N,M> mat){
		bool ret = true;
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				if(abs(this->getEntity(i,j)-mat.getEntity(i,j)) >= FLT_EPSILON){
					ret = false;
					break;
				}
			}
			if(!ret){
				break;
			}
		}
		return ret;
	}
	//--------------------------------------
	template<std::size_t N,std::size_t M>
	bool CMatrix<N,M>::operator!=(CMatrix<N,M> mat){
		return !(*this == mat);
	}
	//--------------------------------------
	/*
	template<std::size_t N,std::size_t M>
	void CMatrix<N,M>::operator= (CMatrix<N,M> mat)
	{
		for(int i = 0;i<getColumnNum();i++)
		{
			for(int k =0;k<getRowNum();k++)
			{
				setEntity(i,k,mat.getEntity(i,k));
			}
		}
	}
	*/
	template<std::size_t N,std::size_t M>
	int CMatrix<N,M>::getRowNum()
	{
		return M;
	}
	template<std::size_t N,std::size_t M>
	int CMatrix<N,M>::getColumnNum()
	{
		return N;
	}

	template<std::size_t N,std::size_t M>
	CMatrix<N,M> CMatrix<N,M>::clone()
	{
		CMatrix <N,M> ret;
		for(int i = 0;i<N;i++)
		{
			for(int j = 0;j<M;j++)
			{
				ret.setEntity(i,j,getEntity(i,j));
			}
		}
		return ret;
	}

	//-------------------------------------------------------
	template<std::size_t N>
	CSquareMatrix<N>::CSquareMatrix()
	:CMatrix<N,N>()
	{
	}
//-------------------------------------------------------------
	template<std::size_t N>
	CSquareMatrix<N>::CSquareMatrix(bool column,std::array<float,N*N> arr)
	: CMatrix<N,N>(column,arr,N*N)
	{
	}
//------------------------------------------------------
	template<std::size_t N>
	CSquareMatrix<N>::CSquareMatrix(const CMatrix<N,N>& mat)
	{
		for(int i=0;i<N;i++)
		{
			for(int k=0;k<N;k++)
			{
				this->setEntity(i,k,mat.getEntity(i,k));
			}
		}
	}
//------------------------------------------------------
	template<std::size_t N>
	CSquareMatrix<N> CSquareMatrix<N>::inverse()
	{
		/*
		if(getColumnNum() != getRowNum())
		{
			//failure
		}
		*/
		CSquareMatrix<N> ret;
		CSquareMatrix<N> cloneCMatrix = this->clone();
		for(int i = 0;i<this->getColumnNum();i++)
		{
			ret.setEntity(i,i,1);
		}

		for(int i=0;i<this->getColumnNum();i++)
		{
			float temp = cloneCMatrix.getEntity(i,i);
			if(temp!=1 && temp!=0)
			{
				for(int j=i;j<this->getColumnNum();j++)
				{
					cloneCMatrix.setEntity(j,i,cloneCMatrix.getEntity(j,i)/temp);
				}
				for(int j=0;j<this->getColumnNum();j++)
				{
					float temp1 = ret.getEntity(j,i);
					ret.setEntity(j,i,temp1/temp);
				}
			}
			else if(temp == 0)
			{
				//failure
			}

			for(int k=i+1;k<this->getColumnNum();k++)
			{
				temp = cloneCMatrix.getEntity(i,k)*-1;
				for(int j=0;j<this->getColumnNum();j++)
				{
					cloneCMatrix.setEntity(j,k,cloneCMatrix.getEntity(j,k)+temp*cloneCMatrix.getEntity(j,i));
				}
				for(int j=0;j<this->getColumnNum();j++)
				{
					ret.setEntity(j,k,ret.getEntity(j,k)+temp*ret.getEntity(j,i));
				}
			}
		}

		for(int i = this->getColumnNum()-1;i>=0;i--)
		{
			for(int k=i-1;k>=0;k--)
			{
				float temp = cloneCMatrix.getEntity(i,k)*-1;
				for(int j=i;j>=0 && j!=k;j--)
				{
					cloneCMatrix.setEntity(j,k,cloneCMatrix.getEntity(j,k)+cloneCMatrix.getEntity(j,i)*temp);
				}
				for(int j=0;j<this->getColumnNum();j++)
				{
					ret.setEntity(j,k,ret.getEntity(j,k)+ret.getEntity(j,i)*temp);
				}
			}
		}
		return ret;
	}
/*-------------------------------------------------------------*/
	template<std::size_t N>
	CSquareMatrix<N> CSquareMatrix<N>::getIdentity()
	{
		CSquareMatrix<N> ret;
		for(int i=0;i<ret.getColumnNum();i++)
		{
			ret.setEntity(i,i,1);
		}
		return ret;
	}
	template<std::size_t N>
	CSquareMatrix<N> CSquareMatrix<N>::getTranslationMatrix(CVector<N> vec)
	{
		CSquareMatrix<N> ret = CSquareMatrix<N>::getIdentity();
		for(int i=0;i < N;i++)
		{
			ret.setEntity(N-1,i,vec[i]);
		}
		return ret;
	}
}

#endif
