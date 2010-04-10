#include "System.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	OOS::System* Sys = new OOS::System(hInstance);

	if (Sys->InitInstance())
	{
		while (Sys->IsRunning())
		{
			Sys->RenderOneFrame();
		}
	}

	Sys->Cleanup();
	delete Sys;
	Sys = NULL;

	return 0;
}
