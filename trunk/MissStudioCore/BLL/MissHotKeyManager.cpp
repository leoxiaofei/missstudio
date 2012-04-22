#include "MissHotKeyManager.h"
#include "../Main/MissStudioCoreMain.h"
#include "../Widget/wxKeyMonitorTextCtrl.h"

#include "../../MissAPI/plugin/MissHotKeyFuncBase.h"

#include <iostream>

class MissHotKeyManager::MissHotKeyManagerImpl
{
public:
    MissHotKeyManagerImpl()
        :m_nHotkeyStart(1000) {}

    wxWindow*                       m_pParent;
    int                             m_nHotkeyStart;
    std::vector<SPluginHotKeyData>  m_vecHotKeyData;
};


MissHotKeyManager::MissHotKeyManager():
    m_pImpl(new MissHotKeyManagerImpl)
{
    //ctor
}

void MissHotKeyManager::SetMainWindow(wxWindow* pParent)
{
    m_pImpl->m_pParent = pParent;
}

MissHotKeyManager::~MissHotKeyManager()
{
    //dtor
}

std::vector<SPluginHotKeyData>& MissHotKeyManager::GetHotKeyData()
{
    return m_pImpl->m_vecHotKeyData;
}

void MissHotKeyManager::RunFuncFromHotKey(int nHotKeyID)
{
    int nFuncIndex;
    for(std::vector<SPluginHotKeyData>::reverse_iterator ritor = m_pImpl->m_vecHotKeyData.rbegin();
            ritor != m_pImpl->m_vecHotKeyData.rend(); ++ritor)
    {
        nFuncIndex = nHotKeyID - ritor->nStartID;
        if(nFuncIndex >= 0)
        {
            if(static_cast<unsigned int>(nFuncIndex) < ritor->vecHotKey.size())
            {
                ritor->pHotKeyBase->RunFunc(nFuncIndex);
            }
            else
            {
                assert(false);
            }
            break;
        }
    }
}

bool MissHotKeyManager::RegHotKeys(const std::vector<SHotKeyData>& vecHotKey, MissHotKeyFuncBase* pChild)
{
    SPluginHotKeyData data;
    data.nStartID = m_pImpl->m_nHotkeyStart;
    data.vecHotKey = vecHotKey;
    data.pHotKeyBase = pChild;

    bool bRet(true);

    for(unsigned int ix = 0; ix != data.vecHotKey.size(); ++ix)
    {
        if(!RegHotKey(m_pImpl->m_nHotkeyStart + ix, data.vecHotKey[ix].strHotKey))
        {
            data.vecHotKey[ix].strHotKey.Clear();
            bRet = false;
        }
    }

    m_pImpl->m_vecHotKeyData.push_back(data);
    m_pImpl->m_nHotkeyStart += vecHotKey.size();
    return bRet;
}

bool MissHotKeyManager::ModifyHotKey(unsigned int nPlugin, unsigned int nFunc,
                                     const wxString& strHotKey)
{
    std::cout << nPlugin << " " << nFunc << " " << strHotKey << std:: endl;
    bool bRet(false);
    if(nPlugin < m_pImpl->m_vecHotKeyData.size())
    {
        if(nFunc < m_pImpl->m_vecHotKeyData[nPlugin].vecHotKey.size())
        {
            int nHotKeyID = m_pImpl->m_vecHotKeyData[nPlugin].nStartID + nFunc;
            UnRegHotKey(nHotKeyID);
            if(strHotKey.IsEmpty() || RegHotKey(nHotKeyID,strHotKey))
            {
                m_pImpl->m_vecHotKeyData[nPlugin].vecHotKey[nFunc].strHotKey = strHotKey;
                bRet = true;
            }
            else
            {
                m_pImpl->m_vecHotKeyData[nPlugin].vecHotKey[nFunc].strHotKey.Clear();
            }

            ///通知插件，快捷键已修改
            m_pImpl->m_vecHotKeyData[nPlugin].pHotKeyBase->ModifiedHotKey(nFunc,
                    m_pImpl->m_vecHotKeyData[nPlugin].vecHotKey[nFunc].strHotKey);

        }
    }
    return bRet;
}

bool MissHotKeyManager::RegHotKey(int nHotKeyID, const wxString& strHotKey)
{
    bool bRet(false);
    int nKeyCode = wxKeyBind::StringToKeyCode(strHotKey);
    int nKeyModifier = wxKeyBind::StringToKeyModifier(strHotKey);

    if(m_pImpl->m_pParent->RegisterHotKey(nHotKeyID, nKeyModifier, nKeyCode))
    {
        m_pImpl->m_pParent->Connect( nHotKeyID, wxEVT_HOTKEY,
                                     wxKeyEventHandler( MissStudioCoreFrame::OnHotKey ) );
        bRet = true;
    }
    return bRet;
}

bool MissHotKeyManager::UnRegHotKey(int nHotKeyID)
{
    bool bRet(false);
    if(m_pImpl->m_pParent->UnregisterHotKey(nHotKeyID))
    {
        m_pImpl->m_pParent->Disconnect( nHotKeyID, wxEVT_HOTKEY);
        bRet = true;
    }
    return bRet;
}

bool MissHotKeyManager::GetHotkeyString(unsigned int nPlugin, unsigned int nFunc, wxString& strValue)
{
    std::vector<SPluginHotKeyData>& datas = m_pImpl->m_vecHotKeyData;
    if(nPlugin < datas.size() && nFunc < datas[nPlugin].vecHotKey.size())
    {
        strValue = datas[nPlugin].vecHotKey[nFunc].strHotKey;
        return true;
    }
    return false;
}
