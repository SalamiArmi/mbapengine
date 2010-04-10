#ifndef _MODELINPUT_HEADER_
#define _MODELINPUT_HEADER_

#include "d3dx9math.h"

namespace OOS
{

	class RotatableObject
	{
	public:

		///UPDATEROTATION(VOID)
		///
		///Update the rotation of the object
		///
		///No Params:
		void updateRotation();

		///PITCH(VOID)
		///
		///Rotate the camera around the X axis
		///
		///Param Degrees: The desired degrees to be rotated
		void Pitch(float Degrees);

		///YAW(VOID)
		///
		///Rotate the camera around the Y axis
		///
		///Param Degrees: The desired degrees to be rotated
		void Yaw(float Degrees);

		///ROLL(VOID)
		///
		///Rotate the camera around the Z axis
		///
		///Param Degrees: The desired degrees to be rotated
		void Roll(float Degrees);

		///SETPOSITION(VOID)
		///
		///
		///
		///Param position: The new desired position of the camera
		void setPosition(D3DXVECTOR3 position);

		///GET FUNCTION
		///GETPOSITION(D3DXVECTOR3)
		///
		///Retireve the position of the camera
		///
		///No Params:
		D3DXVECTOR3	getPosition();

		///SETROTATION(VOID)
		///
		///Set the current rotation of the object
		///
		///
		///Param Rotation: The new rotation
		void setRotation(D3DXVECTOR3 Rotation);

		///GET FUNCTION
		///GETROTATION(D3DXVECTOR3)
		///
		///Retrieve the current rotation of the object
		///
		///No Params:
		D3DXVECTOR3 getRotation();

		///GET FUNCTION
		///GETUP(D3DXVECTOR3)
		///
		///Retrieve Y axis rotation
		///
		///No Params:
		D3DXVECTOR3 getUp();

		///GET FUNCTION
		///GETRIGHT(D3DXVECTOR3)
		///
		///Retrieve the X axis rotation
		///
		///No Params:
		D3DXVECTOR3 getRight();

		///GET FUNCTION
		///GETLOOK(D3DXVECTOR3)
		///
		///Retrieve the Z axis rotation
		///
		///No Params:
		D3DXVECTOR3 getLook();

	protected:
		D3DXVECTOR3 mPosition;
		D3DXVECTOR3 mRotation;
		D3DXVECTOR3 mLook;
		D3DXVECTOR3 mUp;
		D3DXVECTOR3 mRight;

		D3DXMATRIX mMatrix;
	};

}

#endif //_MODELINPUT_HEADER_