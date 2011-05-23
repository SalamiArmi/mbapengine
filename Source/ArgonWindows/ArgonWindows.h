#ifndef _ARGONWINDOWS_HEADER_
#define _ARGONWINDOWS_HEADER_

#include <Interface/IPlatform.h>
#include <Interface/IArgonUnknownImp.h>
#include <Interface/IWindow.h>
#include <Standard/ArgonPair.h>
#include "Windows.h"

namespace Argon
{
	class WindowsDll;

	class WindowsPlatform : public IArgonUnknownImp<IPlatform, GUID_IPlatform>
	{
	public:
		WindowsPlatform();
		~WindowsPlatform();

		bool Load();

		///////////////////////////////////////////////////////////////////
		// IPlatform Implemention
		void*			LoadLibrary(String FileName);		 						///Load a Dll library
		FARPROC			LoadEntryPoint(void* Library, String EnrtyPoint) ;			///Load the Entry Point to the Library
		bool			UnLoadLibrary(void* Library);								///UnLoad the Library to freeup memory
		bool			UnLoadLibrary(String LibraryFileName);						///UnLoad the Library to freeup memory
		void			FindAllFiles(String Directory, Vector<String>* Out);		///Find all files in a directory
		IWindow*		CreateArgonWindow();

	protected:
		Vector<WindowsDll*>				m_LoadedLibraries;				///All Current loaded libraries, When the Platoform is deleted remove all platforms
	};	

} //Namespace

#endif //_ARGONWINDOWS_HEADER_