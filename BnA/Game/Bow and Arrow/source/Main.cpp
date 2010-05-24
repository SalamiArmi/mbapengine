#include "Precompiled.h"
#include "Framework.h"

#include "PCInputManager.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF|_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF));

	try
	{
		while(Framework::instance()->isRunning())
		{
			Framework::instance()->Update();
		}	
		Framework::destroyInstance();	
	}
	catch(Ogre::Exception& e)
	{
		MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}

	return 0;
}
