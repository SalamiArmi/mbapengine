#include "RotatableObject.h"
#include "dinput.h"

namespace OOS
{

	void RotatableObject::updateRotation()
	{
		mMatrix._11 = mRight.x; mMatrix._12 = mUp.x; mMatrix._13 = mLook.x;
		mMatrix._21 = mRight.y; mMatrix._22 = mUp.y; mMatrix._23 = mLook.y;
		mMatrix._31 = mRight.z; mMatrix._32 = mUp.z; mMatrix._33 = mLook.z;

		mMatrix._41 = -D3DXVec3Dot(&mPosition, &mRight);
		mMatrix._42 = -D3DXVec3Dot(&mPosition, &mUp);
		mMatrix._43 = -D3DXVec3Dot(&mPosition, &mLook);
	}

	void RotatableObject::Pitch(float Degrees)
	{
		D3DXMATRIX PitchMatrix;
		D3DXMatrixRotationAxis(&PitchMatrix, &mRight, Degrees); 
		D3DXVec3TransformCoord(&mLook, &mLook, &PitchMatrix);
		D3DXVec3TransformCoord(&mUp, &mUp, &PitchMatrix);
	}

	void RotatableObject::Yaw(float Degrees)
	{
		D3DXMATRIX YawMatrix;
		D3DXMatrixRotationAxis(&YawMatrix, &mUp, Degrees); 
		D3DXVec3TransformCoord(&mLook, &mLook, &YawMatrix);
		D3DXVec3TransformCoord(&mRight, &mRight, &YawMatrix);
	}

	void RotatableObject::Roll(float Degrees)
	{
		D3DXMATRIX RollMatrix;
		D3DXMatrixRotationAxis(&RollMatrix, &mLook, Degrees); 
		D3DXVec3TransformCoord(&mRight, &mRight, &RollMatrix);
		D3DXVec3TransformCoord(&mUp, &mUp, &RollMatrix);
	}

	void RotatableObject::setPosition(D3DXVECTOR3 Position)
	{
		mPosition = Position;
	}

	D3DXVECTOR3 RotatableObject::getPosition()
	{
		return mPosition;
	}

	void RotatableObject::setRotation(D3DXVECTOR3 Rotation)
	{
		mRotation = Rotation;
	}

	D3DXVECTOR3 RotatableObject::getRotation()
	{
		return mRotation;
	}

}
