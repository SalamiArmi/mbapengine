#include "Camera.h"

namespace OOS
{

	Camera::Camera(D3DXVECTOR3 position, D3DXVECTOR3 TargetPosition)
	{
		mPosition = position;
		mTargetPosition = TargetPosition;
		mUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
		mLook = D3DXVECTOR3(0.0f,0.0f,1.0f);
		mRight = D3DXVECTOR3(1.0f,0.0f,0.0f);
		mRotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
		D3DXMatrixIdentity(&mMatrix);
		mMoveSpeed = 5.0f;
	}

	Camera::~Camera()
	{
	}

	D3DXVECTOR3 Camera::getTargetPosition()
	{
		return mTargetPosition;
	}

	D3DXMATRIX Camera::getView()
	{
		updateRotation();
		return mMatrix;
	}

	D3DXMATRIX Camera::getProjection()
	{
		D3DXMatrixPerspectiveFovLH(&mProjection, 3.14/4, 1.25f, 1.0f, 5000.0f);
		return mProjection;
	}

}