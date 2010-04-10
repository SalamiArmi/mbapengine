#ifndef _MATRIX4_HEADER
#define _MATRIX4_HEADER

#include "Vector3.h"
#include "Matrix3.h"

namespace OOS
{
	template<typename T> class Matrix4T
	{
	public:
		//Data
		enum {rows = 4,columns = 4};
		T Matrix[rows][columns];

		Matrix4T()
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++) //Clearing all matrix assing to zero
				{
					Matrix[i][j] = 0;
				}
			}
		}
		inline Matrix4T(T m11, T m12, T m13, T m14, T m15, T m16, T m17, T m18, T m19, T m20, T m21, T m22, T m23, T m24, T m25, T m26)
		{
			Matrix[0][0] = m11; Matrix[0][1] = m12; Matrix[0][2] = m13; Matrix[0][3] = m14;
			Matrix[1][0] = m15; Matrix[1][1] = m16; Matrix[1][2] = m17; Matrix[1][3] = m18;
			Matrix[2][0] = m19; Matrix[2][1] = m20; Matrix[2][2] = m21; Matrix[2][3] = m22;
			Matrix[3][0] = m23; Matrix[3][1] = m24; Matrix[3][2] = m25; Matrix[3][3] = m26;
		}
		~Matrix4T()
		{
			//destructor
		}

		void IdentityMatrix()
		{
			Matrix[0][0] = 1;
			Matrix[1][1] = 1;
			Matrix[2][2] = 1;
			Matrix[3][3] = 1;
		}

		inline void reflection()
		{
			Matrix[0][0] *= -1;
			Matrix[1][1] *= -1;
			Matrix[2][2] *= -1;
			Matrix[3][3] *= -1;
		}

		void MatrixTranspose()
		{

			for (int i = 0; i < 4; i++) {
				for (int j = i + 1; j < 4; j++) {
					int NewMatrix = Matrix[i][j];
					Matrix[i][j] = Matrix[j][i];
					Matrix[j][i] = NewMatrix;
				}
			}
		}

		Matrix4T operator+(const Matrix4T &NewMatrix)
		{
			return Matrix4T(
				Matrix[0][0]+NewMatrix.Matrix[0][0], Matrix[0][1]+NewMatrix.Matrix[0][1], Matrix[0][2]+NewMatrix.Matrix[0][2], Matrix[0][3]+NewMatrix.Matrix[0][3],
				Matrix[1][0]+NewMatrix.Matrix[1][0], Matrix[1][1]+NewMatrix.Matrix[1][1], Matrix[1][2]+NewMatrix.Matrix[1][2], Matrix[1][3]+NewMatrix.Matrix[1][3],
				Matrix[2][0]+NewMatrix.Matrix[2][0], Matrix[2][1]+NewMatrix.Matrix[2][1], Matrix[2][2]+NewMatrix.Matrix[2][2], Matrix[2][3]+NewMatrix.Matrix[2][3],
				Matrix[3][0]+NewMatrix.Matrix[3][0], Matrix[3][1]+NewMatrix.Matrix[3][1], Matrix[3][2]+NewMatrix.Matrix[3][2], Matrix[3][3]+NewMatrix.Matrix[3][3]);
		}

		Matrix4T operator-(const Matrix4T &NewMatrix)
		{
			return Matrix4T(
				Matrix[0][0]-NewMatrix.Matrix[0][0], Matrix[0][1]-NewMatrix.Matrix[0][1], Matrix[0][2]-NewMatrix.Matrix[0][2], Matrix[0][3]-NewMatrix.Matrix[0][3],
				Matrix[1][0]-NewMatrix.Matrix[1][0], Matrix[1][1]-NewMatrix.Matrix[1][1], Matrix[1][2]-NewMatrix.Matrix[1][2], Matrix[1][3]-NewMatrix.Matrix[1][3],
				Matrix[2][0]-NewMatrix.Matrix[2][0], Matrix[2][1]-NewMatrix.Matrix[2][1], Matrix[2][2]-NewMatrix.Matrix[2][2], Matrix[2][3]-NewMatrix.Matrix[2][3],
				Matrix[3][0]-NewMatrix.Matrix[3][0], Matrix[3][1]-NewMatrix.Matrix[3][1], Matrix[3][2]-NewMatrix.Matrix[3][2], Matrix[3][3]-NewMatrix.Matrix[3][3]);
		}
		Matrix4T operator*(const Matrix4T &NewMatrix) const 
		{
			return Matrix4T(
				Matrix[0][0]*NewMatrix.Matrix[0][0] + Matrix[0][1]*NewMatrix.Matrix[1][0] + Matrix[0][2]*NewMatrix.Matrix[2][0] + Matrix[0][3]*NewMatrix.Matrix[3][0],
				Matrix[0][0]*NewMatrix.Matrix[0][1] + Matrix[0][1]*NewMatrix.Matrix[1][1] + Matrix[0][2]*NewMatrix.Matrix[2][1] + Matrix[0][3]*NewMatrix.Matrix[3][1],
				Matrix[0][0]*NewMatrix.Matrix[0][2] + Matrix[0][1]*NewMatrix.Matrix[1][2] + Matrix[0][2]*NewMatrix.Matrix[2][2] + Matrix[0][3]*NewMatrix.Matrix[3][2],
				Matrix[0][0]*NewMatrix.Matrix[0][3] + Matrix[0][1]*NewMatrix.Matrix[1][3] + Matrix[0][2]*NewMatrix.Matrix[2][3] + Matrix[0][3]*NewMatrix.Matrix[3][3],

				Matrix[1][0]*NewMatrix.Matrix[0][0] + Matrix[1][1]*NewMatrix.Matrix[1][0] + Matrix[1][2]*NewMatrix.Matrix[2][0] + Matrix[1][3]*NewMatrix.Matrix[3][0],
				Matrix[1][0]*NewMatrix.Matrix[0][1] + Matrix[1][1]*NewMatrix.Matrix[1][1] + Matrix[1][2]*NewMatrix.Matrix[2][1] + Matrix[1][3]*NewMatrix.Matrix[3][1],
				Matrix[1][0]*NewMatrix.Matrix[0][2] + Matrix[1][1]*NewMatrix.Matrix[1][2] + Matrix[1][2]*NewMatrix.Matrix[2][2] + Matrix[1][3]*NewMatrix.Matrix[3][2],
				Matrix[1][0]*NewMatrix.Matrix[0][3] + Matrix[1][1]*NewMatrix.Matrix[1][3] + Matrix[1][2]*NewMatrix.Matrix[2][3] + Matrix[1][3]*NewMatrix.Matrix[3][3],

				Matrix[2][0]*NewMatrix.Matrix[0][0] + Matrix[2][1]*NewMatrix.Matrix[1][0] + Matrix[2][2]*NewMatrix.Matrix[2][0] + Matrix[2][3]*NewMatrix.Matrix[3][0],
				Matrix[2][0]*NewMatrix.Matrix[0][1] + Matrix[2][1]*NewMatrix.Matrix[1][1] + Matrix[2][2]*NewMatrix.Matrix[2][1] + Matrix[2][3]*NewMatrix.Matrix[3][1],
				Matrix[2][0]*NewMatrix.Matrix[0][2] + Matrix[2][1]*NewMatrix.Matrix[1][2] + Matrix[2][2]*NewMatrix.Matrix[2][2] + Matrix[2][3]*NewMatrix.Matrix[3][2],
				Matrix[2][0]*NewMatrix.Matrix[0][3] + Matrix[2][1]*NewMatrix.Matrix[1][3] + Matrix[2][2]*NewMatrix.Matrix[2][3] + Matrix[2][3]*NewMatrix.Matrix[3][3],

				Matrix[3][0]*NewMatrix.Matrix[0][0] + Matrix[3][1]*NewMatrix.Matrix[1][0] + Matrix[3][2]*NewMatrix.Matrix[2][0] + Matrix[3][3]*NewMatrix.Matrix[3][0],
				Matrix[3][0]*NewMatrix.Matrix[0][1] + Matrix[3][1]*NewMatrix.Matrix[1][1] + Matrix[3][2]*NewMatrix.Matrix[2][1] + Matrix[3][3]*NewMatrix.Matrix[3][1],
				Matrix[3][0]*NewMatrix.Matrix[0][2] + Matrix[3][1]*NewMatrix.Matrix[1][2] + Matrix[3][2]*NewMatrix.Matrix[2][2] + Matrix[3][3]*NewMatrix.Matrix[3][2],
				Matrix[3][0]*NewMatrix.Matrix[0][3] + Matrix[3][1]*NewMatrix.Matrix[1][3] + Matrix[3][2]*NewMatrix.Matrix[2][3] + Matrix[3][3]*NewMatrix.Matrix[3][3]);
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

		void setTrans(const Vector3 &Position)
		{
			Matrix[0][3] = Position.x;
			Matrix[1][3] = Position.y;
			Matrix[2][3] = Position.z;
		}

		inline Vector3 getTrans()
		{
			return Vector3(Matrix[0][3],Matrix[1][3],Matrix[2][3]);
		}

		inline void rotateX(T angle)
		{
			Matrix[1][1] = cos(angle);
			Matrix[2][2] = cos(angle);
			Matrix[2][1] = -sin(angle);
			Matrix[1][2] = sin(angle);
		}

		inline void rotateY(T angle)
		{
			Matrix[0][0] = cos(angle);
			Matrix[2][2] = cos(angle);
			Matrix[2][0] = sin(angle);
			Matrix[0][2] = -sin(angle);
		}
		inline void rotateZ(T angle)
		{
			Matrix[0][0] = cos(angle);
			Matrix[1][1] = cos(angle);
			Matrix[1][0] = -sin(angle);
			Matrix[0][1] = sin(angle);
		}

		inline void ScaleMatrix4Free(const T xFactor, const T yFactor, const T zFactor)
		{
			IdentityMatrix();
			Matrix[0][0] = xFactor;
			Matrix[1][1] = yFactor;
			Matrix[2][2] = zFactor;
		}

		inline void ScaleMatrix4X(const T factor)
		{
			ScaleMatrix4Free(factor,1,1);
		}
		inline void scaleMatrix4Y(const T factor)
		{
			ScaleMatrix4Free(1,factor,1);
		}
		inline void scaleMatrix4Z(const T factor)
		{
			ScaleMatrix4Free(1,1,factor);
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

		inline T DeterminantMatrix()
		{
			T Determinant;
			return Determinant = (Matrix[0][0] * (Matrix[1][1] * Matrix[2][2] - Matrix[1][2] * Matrix[2][1]) +
				Matrix[0][1] * (Matrix[1][2] * Matrix[2][0] - Matrix[1][0] * Matrix[2][2]) +
				Matrix[0][2] * (Matrix[1][0] * Matrix[2][1] - Matrix[1][1] * Matrix[2][0]));
		}
	};
	typedef Matrix4T<float> Matrix4;
}
#endif //_MATRIX4_HEADER