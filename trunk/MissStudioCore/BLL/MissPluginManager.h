#ifndef MISSPLUGINMANAGER_H
#define MISSPLUGINMANAGER_H

class wxDynamicLibrary;
class MissPluginBase;

class MissHotKeyManager;
class MissWidgetManager;
class IMissMain;

class MissPluginManager
{
    class MissPluginManagerImpl;

    struct SPluginData
    {
        wxDynamicLibrary*      pDllHandle;
        MissPluginBase*        pPlugin;
    };

public:
    static MissPluginManager& Instance()
    {
        static MissPluginManager theSingleton;
        return theSingleton;
    }

public:
    void Init(wxWindow* pMainWindow);
    bool LoadDll(const wxString& strPath, IMissMain* pParent);
    bool UnloadDll();

    MissHotKeyManager& GetHotKeyManager();
    MissWidgetManager& GetWidgetManager();

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
