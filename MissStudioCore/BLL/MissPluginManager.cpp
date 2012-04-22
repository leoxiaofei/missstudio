#include "MissPluginManager.h"

#include "../BLL/MissWidgetManager.h"
#include "../BLL/MissHotKeyManager.h"

#include <wx/dynlib.h>
#include "../../MissAPI/plugin/MissPluginBase.h"

//#include <iostream>

class MissPluginManager::MissPluginManagerImpl
{
public:
    std::vector<SPluginData> m_vecPlugin;
    MissHotKeyManager    m_HotKeyManager;
    MissWidgetManager    m_WidgetManager;
};

MissPluginManager::MissPluginManager():
    m_pImpl(new MissPluginManagerImpl)
{
    //ctor
}

MissPluginManager::~MissPluginManager()
{
    //dtor
}

void MissPluginManager::Init(wxWindow* pMainWindow)
{
    m_pImpl->m_HotKeyManager.SetMainWindow(pMainWindow);
}

bool MissPluginManager::LoadDll(const wxString& strPath, IMissMain* pParent)
{
    SPluginData data;
    data.pDllHandle = new wxDynamicLibrary(strPath);
    do
    {
        if ( !data.pDllHandle->IsLoaded() )
        {
            break;
        }

        ///验证插件API是否和主程序匹配
        typedef int (* PFN_GetAPIVersion)();
        PFN_GetAPIVersion pAPIFun = (PFN_GetAPIVersion)(
                                        data.pDllHandle->GetSymbol(wxT("GetAPIVersion")));
        if(!pAPIFun || pAPIFun() != MissPluginBase::APIVersion() )
        {
            data.pDllHandle->Unload();
            break;
        }

        typedef bool (* PFN_CreateMissStudioPlug)(void **, void* );
        PFN_CreateMissStudioPlug pFun = (PFN_CreateMissStudioPlug)(
                                            data.pDllHandle->GetSymbol(wxT("CreateMissStudioPlug")));
        if(!pFun)
        {
            data.pDllHandle->Unload();
            break;
        }
        if(!pFun((void **)&data.pPlugin, pParent))
        {
            break;
        }
        m_pImpl->m_vecPlugin.push_back(data);
        ///调用初始化函数；
        data.pPlugin->LoadPlugin(strPath.Left(strPath.rfind('.')));
        //std::wcout<<strPath.Left(strPath.rfind('.')).c_str()<<std::endl;
        return true;
    }
    while(0);
    delete data.pDllHandle;
    assert(false);
    return false;
}

MissHotKeyManager& MissPluginManager::GetHotKeyManager()
{
    return m_pImpl->m_HotKeyManager;
}

MissWidgetManager& MissPluginManager::GetWidgetManager()
{
    return m_pImpl->m_WidgetManager;
}
