#ifndef _ICAMERA_HEADER_
#define _ICAMERA_HEADER_

#include <Standard/ArgonMatrix4.h>
#include <Standard/ArgonQString.h>

#include <Core/ArgonEntity.h>

#pragma warning(disable : 4251 )

namespace Argon
{
	class Camera : public Entity
	{
	public:
		Camera(String Name);
		~Camera();

		///GETVIEWMATRIX(MATRIX4)
		///
		/// Get the View Matrix, normally used for rendering and shaders
		///
		///No Params:
		Matrix4 GetViewMatrix();

		///GETPROJECTIONMATRIX(MATRIX4)
		///
		/// Get the Projection Matrix, normally used for rendering and shaders
		///
		///No Params:
		Matrix4 GetProjectionMatrix();

		///(MATRIX4)
		///
		/// Get the View Projection Matrix, normally used for rendering and shaders
		///
		///No Params:
		Matrix4 GetViewProjectionMatrix();

		///SETPROJECTIION(VOID)
		///
		/// Create a new projection matrix from the supplied parameters
		///
		///Params FOVY: Field of view in the y direction, in radians.
		///Params Aspect: Aspect ratio, defined as view space width divided by height
		///Params Near: Z-value of the near view-plane
		///Params Far: Z-value of the far view-plane
		void SetProjection(float FOVY, float Aspect, float Near, float Far);

		///GETPROJECTION(VOID)
		///
		/// Get the Defining parts that create a projection matrix
		///
		///Params OUT FOVY: Field of view in the y direction, in radians.
		///Params OUT Aspect: Aspect ratio, defined as view space width divided by height
		///Params OUT Near: Z-value of the near view-plane
		///Params OUT Far: Z-value of the far view-plane
		void GetProjection(float &FOVY, float &Aspect, float &Near, float &Far);

	protected:
		Matrix4			m_View;
		Matrix4			m_Projection;

		float			m_Fovy;
		float			m_Aspect;
		float			m_Near;
		float			m_Far;
	};

} //Namespace

#endif //_ICAMERA_HEADER_