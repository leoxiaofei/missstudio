#include "ImplMissHotKeyMgr.h"

#include "../BLL/MissPluginManager.h"
#include "../BLL/MissHotKeyManager.h"


ImplMissHotKeyMgr::ImplMissHotKeyMgr(MissPluginBase* pPlugMain)
: m_pPlugMain(pPlugMain)
{
    //ctor
}

ImplMissHotKeyMgr::~ImplMissHotKeyMgr()
{
    //dtor
}

bool ImplMissHotKeyMgr::RegHotKeys(const HotKeyMajorSet& vecHotKey,
                           MissHotKeyFuncBase* pFunc)
{
     return MissHotKeyManager::Instance().RegHotKeys(m_pPlugMain, vecHotKey, pFunc);
}

bool ImplMissHotKeyMgr::UnRegHotKeys( MissHotKeyFuncBase* pFunc )
{
    return MissHotKeyManager::Instance().UnRegHotKeys(pFunc);
}
