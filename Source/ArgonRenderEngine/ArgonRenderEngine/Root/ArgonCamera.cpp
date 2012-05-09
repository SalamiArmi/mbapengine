#include <Core/ArgonCamera.h>

namespace Argon
{
	Camera::Camera(QString Name)
		: SceneNode(Name)
	{
	}

	Camera::~Camera()
	{
	}

	Matrix4 Camera::GetViewMatrix()
	{
		return m_View;
	}

	Matrix4 Camera::GetProjectionMatrix()
	{
		return m_Projection;
	}

	Matrix4 Camera::GetViewProjectionMatrix()
	{
		return m_View * m_Projection;
	}

	void Camera::SetProjection(float FOVY, float Aspect, float Near, float Far)
	{
		m_Fovy = FOVY;
		m_Aspect = Aspect;
		m_Near = Near;
		m_Far = Far;

		m_Projection.Perspective(FOVY, Aspect, Near, Far);
	}

	void Camera::GetProjection(float &FOVY, float &Aspect, float &Near, float &Far)
	{
		FOVY = m_Fovy;
		Aspect = m_Aspect;
		Near = m_Near;
		Far = m_Far;
	}

} //Namespace