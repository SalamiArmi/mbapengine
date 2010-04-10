#ifndef _CAMERA_HEADER_
#define _CAMERA_HEADER_

#include "RotatableObject.h"

namespace OOS
{

	class Camera : public RotatableObject
	{
	public:
		Camera(D3DXVECTOR3 position, D3DXVECTOR3 TargetPosition);
		~Camera();

		D3DXMATRIX getView();

		D3DXMATRIX getProjection();

		D3DXVECTOR3	getTargetPosition();

	protected:
		D3DXVECTOR3	mTargetPosition;
		D3DXMATRIX	mProjection;
		float		mMoveSpeed;
	};

}

#endif //_CAMERA_HEADER_