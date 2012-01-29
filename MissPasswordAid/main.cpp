#include "main.h"
#include "Main/MissPluginMain.h"

// a sample exported function
bool DLL_EXPORT CreateMissStudioPlug(void ** pobj, void* pParent)
{
    *pobj = new MissPluginMain((IMissMain*)pParent);
    return *pobj != NULL;
}

int DLL_EXPORT GetAPIVersion()
{
    return MissPluginBase::APIVersion();
}

/*
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
*/
