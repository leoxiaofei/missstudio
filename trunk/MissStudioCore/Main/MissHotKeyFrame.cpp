#include "MissHotKeyFrame.h"

#include "MissSetHotKey.h"
#include "../BLL/MissHotKeyManager.h"
#include "../../MissAPI/plugin/MissHotKeyFuncBase.h"
#include "../../MissAPI/plugin/MissPluginBase.h"

#include <iostream>

class MissHotKeyFrame::MissHotKeyFrameImpl
{
public:
    MissHotKeyManager* m_pData;
};

MissHotKeyFrame::MissHotKeyFrame( wxWindow* parent, MissHotKeyManager* pData )
:
MissHotKeyFrameBase( parent ),
m_pImpl(new MissHotKeyFrameImpl)
{
    m_pImpl->m_pData = pData;
    InitUI();
    Centre( wxBOTH );
}

void MissHotKeyFrame::InitUI()
{
    m_listHotKey->InsertColumn(0,_T("ID"),wxLIST_FORMAT_LEFT,0);
    m_listHotKey->InsertColumn(1,_T("插件名称"),wxLIST_FORMAT_LEFT,100);
    m_listHotKey->InsertColumn(2,_T("功能"),wxLIST_FORMAT_LEFT,200);
    m_listHotKey->InsertColumn(3,_T("快捷键"),wxLIST_FORMAT_LEFT,100);
    //m_listHotKey->InsertColumn(4,_T(""),wxLIST_FORMAT_LEFT,220);

    int nItemIndex = 0;
    int nPluginIndex = 0;
    int nFuncIndex = -1;
    std::vector<ChildData>& datas = m_pImpl->m_pData->GetChildData();
    for(std::vector<ChildData>::iterator itor = datas.begin();
        itor != datas.end(); ++itor)
    {
        nFuncIndex = -2;
        m_listHotKey->InsertItem(nItemIndex, wxEmptyString);
        m_listHotKey->SetItem(nItemIndex,0,wxString::Format(wxT("%d:%d"),nPluginIndex,++nFuncIndex));
        m_listHotKey->SetItem(nItemIndex,1,itor->pChild->GetPlugin()->GetPlugInfo().strPluginName);
        ++nItemIndex;
        for(std::vector<SHotKey>::iterator hkitor = itor->vecHotKey.begin();
            hkitor != itor->vecHotKey.end(); ++hkitor)
        {
            m_listHotKey->InsertItem(nItemIndex, wxEmptyString);
            //m_listHotKey->SetItem(nItemIndex,0,m_pImpl->m_pData->);
            //m_listHotKey->SetItem(nItemIndex,1,wxString::Format(wxT("%d"),nItemIndex+1));

            m_listHotKey->SetItem(nItemIndex,0,wxString::Format(wxT("%d:%d"),nPluginIndex,++nFuncIndex));
            m_listHotKey->SetItem(nItemIndex,1,wxT("    ┖┄┄┄┄"));
            m_listHotKey->SetItem(nItemIndex,2,hkitor->strDescription);
            m_listHotKey->SetItem(nItemIndex,3,hkitor->strHotKey);
            ++nItemIndex;
        }
        ++nPluginIndex;
    }

}

void MissHotKeyFrame::OnListItemActivated(wxListEvent& event)
{
    //event->
    int nItemIndex = event.GetIndex();
    wxString strID = m_listHotKey->GetItemText(nItemIndex);
    long nFunc = -1;
    strID.AfterLast(':').ToLong(&nFunc);
    std::wcout << strID.c_str() << " " << strID.AfterLast(':').c_str() <<" " << nFunc << std::endl;

    if(nFunc > -1)
    {
        long nPlugin = -1;
        strID.BeforeFirst(':').ToLong(&nPlugin);
        wxString strHotkey;
        if(GetHotkeyString(nPlugin,nFunc,strHotkey))
        {
            MissSetHotKey dlg(strHotkey,this);
            if(dlg.ShowModal() == wxID_OK)
            {
                dlg.GetHotKeyString(strHotkey);
                if(!m_pImpl->m_pData->ModifyHotKey(nPlugin, nFunc, strHotkey))
                {
                    wxMessageBox(wxT("抱歉，快捷键冲突，请重新设置。"));
                    strHotkey.Clear();
                }
                m_listHotKey->SetItem(nItemIndex,3,strHotkey);
            }
        }

    }

}

bool MissHotKeyFrame::GetHotkeyString(int nPlugin, int nFunc, wxString& strValue)
{
    std::vector<ChildData>& datas = m_pImpl->m_pData->GetChildData();
    if(nPlugin < 0 || static_cast<unsigned int>(nPlugin) >= datas.size())
    {
        return false;
    }

    if(nFunc < 0 || static_cast<unsigned int>(nFunc) >= datas[nPlugin].vecHotKey.size())
    {
        return false;
    }

    strValue = datas[nPlugin].vecHotKey[nFunc].strHotKey;
    return true;
}

