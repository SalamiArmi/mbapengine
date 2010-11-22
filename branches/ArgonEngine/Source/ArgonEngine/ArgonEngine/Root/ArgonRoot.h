#ifndef _ARGONROOT_HEADER_
#define _ARGONROOT_HEADER_

#include <Standard/ArgonStandard.h>
#include <Standard/ArgonVector.h>
#include <Interface/IRenderSystem.h>
#include <Interface/IPlatform.h>
#include <Interface/IComponent.h>

namespace Argon
{
	class Log;

	class Root
	{
	public:
		Root();
		~Root();

		///LOAD(BOOL)
		///
		///Load and init the Root
		///
		///No Params:
		bool				Load();

		///UNLOAD(VOID)
		///
		///Release and Cleanup the Root
		///
		///No Params:
		bool				Unload();

		///GETRENDERSYSTEMCOUNT(SIZE_T)
		///
		///Get all the Found and loaded rendersystems once the render system is chosen all others are unloaded
		///
		///No Params:
		size_t				GetRenderSystemCount();

		///GETRENDERSYSTEM(IRENDERSYSTEM)
		///
		///Get a RenderSystem
		///
		///Param Index: Which render system to get
		IRenderSystem*		GetRenderSystem(size_t Index) const;

	protected:

		///IMPORTCOMPONENTS(VOID)
		///
		///Import all external Components
		///
		///No Params:
		void				ImportComponents();

		///IMPORTRENDERSYSTEM(VOID)
		///
		///Import all supported components that are currently of type IRenderSystem.
		///
		///
		///No Params:
		void				ImportRenderSystems();

		///FINDSUPPORTEDCOMPONENTS(VOID)
		///
		///Find all components and load them into a list
		///
		///No Params:
		void				FindSupportedComponents();

	private:
		Vector<IComponent*>		m_Components;
		Vector<IRenderSystem*>	m_LoadedRenderSystems;
		Vector<String>			m_FoundComponents;
		IPlatform*				m_Platform;
		Log*					m_Log;
	};

} //Namespace

#endif //_ARGONROOT_HEADER_