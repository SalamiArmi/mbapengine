#include <Core/ArgonCamera.h>

namespace Argon
{
	ArgonStandard Camera::Camera(QString Name)
		: SceneNode(Name)
	{
	}

	ArgonStandard Camera::~Camera()
	{
	}

	ArgonStandard Matrix4 Camera::GetViewMatrix()
	{
		return m_View;
	}

	ArgonStandard Matrix4 Camera::GetProjectionMatrix()
	{
		return m_Projection;
	}

	ArgonStandard Matrix4 Camera::GetViewProjectionMatrix()
	{
		return m_View * m_Projection;
	}

	ArgonStandard void Camera::SetProjection(float FOVY, float Aspect, float Near, float Far)
	{
		m_Fovy = FOVY;
		m_Aspect = Aspect;
		m_Near = Near;
		m_Far = Far;

		m_Projection.Perspective(FOVY, Aspect, Near, Far);
	}

	ArgonStandard void Camera::GetProjection(float &FOVY, float &Aspect, float &Near, float &Far)
	{
		FOVY = m_Fovy;
		Aspect = m_Aspect;
		Near = m_Near;
		Far = m_Far;
	}

} //Namespace