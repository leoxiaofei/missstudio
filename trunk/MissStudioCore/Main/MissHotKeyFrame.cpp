#include "MissHotKeyFrame.h"

#include "MissSetHotKey.h"
#include "../BLL/MissHotKeyManager.h"
#include "../BLL/MissPluginManager.h"
#include "../../MissAPI/plugin/MissHotKeyFuncBase.h"
#include "../../MissAPI/plugin/MissPluginBase.h"
#include "../Model/MissPluginTreeListData.h"
#include <iostream>

class MissHotKeyFrame::MissHotKeyFrameImpl
{
public:

};

MissHotKeyFrame::MissHotKeyFrame( wxWindow* parent )
    : MissHotKeyFrameBase( parent )
    , m_pImpl(new MissHotKeyFrameImpl)
{
    InitUI();
    CentreOnScreen();
}

void MissHotKeyFrame::InitUI()
{
    // m_treelist->SetBackgroundColour(wxColour(240,240,240));
    MissPluginBase* pPlugin(NULL);
    wxTreeItemId idRoot = m_listHotKey->AddRoot(_T("Miss Studio"));
    wxTreeItemId idParent, idItem;
    unsigned int nPluginIndex = 0;
    unsigned int nFuncIndex = 0;
    std::vector<SPluginHotKeyData>& datas = MissPluginManager::Instance().GetHotKeyManager().GetHotKeyData();
    for(std::vector<SPluginHotKeyData>::iterator itor = datas.begin();
            itor != datas.end(); ++itor)
    {
        pPlugin = MissPluginManager::Instance().QueryPluginByInterface(itor->pHotKeyBase);
        if(pPlugin)
        {
            nFuncIndex = -1;
            idParent = m_listHotKey->AppendItem(idRoot, wxEmptyString);
            m_listHotKey->SetItemText(idParent, 0, pPlugin->GetPlugInfo().strPluginName);

            for(HotKeyDataSet::iterator hkitor = itor->vecHotKey.begin();
                    hkitor != itor->vecHotKey.end(); ++hkitor)
            {
                idItem = m_listHotKey->AppendItem(idParent, wxEmptyString, -1, -1,
                                                  new MissPluginTreeListData(nPluginIndex, ++nFuncIndex));
                m_listHotKey->SetItemText(idItem, 0, hkitor->strFuncName);
                m_listHotKey->SetItemText(idItem, 1, hkitor->strHotKey);
                m_listHotKey->SetItemText(idItem, 2, hkitor->strFuncDesc);
            }
            ++nPluginIndex;
        }
    }
    m_listHotKey->ExpandAll(idRoot);
}

void MissHotKeyFrame::OnHotKeyTreeItemActivated(wxTreeEvent& event)
{
    wxTreeItemId idItemIndex = event.GetItem();
    MissPluginTreeListData* pData = static_cast<MissPluginTreeListData*>
                                    (m_listHotKey->GetItemData(idItemIndex));
    if(pData != NULL)
    {
        unsigned int nPlugin = pData->GetPluginIndex();
        unsigned int nFunc   = pData->GetFuncIndex();
        wxString strHotkey;
        if(MissPluginManager::Instance().GetHotKeyManager().
                GetHotkeyString(nPlugin, nFunc, strHotkey))
        {
            MissSetHotKey dlg(strHotkey,this);
            if(dlg.ShowModal() == wxID_OK)
            {
                dlg.GetHotKeyString(strHotkey);
                if(!MissPluginManager::Instance().GetHotKeyManager().
                        ModifyHotKey(nPlugin, nFunc, strHotkey))
                {
                    strHotkey.Clear();
                    wxMessageBox(wxT("抱歉，快捷键冲突，请重新设置。"));
                }
                m_listHotKey->SetItemText(idItemIndex,1,strHotkey);
            }
        }
    }
}
