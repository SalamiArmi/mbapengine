#include "ArgonWindows.h"
#include "ArgonWindowsDll.h"
#include "ArgonWindowsWindow.h"
#include <stdio.h>

namespace Argon
{
	void CreatePlatform(IPlatform** Platform)
	{
		*Platform = new WindowsPlatform();
	}

	WindowsPlatform::WindowsPlatform()
	{
	}


	WindowsPlatform::~WindowsPlatform()
	{
	}

	bool WindowsPlatform::Load()
	{
		return true;
	}
	
	///Load a Dll library
	void* WindowsPlatform::LoadArgonLibrary(String FileName)
	{
		HINSTANCE Component = LoadLibraryExA(FileName.c_str(), NULL, NULL);
		m_LoadedLibraries.Push_Back(new WindowsDll(FileName, Component));
		return (void*)Component;
	}

	///Load the Entry Point to the Library
	void* WindowsPlatform::LoadEntryPoint(void* Library, String EnrtyPoint)
	{
		return (void*)GetProcAddress((HINSTANCE)Library, EnrtyPoint.c_str());
	}

	///UnLoad the Library to freeup memory
	bool WindowsPlatform::UnLoadLibrary(void* Library)
	{
		//Find if the Component was loaded by this platform
		if(m_LoadedLibraries.Size() > 0)
		{
			for(Vector<WindowsDll*>::Iterator it = m_LoadedLibraries.Begin(); it != m_LoadedLibraries.End(); ++it)
			{
				if((*it)->GetComponent() == (HINSTANCE)Library)
				{
					FreeLibrary((HMODULE)Library);	//Free the library
					m_LoadedLibraries.Erase(it);	//Release the Component from the list
					return true;
				}
			}
		}
		return false;
	}

	///UnLoad the Library to freeup memory
	bool WindowsPlatform::UnLoadLibrary(String LibraryFileName)
	{
		//Find if the Component was loaded by this platform
		if(m_LoadedLibraries.Size() > 0)
		{
			for(Vector<WindowsDll*>::Iterator it = m_LoadedLibraries.Begin(); it != m_LoadedLibraries.End(); ++it)
			{
				if((*it)->GetName() == LibraryFileName.c_str())
				{
					FreeLibrary((*it)->GetComponent());	//Free the library
					delete it;
					m_LoadedLibraries.Erase(it);	//Release the Component from the list
					return true;
				}
			}
		}
		return false;
	}

	///Find all files in the defined directory
	void WindowsPlatform::FindAllFiles(String Directory, Vector<String>* Out)
	{
		WIN32_FIND_DATAA FindFileData;
		HANDLE Find = FindFirstFileA(Directory.c_str(), &FindFileData );

		BOOL keepSearching = true;
		Vector<String> ReturnVector;

		if (Find != INVALID_HANDLE_VALUE)
		{
			while (keepSearching)
			{
				String FileName = FindFileData.cFileName;
				String Filename = String("ArgonEngine\\Components\\") + FileName;
				Out->Push_Back(Filename);
				keepSearching = FindNextFile(Find, &FindFileData);
			}
		}

		FindClose(Find);
	}

	IWindow* WindowsPlatform::CreateArgonWindow()
	{
		Window* Win = new Window();
		return Win;
	}

	Vector<char> WindowsPlatform::GetFileData(String FileName)
	{
		FILE* File = NULL;
		fseek(File, 0, SEEK_END); //Seek the end of the file to get the size
		long FileSize = ftell(File);
		rewind(File); //Place the reader back to the start

		Vector<char> FileContenst;
		FileContenst.Resize(FileSize);
		fread(&FileContenst[0], 1, FileSize, File); //Read the total amount of bytes

		fclose(File);
		return FileContenst;
	}

} //Namespace