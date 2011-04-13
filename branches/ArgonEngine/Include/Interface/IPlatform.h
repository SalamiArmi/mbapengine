#ifndef _IPLATFORM_HEADER_
#define _IPLATFORM_HEADER_

#include "Windows.h"

#include "IArgonUnknown.h"
#include <Standard/ArgonString.h>
#include <Standard/ArgonVector.h>

namespace Argon
{
	DeclareBasedInterface(IPlatform, IArgonUnknown)

		///LOADLIBRARY(HANDLE)
		///
		///Load a Dll library
		///
		///Param FileName: The destination to open the file
		void* LoadLibrary(String FileName) = 0;		

		///LOADENTRYPOINT(FARPROC)
		///
		///Load the Entry Point to the Library
		///
		///Param Library: The Library to attempt to get the entry point from
		///Param EntryPoint: The Entry point to attempt to gain access to the Library
		FARPROC LoadEntryPoint(void* Library, String EnrtyPoint) = 0;

		///UNLOADLIBRARY(BOOL)
		///
		///UnLoad the Library to freeup memory
		///
		///Param Library: The Handle to the Component Library
		bool UnLoadLibrary(void* Library) = 0;

		///UNLOADLIBRARY(BOOL)
		///
		///UnLoad the Library to freeup memory
		///
		///Param LibraryFileName: The Name of the Library to unload
		bool UnLoadLibrary(String LibraryFileName) = 0;

		///FINDALLFILES(VECTOR<STRING>)
		///
		///Find all files in a desired directory
		///
		///Param Directory: The location of the directory to find all the files
		void FindAllFiles(String Directory, Vector<String>* Out) = 0;

	EndInterface(IPlatform)

	ArgonExport void CreatePlatform(IPlatform** Platform);

} //Namespace

#endif //_IPLATFORM_HEADER_