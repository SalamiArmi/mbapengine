#ifndef	_SCENEMANAGER_HEADER_
#define _SCENEMANAGER_HEADER_

#include <Interface/IFrameListner.h>
#include <Interface/IComponent.h>
#include <Interface/IArgonUnknownImp.h>

namespace Argon
{
	class ArgonAPI SceneManager : public IArgonUnknownImp2<IComponent, GUID_IComponent, IFrameListner, GUID_IFrameListner>
	{
	public:
		SceneManager(QString Name, Root* Creator);

		///GETCREATOR(ROOT)
		///
		///Get the Root whom Created this object
		///
		///No Params:
		Root*	GetCreator();

	protected:
		Root*	m_Creator; //The Root which created this Manager

	};
} //Namespace

#endif //_SCENEMANAGER_HEADER_