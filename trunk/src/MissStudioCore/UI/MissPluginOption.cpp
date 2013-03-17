#include "MissPluginOption.h"

#include <wx/dataview.h>
#include "../Model/MissHotKeyModel.h"
#include "MissHotKeySetting.h"
#include "../Common/AutoColumnWidth.h"

class MissPluginOption::Impl
{
public:
    wxDataViewCtrl*                  pHotKeyList;
    wxObjectDataPtr<MissHotKeyModel> ptHotKeyModel;
    AutoColumnWidth                  acwHotKeyList;
};



MissPluginOption::MissPluginOption( wxWindow* parent )
: PluginOptionBase( parent )
, m_pImpl(new Impl)
{
    InitUi();
    BindEvent();
}

MissPluginOption::~MissPluginOption()
{
    UnbindEvent();
}

void MissPluginOption::InitUi()
{
    wxDataViewCtrl* pHotKeyList;
    pHotKeyList = new wxDataViewCtrl(panHotKey, wxID_ANY);
    m_pImpl->acwHotKeyList.SetViewCtrl(pHotKeyList);
    m_pImpl->acwHotKeyList.SetAutoColumn(1);
    m_pImpl->acwHotKeyList.SetMinWidth(100);
    m_pImpl->ptHotKeyModel = new MissHotKeyModel;
    pHotKeyList->AssociateModel( m_pImpl->ptHotKeyModel.get() );
    m_pImpl->acwHotKeyList << pHotKeyList->AppendTextColumn(wxT("插件名称"), 0, wxDATAVIEW_CELL_INERT, 120);
    m_pImpl->acwHotKeyList << pHotKeyList->AppendTextColumn(wxT("功能描述"), 1, wxDATAVIEW_CELL_INERT, 200);
    m_pImpl->acwHotKeyList << pHotKeyList->AppendTextColumn(wxT("快捷键"), 2, wxDATAVIEW_CELL_INERT, 90);
    m_pImpl->acwHotKeyList << pHotKeyList->AppendToggleColumn (wxT("启用"), 3, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE );
    sizerHotKey->Add(pHotKeyList, 1, wxEXPAND | wxALL, 5 );
    sizerHotKey->Layout();
    m_pImpl->pHotKeyList = pHotKeyList;
    //pHotKeyList->ExpandAncestors();
}

void MissPluginOption::BindEvent()
{
    choFilter->Bind( wxEVT_COMMAND_CHOICE_SELECTED, &MissPluginOption::OnFilterChoice, this );
    m_pImpl->pHotKeyList->Bind( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, &MissPluginOption::OnHotKeyItemActivated, this );
}


void MissPluginOption::UnbindEvent()
{
    choFilter->Unbind( wxEVT_COMMAND_CHOICE_SELECTED, &MissPluginOption::OnFilterChoice, this );
    m_pImpl->pHotKeyList->Unbind( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, &MissPluginOption::OnHotKeyItemActivated, this );

}

void MissPluginOption::OnFilterChoice( wxCommandEvent& event )
{
    std::cout<<event.GetString()<<std::endl;
}

void MissPluginOption::OnHotKeyItemActivated( wxDataViewEvent& event )
{
    unsigned int uRelationIndex(0), uHotkeyId(0);
    wxDataViewItem Item = event.GetItem();
    if(m_pImpl->ptHotKeyModel->GetIndexData(Item, uRelationIndex, uHotkeyId))
    {
        wxVariant variant;
        event.GetModel()->GetValue(variant, Item, 2);
        MissHotKeySetting hotkeyDlg(variant.GetString(), this);
        if(hotkeyDlg.ShowModal() == wxID_OK)
        {
            wxString strHotKey;
            hotkeyDlg.GetHotKeyString(strHotKey);
            variant = strHotKey;
            event.GetModel()->SetValue(variant, Item, 2);
            event.GetModel()->ItemChanged(Item);
        }
    }
}
