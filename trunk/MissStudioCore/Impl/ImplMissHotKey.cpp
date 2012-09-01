#include "ImplMissHotKey.h"
#include "../BLL/MissPluginManager.h"
#include "../BLL/MissHotKeyManager.h"


ImplMissHotKey::ImplMissHotKey(MissPluginBase* pPlugMain)
: m_pPlugMain(pPlugMain)
{
    //ctor
}

ImplMissHotKey::~ImplMissHotKey()
{
    //dtor
}

bool ImplMissHotKey::RegHotKeys(const HotKeyDataSet& vecHotKey,
                           MissHotKeyFuncBase* pChild)
{
    MissPluginManager::Instance().RegPluginInterface(m_pPlugMain, pChild);
    return MissPluginManager::Instance().GetHotKeyManager().RegHotKeys(vecHotKey, pChild);
}
