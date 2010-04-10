#ifndef _MATRIX3_HEADER
#define _MATRIX3_HEADER

#include "Vector3.h"
#include "Matrix4.h"

namespace OOS //Zarantas namespace
{
	template<typename T> class Matrix3T
	{
	public:

		enum {rows = 3,columns = 3}; //Change the amount of columns and rows depending on the Matrix
		//Idea make 2 floats with user input making the rows and columns change. (Scrapped reason ou of time)
		T Matrix[rows][columns];

		Matrix3T()
		{
			//destructor
		}

		Matrix3T(T m11, T m12, T m13, T m14, T m15, T m16, T m17, T m18, T m19)
		{
			Matrix[0][0] = m11; //Constructor makin the 3x3 matrix through user input
			Matrix[0][1] = m12;
			Matrix[0][2] = m13;
			Matrix[1][0] = m14;
			Matrix[1][1] = m15;
			Matrix[1][2] = m16;
			Matrix[2][0] = m17;
			Matrix[2][1] = m18;
			Matrix[2][2] = m19;
		}

		Matrix3T operator*(const Matrix3T &NewMatrix) //Multiply of 2 Matrix's
		{
			return Matrix3T(
				Matrix[0][0]*NewMatrix.Matrix[0][0] + Matrix[0][1]*NewMatrix.Matrix[1][0] + Matrix[0][2]*NewMatrix.Matrix[2][0],
				Matrix[0][0]*NewMatrix.Matrix[0][1] + Matrix[0][1]*NewMatrix.Matrix[1][1] + Matrix[0][2]*NewMatrix.Matrix[2][1],
				Matrix[0][0]*NewMatrix.Matrix[0][2] + Matrix[0][1]*NewMatrix.Matrix[1][2] + Matrix[0][2]*NewMatrix.Matrix[2][2],
				Matrix[1][0]*NewMatrix.Matrix[0][0] + Matrix[1][1]*NewMatrix.Matrix[1][0] + Matrix[1][2]*NewMatrix.Matrix[2][0],
				Matrix[1][0]*NewMatrix.Matrix[0][1] + Matrix[1][1]*NewMatrix.Matrix[1][1] + Matrix[1][2]*NewMatrix.Matrix[2][1],
				Matrix[1][0]*NewMatrix.Matrix[0][2] + Matrix[1][1]*NewMatrix.Matrix[1][2] + Matrix[1][2]*NewMatrix.Matrix[2][2],
				Matrix[2][0]*NewMatrix.Matrix[0][0] + Matrix[2][1]*NewMatrix.Matrix[1][0] + Matrix[2][2]*NewMatrix.Matrix[2][0],
				Matrix[2][0]*NewMatrix.Matrix[0][1] + Matrix[2][1]*NewMatrix.Matrix[1][1] + Matrix[2][2]*NewMatrix.Matrix[2][1],
				Matrix[2][0]*NewMatrix.Matrix[0][2] + Matrix[2][1]*NewMatrix.Matrix[1][2] + Matrix[2][2]*NewMatrix.Matrix[2][2]);
		}
		Matrix3T operator+(const Matrix3T &NewMatrix) //Addition of 2 Matrix's
		{
			return Matrix3T(
				Matrix[0][0]+NewMatrix.Matrix[0][0], Matrix[0][1]+NewMatrix.Matrix[0][1], Matrix[0][2]+NewMatrix.Matrix[0][2],
				Matrix[1][0]+NewMatrix.Matrix[1][0], Matrix[1][1]+NewMatrix.Matrix[1][1], Matrix[1][2]+NewMatrix.Matrix[1][2],
				Matrix[2][0]+NewMatrix.Matrix[2][0], Matrix[2][1]+NewMatrix.Matrix[2][1], Matrix[2][2]+NewMatrix.Matrix[2][2]);
		}
		Matrix3T operator-(const Matrix3T &NewMatrix) const //Subtraction of 2 matrix's
		{
			return Matrix3T(
				Matrix[0][0]-NewMatrix.Matrix[0][0], Matrix[0][1]-NewMatrix.Matrix[0][1], Matrix[0][2]-NewMatrix.Matrix[0][2],
				Matrix[1][0]-NewMatrix.Matrix[1][0], Matrix[1][1]-NewMatrix.Matrix[1][1], Matrix[1][2]-NewMatrix.Matrix[1][2],
				Matrix[2][0]-NewMatrix.Matrix[2][0], Matrix[2][1]-NewMatrix.Matrix[2][1], Matrix[2][2]-NewMatrix.Matrix[2][2]);
		}
		Vector3 operator * ( const Vector3 &NewVector ) const //Vector * Matrix
		{
			return Vector3(
				(Matrix[0][0] * NewVector.x + Matrix[0][1] * NewVector.y + Matrix[0][2] * NewVector.z ), 
				( Matrix[1][0] * NewVector.x + Matrix[1][1] * NewVector.y + Matrix[1][2] * NewVector.z ), 
				( Matrix[2][0] * NewVector.x + Matrix[2][1] * NewVector.y + Matrix[2][2] * NewVector.z ));
		}

		Matrix3T Transpose() //Transpose
		{
			return Matrix3T(Matrix[0][0],Matrix[1][0],Matrix[2][0],Matrix[0][1],Matrix[1][1],Matrix[2][1],Matrix[0][2],Matrix[1][2],Matrix[2][2]);
		}

		inline void reflection()
		{
			Matrix[0][0] *= -1;
			Matrix[1][1] *= -1;
		}

		void IdentityMatrix()
		{
			Matrix[0][0] = 1;
			Matrix[1][1] = 1;
			Matrix[2][2] = 1;
		}


		Vector3 xAxis()
		{
			Vector3(Matrix[0][0],Matrix[1][0],Matrix[2][0]);
		}
		void xAxis(const Vector3 &NewVector)
		{
			Matrix[0][0] = NewVector.x;
			Matrix[1][0] = NewVector.y;
			Matrix[2][0] = NewVector.z;
		}

		Vector3 yAxis()
		{
			Vector3(Matrix[0][0],Matrix[1][0],Matrix[2][0]);
		}
		void yAxis(const Vector3 &NewVector)
		{
			Matrix[0][1] = NewVector.x;
			Matrix[1][1] = NewVector.y;
			Matrix[2][1] = NewVector.z;
		}

		Vector3 zAxis()
		{
			Vector3(Matrix[0][0],Matrix[1][0],Matrix[2][0]);
		}
		void zAxis(const Vector3 &NewVector)
		{
			Matrix[0][2] = NewVector.x;
			Matrix[1][2] = NewVector.y;
			Matrix[2][2] = NewVector.z;
		}


		inline Matrix3T NonUniformScaleMatrix(const Vector3 &NewVector)
		{
			return Matrix3T(
				Matrix[0][0] * NewVector.x, Matrix[0][1] * NewVector.x, Matrix[0][2] * NewVector.x,
				Matrix[1][0] * NewVector.y, Matrix[1][1] * NewVector.y, Matrix[1][2] * NewVector.y,
				Matrix[2][0] * NewVector.z, Matrix[2][1] * NewVector.z);
		}

		//inline void ImportingMatrix3INTOMatrix4(Matrix4 &NewMatrix4, Matrix3T &NewMatrix3)  //Making a Natrix4x4 into a Matrix3T
		//{
		//	NewMatrix4x4.Matrix[0][0] = NewMatrix3.Matrix[0][0]; //Each co-ordinate is moved form the 
		//	NewMatrix4x4.Matrix[0][1] = NewMatrix3.Matrix[0][1]; //4x4 and placed into the 3x3
		//	NewMatrix4x4.Matrix[0][2] = NewMatrix3.Matrix[0][2]; //The 4th row and column simply is 
		//	NewMatrix4x4.Matrix[1][0] = NewMatrix3.Matrix[1][0]; //excluded from the 3x3 matrix
		//	NewMatrix4x4.Matrix[1][1] = NewMatrix3.Matrix[1][1];
		//	NewMatrix4x4.Matrix[1][2] = NewMatrix3.Matrix[1][2];
		//	NewMatrix4x4.Matrix[2][0] = NewMatrix3.Matrix[2][0];
		//	NewMatrix4x4.Matrix[2][1] = NewMatrix3.Matrix[2][1];
		//	NewMatrix4x4.Matrix[2][2] = NewMatrix3.Matrix[2][2];
		//}

		void rotateX(T angle)
		{
			Matrix[1][1] = cos(angle);
			Matrix[2][2] = cos(angle);
			Matrix[2][1] = -sin(angle);
			Matrix[1][2] = sin(angle);
		}

		void rotateY(T angle)
		{
			Matrix[0][0] = cos(angle);
			Matrix[2][2] = cos(angle);
			Matrix[2][0] = sin(angle);
			Matrix[0][2] = -sin(angle);
		}
		void rotateZ(T angle)
		{
			Matrix[0][0] = cos(angle);
			Matrix[1][1] = cos(angle);
			Matrix[1][0] = -sin(angle);
			Matrix[0][1] = sin(angle);
		}

		inline void ScaleMatrix3Free(const T xFactor, const T yFactor, const T zFactor)
		{
			IdentityMatrix();
			Matrix[0][0] = xFactor;
			Matrix[1][1] = yFactor;
			Matrix[2][2] = zFactor;
		}

		inline void ScaleMatrix3X(const T factor)
		{
			ScaleMatrix3Free(factor,1,1);
		}
		inline void scaleMatrix3Y(const T factor)
		{
			ScaleMatrix3Free(1,factor,1);
		}
		inline void scaleMatrix3Z(const T factor)
		{
			ScaleMatrix3Free(1,1,factor);
		}
		inline void ShearX(const T ShearAmount, Vector3 NewVector)
		{
			IdentityMatrix();
			Matrix[0][1] = ShearAmount * NewVector.y, NewVector.x;
			Matrix[0][2] = ShearAmount * NewVector.z, NewVector.x;
		}

		inline void ShearY(const T ShearAmount, Vector3 NewVector)
		{
			IdentityMatrix();
			Matrix[1][0] = ShearAmount * NewVector.x, NewVector.y;
			Matrix[1][2] = ShearAmount * NewVector.z, NewVector.y;
		}

		inline void ShearZ(const T ShearAmount, Vector3 NewVector)
		{
			IdentityMatrix();
			Matrix[2][0] = ShearAmount * NewVector.x, NewVector.z;
			Matrix[2][1] = ShearAmount * NewVector.y, NewVector.z;
		}

		inline void SixWayShear(const T ShearAmount, Vector3 NewVector)
		{
			Matrix[0][1] = ShearAmount * NewVector.y, NewVector.x;
			Matrix[0][2] = ShearAmount * NewVector.z, NewVector.x;
			Matrix[1][0] = ShearAmount * NewVector.x, NewVector.y;
			Matrix[1][2] = ShearAmount * NewVector.z, NewVector.y;
			Matrix[2][0] = ShearAmount * NewVector.x, NewVector.z;
			Matrix[2][1] = ShearAmount * NewVector.y, NewVector.z;
		}
	};

	typedef Matrix3T<float> Matrix3;
}


#endif //_MATRIX3_HEADER