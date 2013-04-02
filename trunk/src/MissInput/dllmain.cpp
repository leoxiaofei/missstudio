// dllmain.cpp : Defines the entry point for the DLL application.
//#include "stdafx.h"

#include "Impl\MissPluginMain.h"

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    bool DLL_EXPORT CreateMissPlugin(void ** pobj)
    {
        *pobj = new MissPluginMain;
        return *pobj != NULL;
    }

    int DLL_EXPORT GetAPIVersion()
    {
        return MissPluginBase::APIVersion();
    }

#ifdef __cplusplus
}
#endif
