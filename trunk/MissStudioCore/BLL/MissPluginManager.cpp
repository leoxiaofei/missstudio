#include "MissPluginManager.h"

#include "../BLL/MissWidgetManager.h"
#include "../BLL/MissHotKeyManager.h"
#include "../Impl/ImplMissMain.h"

#include <wx/dynlib.h>
#include "../../MissAPI/plugin/MissPluginBase.h"

#include <map>

class MissPluginManager::MissPluginManagerImpl
{
public:
    std::vector<SPluginData> m_vecPlugin;
    MissHotKeyManager    m_HotKeyManager;
    MissWidgetManager    m_WidgetManager;
    std::map<void*, MissPluginBase*> m_mapPluginQuery;
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

bool MissPluginManager::LoadDll(const wxString& strPath, MissStudioCoreFrame* pParent)
{
    SPluginData data;
    data.strPath = strPath;
    data.pDllHandle = new wxDynamicLibrary(strPath);
    do
    {
        if ( !data.pDllHandle->IsLoaded() )
        {
            break;
        }

        ///验证插件API是否和主程序匹配
        typedef int (* PFN_GetAPIVersion)();
        PFN_GetAPIVersion pAPIFun =
            (PFN_GetAPIVersion)(data.pDllHandle->GetSymbol(wxT("GetAPIVersion")));
        if(!pAPIFun || pAPIFun() != MissPluginBase::APIVersion() )
        {
            data.pDllHandle->Unload();
            break;
        }

        typedef bool (* PFN_CreateMissStudioPlug)(void **);
        PFN_CreateMissStudioPlug pFun =
            (PFN_CreateMissStudioPlug)(data.pDllHandle->GetSymbol(wxT("CreateMissStudioPlug")));
        if(!pFun)
        {
            data.pDllHandle->Unload();
            break;
        }
        if(!pFun((void **)&data.pPlugin))
        {
            break;
        }
        m_pImpl->m_vecPlugin.push_back(data);
        ///调用初始化函数；//strPath.Left(strPath.rfind('.'))
        data.pPlugin->LoadPlugin(std::tr1::shared_ptr<IMissMain>(
                        new ImplMissMain(pParent, data.pPlugin)));
        //std::wcout<<strPath.Left(strPath.rfind('.')).c_str()<<std::endl;
        return true;
    }
    while(0);
    delete data.pDllHandle;
    assert(false);
    return false;
}

bool MissPluginManager::FindPluginPath(const MissPluginBase* pPlugin, wxString& strPath) const
{
    bool bRet(false);
    for(std::vector<SPluginData>::const_iterator citor =
        m_pImpl->m_vecPlugin.begin(); citor != m_pImpl->m_vecPlugin.end(); ++citor)
    {
         if(citor->pPlugin == pPlugin)
         {
             strPath = citor->strPath;
             bRet = true;
         }
    }
    return bRet;
}

MissHotKeyManager& MissPluginManager::GetHotKeyManager()
{
    return m_pImpl->m_HotKeyManager;
}

MissWidgetManager& MissPluginManager::GetWidgetManager()
{
    return m_pImpl->m_WidgetManager;
}

MissPluginBase* MissPluginManager::QueryPluginByInterface(void* pInterface)
{
    MissPluginBase* pRet(NULL);
    std::map<void*, MissPluginBase*>::iterator itor =
    m_pImpl->m_mapPluginQuery.find(pInterface);
    if( itor != m_pImpl->m_mapPluginQuery.begin() )
    {
        pRet = itor->second;
    }
    return pRet;
}

void MissPluginManager::RegPluginInterface(MissPluginBase* pPlugin, void* pInterface)
{
    m_pImpl->m_mapPluginQuery[pInterface] = pPlugin;
}

