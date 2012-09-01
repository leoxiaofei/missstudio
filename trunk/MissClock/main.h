#ifndef __MAIN_H__
#define __MAIN_H__


/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

bool DLL_EXPORT CreateMissStudioPlug(void ** pobj);

int DLL_EXPORT GetAPIVersion();

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
