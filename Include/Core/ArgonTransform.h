#ifndef _ARGONTRANSFORM_HEADER_
#define _ARGONTRANSFORM_HEADER_

#include <Standard/ArgonMatrix4.h>
#include <Standard/ArgonVector3.h>
#include "ArgonTransform4.h"

namespace Argon
{
	class Transform
	{
	public:
		Transform()
		{
		}

		void SetIdentityTransform()
		{
			m_WorldTransform.SetIdentity();
			m_InverseWorldTransform.SetIdentity();
		}

		const Matrix4& GetWorldTransform() const
		{
			return m_WorldTransform;
		}

		const Vector3& GetWorldPosition() const
		{
			return m_WorldTransform.GetTranslation();
		}

		const Matrix4& GetInverseWorldTransform() const
		{
			return m_InverseWorldTransform;
		}

		void SetWorldTransform(const Transform4& Transform)
		{
			m_WorldTransform = Transform;
			m_InverseWorldTransform = Inverse(m_WorldTransform);
		}

		void SetWorldTransform(const Matrix4& m, const Vector3& p)
		{
			m_WorldTransform.Set(m, p);
			m_InverseWorldTransform = Inverse(m_WorldTransform);
		}

		void SetWorldPosition(const Vector3& Position)
		{
			m_WorldTransform.SetTranslation(Position);
			m_InverseWorldTransform = Inverse(m_WorldTransform);
		}

		Transform4 Inverse(const Matrix4& m)
		{
			float n00 = m(0,0);
			float n01 = m(0,1);
			float n02 = m(0,2);
			float n03 = m(0,3);

			float n10 = m(1,0);
			float n11 = m(1,1);
			float n12 = m(1,2);
			float n13 = m(1,3);

			float n20 = m(2,0);
			float n21 = m(2,1);
			float n22 = m(2,2);
			float n23 = m(2,3);

			float p00 = n11 * n22 - n12 * n21;
			float p10 = n12 * n20 - n10 * n22;
			float p20 = n10 * n21 - n11 * n20;

			float t = 1.0F / (n00 * p00 + n01 * p10 + n02 * p20);

			return (Transform4(p00 * t,
				(n02 * n21 - n01 * n22) * t,
				(n01 * n12 - n02 * n11) * t,
				(n01 * (n13 * n22 - n12 * n23) + n02 * (n11 * n23 - n13 * n21) + n03 * (n12 * n21 - n11 * n22)) * t,
				p10 * t,
				(n00 * n22 - n02 * n20) * t,
				(n02 * n10 - n00 * n12) * t,
				(n00 * (n12 * n23 - n13 * n22) + n02 * (n13 * n20 - n10 * n23) + n03 * (n10 * n22 - n12 * n20)) * t,
				p20 * t,
				(n01 * n20 - n00 * n21) * t,
				(n00 * n11 - n01 * n10) * t,
				(n00 * (n13 * n21 - n11 * n23) + n01 * (n10 * n23 - n13 * n20) + n03 * (n11 * n20 - n10 * n21)) * t));
		}

		Transform4 Adjugate(const Matrix4& m)
		{
			float n00 = m(0,0);
			float n01 = m(0,1);
			float n02 = m(0,2);
			float n03 = m(0,3);

			float n10 = m(1,0);
			float n11 = m(1,1);
			float n12 = m(1,2);
			float n13 = m(1,3);

			float n20 = m(2,0);
			float n21 = m(2,1);
			float n22 = m(2,2);
			float n23 = m(2,3);

			return (Transform4(n11 * n22 - n12 * n21,
				n02 * n21 - n01 * n22,
				n01 * n12 - n02 * n11,
				n01 * (n13 * n22 - n12 * n23) + n02 * (n11 * n23 - n13 * n21) + n03 * (n12 * n21 - n11 * n22),
				n12 * n20 - n10 * n22,
				n00 * n22 - n02 * n20,
				n02 * n10 - n00 * n12,
				n00 * (n12 * n23 - n13 * n22) + n02 * (n13 * n20 - n10 * n23) + n03 * (n10 * n22 - n12 * n20),
				n10 * n21 - n11 * n20,
				n01 * n20 - n00 * n21,
				n00 * n11 - n01 * n10,
				n00 * (n13 * n21 - n11 * n23) + n01 * (n10 * n23 - n13 * n20) + n03 * (n11 * n20 - n10 * n21)));
		}

	protected:
		Transform4	m_WorldTransform;
		Transform4	m_InverseWorldTransform;
	}; //class
} //Namespace

#endif //_ARGONTRANSFORM_HEADER_