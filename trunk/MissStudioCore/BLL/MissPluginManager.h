#ifndef MISSPLUGINMANAGER_H
#define MISSPLUGINMANAGER_H

class wxDynamicLibrary;
class MissPluginBase;
class IMissMain;

struct PluginData
{
    wxDynamicLibrary*      pDllHandle;
    MissPluginBase*        pPlugin;
};

class MissPluginManager
{
    class MissPluginManagerImpl;

    public:
        static MissPluginManager& GetInstance()
        {
            static MissPluginManager theSingleton;
            return theSingleton;
        }
    private:
        MissPluginManager();
        virtual ~MissPluginManager();
        MissPluginManager(const MissPluginManager&);
        MissPluginManager& operator=(const MissPluginManager&);

    public:
        bool LoadDll(const wxString& strPath, IMissMain* pParent);
        bool UnloadDll();

    protected:
    private:
        shared_ptr<MissPluginManagerImpl> m_pImpl;
};

#endif // MISSPLUGINMANAGER_H
