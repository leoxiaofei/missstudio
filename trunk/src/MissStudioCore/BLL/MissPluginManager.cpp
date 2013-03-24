#include "MissPluginManager.h"

//#include "../BLL/MissWidgetManager.h"
//#include "../BLL/MissHotKeyManager.h"
//#include "../Impl/ImplMissMain.h"

#include "../Impl/MissMainEntry.h"
#include "MissAPI/plugin/MissPluginBase.h"


#include <assert.h>
#include <map>
#include <vector>
#include <wx/dir.h>
#include <wx/dynlib.h>
#include <wx/filename.h>
#include "MissFunctor.h"
#include "../Common/MissPaths.h"


class MissPluginManager::Impl
{
public:
    std::vector<SDllData>         vecPlugin;
};

MissPluginManager::MissPluginManager()
: m_pImpl(new Impl)
{
    //ctor
}

MissPluginManager::~MissPluginManager()
{
    //dtor
}

void MissPluginManager::LoadPlugin()
{
    wxString strDiraddr = MissPaths::Instance().GetPluginDir();
    wxDir dirPath(strDiraddr);
    wxDir dirPlugin;
    if (dirPath.IsOpened())
    {
        wxString strPluginPath;
        bool bFindPath = dirPath.GetFirst(&strPluginPath, wxT(""), wxDIR_DIRS);
        while (bFindPath)
        {
            if(dirPlugin.Open(strDiraddr + strPluginPath))
            {
                wxString strFile;
                bool bFindPlugin = dirPlugin.GetFirst(&strFile, wxT("*.dll"), wxDIR_FILES);
                while (bFindPlugin)
                {
                    LoadDll(strDiraddr + strPluginPath + "\\" , strFile);
                    bFindPlugin = dirPlugin.GetNext(&strFile);
                }
            }
            bFindPath = dirPath.GetNext(&strPluginPath);
        }
    }
}

// void MissPluginManager::UnloadPlugin( MissPluginBase* pPlugin )
// {
//     for (std::vector<SDllData>::iterator itor = m_pImpl->vecPlugin.begin();
//         itor != m_pImpl->vecPlugin.end(); )
//     {
//         if (itor->pPlugin == pPlugin)
//         {
//             ReleaseDll(*itor);
//             itor = m_pImpl->vecPlugin.erase(itor);
//         }
//         else
//         {
//             ++itor;
//         }
//     }
// }
// 
// void MissPluginManager::UnloadAll()
// {
//     for (std::vector<SDllData>::iterator itor = m_pImpl->vecPlugin.begin();
//         itor != m_pImpl->vecPlugin.end(); ++itor)
//     {
//         ReleaseDll(*itor);
//     }
//     m_pImpl->vecPlugin.clear();
// }

bool MissPluginManager::LoadDll( const wxString& strPath, const wxString& strFile )
{
    SDllData data;
    data.pDllHandle = new wxDynamicLibrary(strPath + strFile);
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
            (PFN_CreateMissStudioPlug)(data.pDllHandle->GetSymbol(wxT("CreateMissPlugin")));
        if(!pFun)
        {
            data.pDllHandle->Unload();
            break;
        }
        if(!pFun((void **)&data.pPlugin))
        {
            break;
        }
        data.strPath = strPath;
        //data.strPath = strPath.Left(strPath.rfind('.'));
        m_pImpl->vecPlugin.push_back(data);
        ///调用初始化函数；
        data.pPlugin->InitPlugin(std::tr1::shared_ptr<IMissMain>(
            new MissMainEntry(data.pPlugin)));
        //std::wcout<<strPath.Left(strPath.rfind('.')).c_str()<<std::endl;
        return true;
    }
    while(0);
    delete data.pDllHandle;
    assert(false);
    return false;
}

bool MissPluginManager::ReleaseDll(SDllData& sDllData)
{
    bool bRet(false);

    delete sDllData.pPlugin;
    sDllData.pPlugin = NULL;

    ///卸载dll
    sDllData.pDllHandle->Unload();
    delete sDllData.pDllHandle;
    sDllData.pDllHandle = NULL;

    sDllData.strPath.Clear();

    return bRet;
}

bool MissPluginManager::GetPluginPath(const MissPluginBase* pPlugin, wxString& strPath) const
{
    bool bRet(false);
    for(std::vector<SDllData>::const_iterator citor =
        m_pImpl->vecPlugin.begin(); citor != m_pImpl->vecPlugin.end(); ++citor)
    {
        if(citor->pPlugin == pPlugin)
        {
            strPath = citor->strPath;
            bRet = true;
        }
    }
    return bRet;
}

bool MissPluginManager::GetPluginConfigPath( const MissPluginBase* pPlugin, wxString& strPath ) const
{ 
    bool bRet(false);
    wxString strPCD = MissPaths::Instance().GetConfigPath();
    strPath = strPCD + pPlugin->GetPluginName() + wxT("\\");

    if (!wxDir::Exists(strPath))
    {
        wxDir::Make(strPath, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
    }
    return bRet;
}

bool MissPluginManager::GetPluginByGuid( const wxString& strGuid, MissPluginBase*& pPlugin ) const
{
    bool bRet(false);
    for (std::vector<SDllData>::iterator itor = m_pImpl->vecPlugin.begin();
        itor != m_pImpl->vecPlugin.end(); ++itor)
    {
        if(itor->pPlugin->GetPluginGUID() == strGuid)
        {
            pPlugin = itor->pPlugin;
            bRet = true;
            break;
        }
    }
    return bRet;
}

void MissPluginManager::ClosePlugin( MissPluginBase* pPlugin )
{
    ///通知模块关闭对该插件的使用。
    pPlugin->ClosePlugin();
    PluginUnloader ()(pPlugin);
}

void MissPluginManager::UnloadDll( MissPluginBase* pPlugin )
{
    for (std::vector<SDllData>::iterator itor = m_pImpl->vecPlugin.begin();
        itor != m_pImpl->vecPlugin.end(); )
    {
        if (itor->pPlugin == pPlugin)
        {
            ReleaseDll(*itor);
            itor = m_pImpl->vecPlugin.erase(itor);
        }
        else
        {
            ++itor;
        }
    }
}

void MissPluginManager::ClosePluginAll()
{
    for (std::vector<SDllData>::iterator itor = m_pImpl->vecPlugin.begin();
        itor != m_pImpl->vecPlugin.end(); ++itor)
    {
        ClosePlugin(itor->pPlugin);
    }
}

void MissPluginManager::UnloadDllALL()
{
    for (std::vector<SDllData>::iterator itor = m_pImpl->vecPlugin.begin();
        itor != m_pImpl->vecPlugin.end(); ++itor)
    {
        ReleaseDll(*itor);
    }
    m_pImpl->vecPlugin.clear();
}



