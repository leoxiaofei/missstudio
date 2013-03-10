#include "MissDesktopTools.h"
#include <wx/dataview.h>

class MissDesktopTools::Impl
{
public:
    wxDataViewCtrl* pInstalledList;

};

MissDesktopTools::MissDesktopTools( wxWindow* parent )
: DesktopToolsBase( parent )
, m_pImpl(new Impl)
{

}

void MissDesktopTools::InitUi()
{
    wxDataViewCtrl* pInstalledList;
    pInstalledList = new wxDataViewCtrl(panHotKey, wxID_ANY);

    m_pImpl->hotKeyModel = new MissHotKeyModel;
    pInstalledList->AssociateModel( m_pImpl->hotKeyModel.get() );
    pInstalledList->AppendTextColumn(wxT("插件名称"), 0);
    pInstalledList->AppendTextColumn(wxT("功能描述"), 1);
    pInstalledList->AppendTextColumn(wxT("快捷键"), 2);
    pInstalledList->AppendToggleColumn (wxT("启用"), 3, wxDATAVIEW_CELL_ACTIVATABLE );
    sizerHotKey->Add(pInstalledList, 1, wxEXPAND | wxALL, 5 );
    sizerHotKey->Layout();
    m_pImpl->pInstalledList = hotKeyModel;
}
