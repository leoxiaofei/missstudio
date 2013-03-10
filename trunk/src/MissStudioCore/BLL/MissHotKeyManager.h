#ifndef MISSHOTKEYMANAGER_H
#define MISSHOTKEYMANAGER_H

#include "MissAPI/interface/IMissHotKeyMgr.h"

#include <memory>
#include <map>

struct HotKeyRelation
{
    ///Key: HotkeyId Value: SHotKeyMajor
    std::map<unsigned int, SHotKeyMajor> mapIdToMajor;
    MissHotKeyFuncBase*                  pHotKeyFunc;
};

class MissHotKeyFuncBase;
class MissPluginBase;

class MissHotKeyManager
{
    class Impl;

public:
    static MissHotKeyManager& Instance()
    {
        static MissHotKeyManager theSingleton;
        return theSingleton;
    }

    MissPluginBase* GetPluginBase(MissHotKeyFuncBase* pFunc) const;
    bool RegHotKeys(MissPluginBase* pPluginBase, const HotKeyMajorSet& vecHotKey, MissHotKeyFuncBase* pFunc);
    bool UnRegHotKeys(MissHotKeyFuncBase* pFunc);
    bool UnloadPlugin(MissPluginBase* pPluginBase);


    std::vector<HotKeyRelation>& GetHotKeyRelation();

    void RunFuncFromHotKey(unsigned int uHotKeyId);
    bool ModifyHotKey(unsigned int uRelationIndex, unsigned int uHotkeyId, const SHotKeyMajor& sHotKey);

protected:
    bool RegHotKeyId(unsigned int uHotKeyId, const wxString& strHotKey);
    bool UnRegHotKeyId(unsigned int uHotKeyId);
    unsigned int GetNewHotKeyId();

private:
    MissHotKeyManager();
    ~MissHotKeyManager();
    MissHotKeyManager(const MissHotKeyManager&);
    MissHotKeyManager& operator=(const MissHotKeyManager&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSHOTKEYMANAGER_H
