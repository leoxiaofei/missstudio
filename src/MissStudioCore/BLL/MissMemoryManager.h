#ifndef MISSMEMORYMANAGER_H__
#define MISSMEMORYMANAGER_H__
#include <memory>


class wxString;
class wxVariant;
class MissPluginBase;
class MissSharedMemoryBase;

class MissMemoryManager
{
    class Impl;
public:
    static MissMemoryManager& Instance()
    {
        static MissMemoryManager theSingleton;
        return theSingleton;
    }

    bool RegSharedMemory(MissPluginBase* pPluginBase, const wxString& strMemoryName, MissSharedMemoryBase* pFunc);
    bool UnRegSharedMemory(const wxString& strMemoryName, MissSharedMemoryBase* pFunc);

    bool GetVariant( const MissPluginBase* pPlugMain, const wxString& strMemoryName, wxVariant& varData );
    bool SetVariant( const MissPluginBase* pPlugMain, const wxString& strMemoryName, const wxVariant& varData );

    bool UnloadPlugin(MissPluginBase* pPluginBase);

protected:
    void NotifyChanged(const wxString& strMemoryName, const wxVariant& varData);

private:
    MissMemoryManager();
    ~MissMemoryManager();
    MissMemoryManager(const MissMemoryManager&);
    MissMemoryManager& operator=(const MissMemoryManager&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};


#endif // MISSMEMORYMANAGER_H__
