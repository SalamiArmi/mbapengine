#pragma once

#include "math.h"

namespace Argon
{
	template <typename T>
	class Matrix4
	{
	public:
		static const Matrix4<T> Identity;

		Matrix4()
		{
		}

		// Creates a matrix that lets the user input all data in the parameters
		Matrix4(const T _11, const T _12, const T _13, const T _14,
			const T _21, const T _22, const T _23, const T _24,
			const T _31, const T _32, const T _33, const T _34,
			const T _41, const T _42, const T _43, const T _44)
		{
			m[0][0] = _11; m[0][1] = _12; m[0][2] = _13; m[0][3] = _14;
			m[1][0] = _21; m[1][1] = _22; m[1][2] = _23; m[1][3] = _24;
			m[2][0] = _31; m[2][1] = _32; m[2][2] = _33; m[2][3] = _34;
			m[3][0] = _41; m[3][1] = _42; m[3][2] = _43; m[3][3] = _44;
		};

		~Matrix4()
		{
		}

		Matrix4<T> & operator = (const Matrix4 &rhs)
		{
			m[0][0] = rhs.m[0][0]; m[0][1] = rhs.m[0][1]; m[0][2] = rhs.m[0][2]; m[0][3] = rhs.m[0][3];
			m[1][0] = rhs.m[1][0]; m[1][1] = rhs.m[1][1]; m[1][2] = rhs.m[1][2]; m[1][3] = rhs.m[1][3];
			m[2][0] = rhs.m[2][0]; m[2][1] = rhs.m[2][1]; m[2][2] = rhs.m[2][2]; m[2][3] = rhs.m[2][3];
			m[3][0] = rhs.m[3][0]; m[3][1] = rhs.m[3][1]; m[3][2] = rhs.m[3][2]; m[3][3] = rhs.m[3][3];
			return *this;
		}

		// Matrix transpose
		void Transpose()
		{
			*this = Matrix4(m[0][0], m[1][0], m[2][0], m[3][0],
				m[0][1], m[1][1], m[2][1], m[3][1],
				m[0][2], m[1][2], m[2][2], m[3][2],
				m[0][3], m[1][3], m[2][3], m[3][3]);
		}

		T
			m[4][4];
	};

	template<typename T>
	const Matrix4<T> Matrix4<T>::Identity(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);
}
