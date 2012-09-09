#ifndef MISSPLUGINMANAGER_H
#define MISSPLUGINMANAGER_H

class wxDynamicLibrary;
class MissPluginBase;

class MissHotKeyManager;
class MissWidgetManager;
class MissStudioCoreFrame;

class MissPluginManager
{
    class MissPluginManagerImpl;

    struct SPluginData
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
    void Init(wxWindow* pMainWindow);
    bool LoadDll(const wxString& strPath, MissStudioCoreFrame* pParent);
    bool UnloadDll();

    bool FindPluginPath(const MissPluginBase* pPlugin, wxString& strPath) const;
    MissHotKeyManager& GetHotKeyManager();
    MissWidgetManager& GetWidgetManager();

    MissPluginBase* QueryPluginByInterface(void* pInterface);
    void RegPluginInterface(MissPluginBase* pPlugin, void* pInterface);

    void GetPluginNameList(std::vector<wxString>& vecNames);

protected:
private:
    MissPluginManager();
    virtual ~MissPluginManager();
    MissPluginManager(const MissPluginManager&);
    MissPluginManager& operator=(const MissPluginManager&);

private:
    shared_ptr<MissPluginManagerImpl> m_pImpl;
};

#endif // MISSPLUGINMANAGER_H
