#include "MissHotKeyManager.h"
#include "../Widget/wxKeyMonitorTextCtrl.h"

#include "MissAPI/plugin/MissHotKeyFuncBase.h"

#include <iostream>
#include <wx/event.h>
#include "../UI/MissCoreFrame.h"
#include "../Common/CustomId.h"
#include "MissFuncFinder.h"


class MissHotKeyManager::Impl
{
public:
    Impl()
    : uHotkeyStart(DTD::CI_HOTKEY_ID_BEGIN) {}

    unsigned int                        uHotkeyStart;
    std::vector<HotKeyRelation>         vecHotKeyRelation;
    MissFuncFinder<MissHotKeyFuncBase>  funcFinder;
};


MissHotKeyManager::MissHotKeyManager()
: m_pImpl(new Impl)
{
    //ctor
}


MissHotKeyManager::~MissHotKeyManager()
{
    //dtor
}

void MissHotKeyManager::RunFuncFromHotKey(unsigned int uHotKeyId)
{
    if(uHotKeyId > DTD::CI_HOTKEY_ID_BEGIN)
    {
        std::map<unsigned int, SHotKeyMajor>::iterator iFind;
        for (std::vector<HotKeyRelation>::iterator itor = m_pImpl->vecHotKeyRelation.begin();
            itor != m_pImpl->vecHotKeyRelation.end(); ++itor)
        {
            iFind = itor->mapIdToMajor.find(uHotKeyId);
            if (iFind != itor->mapIdToMajor.end())
            {
                itor->pHotKeyFunc->RunFunc(iFind->second.nFuncId);
                break;
            }
        }
    }
    else
    {
        assert(false);
    }
}

bool MissHotKeyManager::RegHotKeys(MissPluginBase* pPluginBase, const HotKeyMajorSet& vecHotKey, MissHotKeyFuncBase* pFunc)
{
    bool bRet(true);
    m_pImpl->funcFinder.RegPluginFunc(pPluginBase, pFunc);
    std::map<unsigned int, SHotKeyMajor>::iterator iFind;
    for (std::vector<HotKeyRelation>::iterator itor = m_pImpl->vecHotKeyRelation.begin();
        itor != m_pImpl->vecHotKeyRelation.end(); ++itor)
    {
        if (itor->pHotKeyFunc == pFunc)
        {
            UnRegHotKeys(pFunc);
            break;
        }
    }

    m_pImpl->vecHotKeyRelation.resize(m_pImpl->vecHotKeyRelation.size() + 1);
    HotKeyRelation& hotKeyRelation = m_pImpl->vecHotKeyRelation.back();
    hotKeyRelation.pHotKeyFunc = pFunc;
    int nHotKeyId;
    for(HotKeyMajorSet::const_iterator citor = vecHotKey.begin(); citor != vecHotKey.end(); ++citor)
    {
        nHotKeyId = GetNewHotKeyId();
        hotKeyRelation.mapIdToMajor[nHotKeyId] = *citor;
        if (citor->bEnable && !citor->strHotKey.IsEmpty())
        {
            if (!RegHotKeyId(nHotKeyId, citor->strHotKey))
            {
                hotKeyRelation.mapIdToMajor[nHotKeyId].bEnable = false;
                bRet = false;
            }
        }
    }

    return bRet;
}

bool MissHotKeyManager::UnRegHotKeys(MissHotKeyFuncBase* pFunc)
{
    bool bRet(false);
    m_pImpl->funcFinder.UnRegPluginFunc(pFunc);
    for(std::vector<HotKeyRelation>::iterator itorRelation = m_pImpl->vecHotKeyRelation.begin(); 
        itorRelation != m_pImpl->vecHotKeyRelation.end(); ++itorRelation)
    {
        if(itorRelation->pHotKeyFunc == pFunc)
        {
            for(std::map<unsigned int, SHotKeyMajor>::iterator itor = itorRelation->mapIdToMajor.begin();
                itor != itorRelation->mapIdToMajor.end(); ++itor)
            {
                UnRegHotKeyId(itor->first);
            }
            m_pImpl->vecHotKeyRelation.erase(itorRelation);
            bRet = true;
            break;
        }
    }
    return bRet;
}

bool MissHotKeyManager::UnloadPlugin( MissPluginBase* pPluginBase )
{
    std::vector<MissHotKeyFuncBase*> vecFunc;
    m_pImpl->funcFinder.QueryFuncByPlugin(pPluginBase, vecFunc);
    for (std::vector<MissHotKeyFuncBase*>::size_type ix = 0; ix != vecFunc.size(); ++ix)
    {
        UnRegHotKeys(vecFunc[ix]);
    }
    return true;
}

 bool MissHotKeyManager::ModifyHotKey(unsigned int uRelationIndex, unsigned int uHotkeyId, const SHotKeyMajor& sHotKey)
 {
     bool bRet(false);
     if(uRelationIndex < m_pImpl->vecHotKeyRelation.size())
     {
         HotKeyRelation& hotKeyRelation = m_pImpl->vecHotKeyRelation[uRelationIndex];
         std::map<unsigned int, SHotKeyMajor>::iterator iFind = hotKeyRelation.mapIdToMajor.find(uHotkeyId);
         if(iFind != hotKeyRelation.mapIdToMajor.end())
         {
             UnRegHotKeyId(uHotkeyId);
             iFind->second = sHotKey;
             bRet = true;
             if (sHotKey.bEnable && !sHotKey.strHotKey.IsEmpty())
             {
                 if (!RegHotKeyId(uHotkeyId,sHotKey.strHotKey))
                 {
                     iFind->second.bEnable = false;
                     bRet = false;
                 }
             }
             ///通知插件，快捷键已修改
             hotKeyRelation.pHotKeyFunc->ModifiedHotKey(iFind->second);
         }
     }
     return bRet;
 }

bool MissHotKeyManager::RegHotKeyId(unsigned int uHotKeyId, const wxString& strHotKey)
{
    bool bRet(false);
    int nKeyCode = wxKeyBind::StringToKeyCode(strHotKey);
    int nKeyModifier = wxKeyBind::StringToKeyModifier(strHotKey);
    bRet = wxAppFrame->RegisterHotKey(uHotKeyId, nKeyModifier, nKeyCode);
    return bRet;
}

bool MissHotKeyManager::UnRegHotKeyId(unsigned int uHotKeyId)
{
    bool bRet(false);
    bRet = wxAppFrame->UnregisterHotKey(uHotKeyId);
    return bRet;
}

unsigned int MissHotKeyManager::GetNewHotKeyId()
{
    assert(m_pImpl->uHotkeyStart < DTD::CI_HOTKEY_ID_END);
    return ++(m_pImpl->uHotkeyStart);
}

std::vector<HotKeyRelation>& MissHotKeyManager::GetHotKeyRelation()
{
    return m_pImpl->vecHotKeyRelation;
}

MissPluginBase* MissHotKeyManager::GetPluginBase( MissHotKeyFuncBase* pFunc ) const
{
    return m_pImpl->funcFinder.QueryPluginByFunc(pFunc);
}


// bool MissHotKeyManager::GetHotkeyString(unsigned int nPlugin, unsigned int nFunc, wxString& strValue)
// {
//     std::vector<SPluginHotKeyData>& datas = m_pImpl->m_vecHotKeyData;
//     if(nPlugin < datas.size() && nFunc < datas[nPlugin].vecHotKey.size())
//     {
//         strValue = datas[nPlugin].vecHotKey[nFunc].strHotKey;
//         return true;
//     }
//     return false;
// }
