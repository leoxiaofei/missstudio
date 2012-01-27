#include "MissHotKeyManager.h"
#include "../Main/MissStudioCoreMain.h"
#include "../Widget/wxKeyMonitorTextCtrl.h"

#include "../../MissAPI/plugin/MissHotKeyFuncBase.h"

class MissHotKeyManager::MissHotKeyManagerImpl
{
public:
    MissHotKeyManagerImpl():m_nHotkeyStart(1000){}
    wxWindow* m_pParent;
    int m_nHotkeyStart;
    std::vector<ChildData> m_vecChildData;
};


MissHotKeyManager::MissHotKeyManager(wxWindow* pParent):
m_pImpl(new MissHotKeyManagerImpl)
{
    //ctor
    m_pImpl->m_pParent = pParent;
}

MissHotKeyManager::~MissHotKeyManager()
{
    //dtor
}

std::vector<ChildData>& MissHotKeyManager::GetChildData()
{
    return m_pImpl->m_vecChildData;
}

void MissHotKeyManager::RunFuncFromHotKey(int nHotKeyID)
{
    int nFuncIndex;
    for(std::vector<ChildData>::reverse_iterator ritor = m_pImpl->m_vecChildData.rbegin();
        ritor != m_pImpl->m_vecChildData.rend(); ++ritor)
    {
        nFuncIndex = nHotKeyID - ritor->nStartID;
        if(nFuncIndex >= 0)
        {
            if(static_cast<unsigned int>(nFuncIndex) < ritor->vecHotKey.size())
            {
                ritor->pChild->RunFunc(nFuncIndex);
            }
            else
            {
                assert(false);
            }
            break;
        }
    }
}

bool MissHotKeyManager::RegHotKeys(const std::vector<SHotKey>& vecHotKey, MissHotKeyFuncBase* pChild)
{
    ChildData data;
    data.nStartID = m_pImpl->m_nHotkeyStart;
    //data.nCount = vecHotKey.size();
    data.vecHotKey = vecHotKey;
    data.pChild = pChild;

    bool bRet(true);
    int nKeyCode, nKeyModifier;
    for(unsigned int ix = 0; ix != data.vecHotKey.size(); ++ix)
    {
        nKeyCode = wxKeyBind::StringToKeyCode(data.vecHotKey[ix].strHotKey);
        nKeyModifier = wxKeyBind::StringToKeyModifier(data.vecHotKey[ix].strHotKey);

        if(m_pImpl->m_pParent->RegisterHotKey(m_pImpl->m_nHotkeyStart + ix, nKeyModifier, nKeyCode))
        {
            m_pImpl->m_pParent->Connect( m_pImpl->m_nHotkeyStart + ix, wxEVT_HOTKEY,
                    wxKeyEventHandler( MissStudioCoreFrame::OnHotKey ) );
        }
        else
        {
            data.vecHotKey[ix].strHotKey.Clear();
            bRet = false;
        }
    }

    m_pImpl->m_vecChildData.push_back(data);
    m_pImpl->m_nHotkeyStart += vecHotKey.size();
    return bRet;
}

