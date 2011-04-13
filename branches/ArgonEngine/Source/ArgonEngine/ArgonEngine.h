#ifndef _ARGONENGINE_HEADER_
#define _ARGONENGINE_HEADER_

#include <Standard/ArgonStandard.h>
#include <Standard/ArgonSingleton.h>

#include <Interface\IRoot.h>
#include <Interface\IPlatform.h>

namespace Argon
{
	class ArgonEngine : public singleton<ArgonEngine>
	{
		friend singleton;
	public:
		ArgonEngine();
		~ArgonEngine();

		///LOAD(BOOL)
		///
		///Load and init the engine
		///
		///No Params:
		bool				Load();

		///UNLOAD(VOID)
		///
		///Release and Cleanup the Engine
		///
		///No Params:
		bool				Unload();

		///GETROOT(ROOT)
		///
		///Get the root if the engine it contains all the engine components and render systems
		///
		///No Params:
		IRoot*				GetRoot() const;

		///GETPLATFORM(IPLATFORM)
		///
		/// Get the Main platform that is being used
		///
		///No Params:
		IPlatform*			GetPlatform() const;

	protected:

	private:
		IPlatform*		m_Platform;		//The platform that will be used throughout the life of the application
		IRoot*			m_Root;			//The Root is used to hide all Render Systems		
	};
} //Namespace

#endif //_ARGONENGINE_HEADER_