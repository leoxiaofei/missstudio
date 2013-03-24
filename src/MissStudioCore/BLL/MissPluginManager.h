#ifndef MISSPLUGINMANAGER_H
#define MISSPLUGINMANAGER_H

#include <wx/string.h>
#include <memory>

class wxDynamicLibrary;
class MissPluginBase;

// class MissHotKeyManager;
// class MissWidgetManager;
class MissStudioCoreFrame;

class MissPluginManager
{
    class Impl;

    struct SDllData
    {
        wxDynamicLibrary*      pDllHandle;
        MissPluginBase*        pPlugin;
        wxString               strPath;
    };

public:
    static MissPluginManager& Instance()
    {
        static MissPluginManager theSingleton;
        return theSingleton;
    }

public:
    void LoadPlugin();
    //void UnloadPlugin(MissPluginBase* pPlugin);
    //void UnloadAll();
    //void PreCloseALL();
    void ClosePluginAll();
    void UnloadDllALL();
    void ClosePlugin(MissPluginBase* pPlugin);
    void UnloadDll(MissPluginBase* pPlugin);

    bool GetPluginPath(const MissPluginBase* pPlugin, wxString& strPath) const;
    bool GetPluginConfigPath(const MissPluginBase* pPlugin, wxString& strPath) const;
    bool GetPluginByGuid(const wxString& strGuid, MissPluginBase*& pPlugin) const;

protected:
    bool LoadDll(const wxString& strPath, const wxString& strFile);
    bool ReleaseDll(SDllData& sDllData);

private:
    MissPluginManager();
    ~MissPluginManager();
    MissPluginManager(const MissPluginManager&);
    MissPluginManager& operator=(const MissPluginManager&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSPLUGINMANAGER_H
