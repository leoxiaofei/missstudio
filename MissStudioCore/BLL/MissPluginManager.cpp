#include "MissPluginManager.h"

#include <wx/dynlib.h>
#include "../../MissAPI/plugin/MissPluginBase.h"

class MissPluginManager::MissPluginManagerImpl
{
public:
    std::vector<PluginData> m_vecPlugin;
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

bool MissPluginManager::LoadDll(const wxString& strPath, IMissMain* pParent)
{
    PluginData data;
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
        data.pPlugin->LoadPlugin();
        return true;
    }
    while(0);
    delete data.pDllHandle;
    assert(false);
    return false;
}
