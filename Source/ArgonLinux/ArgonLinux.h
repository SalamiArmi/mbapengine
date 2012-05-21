#ifndef _ARGONLINUX_INCLUDED_
#define _ARGONLINUX_INCLUDED_

#include "IPlatform.h"
#include "ArgonVector.h"

#include <dlfcn.h>
#include <dirent.h>

namespace Argon
{
    class Linux : public IArgonUnknownImp<IPlatform, GUID_IPlatform>
    {
    public:
        Linux();
        ~Linux();

        ///LOADARGONLIBRARY(HANDLE)
		///
		///Load a Dll library
		///
		///Param FileName: The destination to open the file
		void* LoadArgonLibrary(String FileName);

		///LOADENTRYPOINT(VOID*)
		///
		///Load the Entry Point to the Library
		///
		///Param Library: The Library to attempt to get the entry point from
		///Param EntryPoint: The Entry point to attempt to gain access to the Library
		void* LoadEntryPoint(void* Library, String EnrtyPoint);

		///UNLOADLIBRARY(BOOL)
		///
		///UnLoad the Library to freeup memory
		///
		///Param Library: The Handle to the Component Library
		bool UnLoadLibrary(void* Library);

		///UNLOADLIBRARY(BOOL)
		///
		///UnLoad the Library to freeup memory
		///
		///Param LibraryFileName: The Name of the Library to unload
		bool UnLoadLibrary(String LibraryFileName);

		///FINDALLFILES(VECTOR<STRING>)
		///
		///Find all files in a desired directory
		///
		///Param Directory: The location of the directory to find all the files
		void FindAllFiles(String Directory, Vector<String>* Out);

		///CREATEWINDOW(IWINDOW)
		///
		///Create Window specific to the platform
		///
		///No Params:
		IWindow* CreateArgonWindow();

		///GETFILEDATA(VECTOR<CHAR>)
		///
		///Get the contenst of a file and put it into a Vector of char's
		///
		///No Params:
		Vector<char> GetFileData(String FileName);
	private:


    }; //Class
} //Namespace

#endif // _ARGONLINUX_INCLUDED_
