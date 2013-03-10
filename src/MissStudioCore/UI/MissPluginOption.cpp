#include "MissPluginOption.h"

#include <wx/dataview.h>
#include "../Model/MissHotKeyModel.h"
#include "MissHotKeySetting.h"

class MissPluginOption::Impl
{
public:
    wxDataViewCtrl*                  pHotKeyList;
    wxObjectDataPtr<MissHotKeyModel> hotKeyModel;
    //void SetupUi(wxWindow* parent);
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
    
    m_pImpl->hotKeyModel = new MissHotKeyModel;
    pHotKeyList->AssociateModel( m_pImpl->hotKeyModel.get() );
    pHotKeyList->AppendTextColumn(wxT("插件名称"), 0);
    pHotKeyList->AppendTextColumn(wxT("功能描述"), 1);
    pHotKeyList->AppendTextColumn(wxT("快捷键"), 2);
    pHotKeyList->AppendToggleColumn (wxT("启用"), 3, wxDATAVIEW_CELL_ACTIVATABLE );
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
    if(m_pImpl->hotKeyModel.get()->GetIndexData(Item, uRelationIndex, uHotkeyId))
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
