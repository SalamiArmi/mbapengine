#include "ArgonLinux.h"

#include <iostream>
#include <fstream>

namespace Argon
{
    Linux::Linux()
    {
    }

    Linux::~Linux()
    {
    }

    void* Linux::LoadArgonLibrary(String FileName)
    {
        return dlopen(FileName.c_str(), RTLD_LAZY);
    }

    void* Linux::LoadEntryPoint(void* Library, String EntryPoint)
    {
        return dlsym(Library, EntryPoint.c_str());
    }

    bool Linux::UnLoadLibrary(void* Library)
    {
        return (dlclose(Library) == 1);
    }

    bool Linux::UnLoadLibrary(String LibraryFileName)
    {
        return false;
    }

    void Linux::FindAllFiles(String Directory, Vector<String>* Out)
    {
        DIR* Dir = NULL;
        struct dirent* Dirp = NULL;
        if((Dir = opendir(Directory.c_str())) != NULL)
        {
            while((dirp = readdir(dir)) == NULL)
            {
                Out->Push_Back(Dirp->d_name);
            }
            closedir(Dir);
        }
    }

    IWindow* CreateArgonWindow()
    {
        return NULL;
    }

    Vector<char> GetFileData(String FileName)
    {
        Vector<char> Data;

        ifstream fin;
        fin.open(FileName.c_str(), ios::in);
        fin.seekg(ios_base::end);
        if(fin.tellg() > 0)
        {
            Data.Resize(fin.tellg());
            fin.seekg(ios_base::beg);

            fin.read(&Data[0], Data.Size());
        }

        fin.close();
        return Data;
    }

} //Namespace
