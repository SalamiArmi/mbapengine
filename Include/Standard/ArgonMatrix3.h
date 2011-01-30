#ifndef _ARGONMATRIX3_HEADER_
#define _ARGONMATRIX3_HEADER_

namespace Argon
{
	template<typename T>class Matrix3T
	{
	public:
		Matrix3T(bool bSetToIdentity = true);

		Matrix3T        operator*(const Matrix3T& In) const;
		Vector3         operator*(const Vector3& In) const;
		bool            operator==(const Matrix3T& In) const;
		bool            operator!=(const Matrix3T& In) const;

		T&				operator () (int r,int c)				{ return m_Single[c*3+r];	}
		const T&		operator () (int r,int c) const			{ return m_Single[c*3+r];	}
		T&				operator [](int index)					{ return m_Single[index];	}

		void            SetIdentity(void);

		// mathematical operations
		void            RotateX(T Radians);
		void            RotateY(T Radians);
		void            RotateZ(T Radians);
		void            RotateArbitrary(const Vector3& Axis, T Radius);
		void            Scale(T x, T y, T z);
		void            Scale(const Vector3& Scale);

		union
		{
			T  m_Single[9];
			T  m_RowCol[3][3];
		};
	};

#include "ArgonMatrix3.inl"

#	if defined ArgonX64
	typedef Matrix3T<double> Matrix3;
#	else 
	typedef Matrix3T<float> Matrix3;
#	endif

} //Namespace

#endif //_ARGONMATRIX3_HEADER_