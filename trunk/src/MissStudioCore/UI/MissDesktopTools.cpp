#include "MissDesktopTools.h"
#include <wx/dataview.h>
#include "../Model/MissInstalledModel.h"

class MissDesktopTools::Impl
{
public:
    wxDataViewCtrl* pInstalledList;
    wxObjectDataPtr<MissInstalledModel> ptInstalledModel;
};

MissDesktopTools::MissDesktopTools( wxWindow* parent )
: DesktopToolsBase( parent )
, m_pImpl(new Impl)
{
    InitUi();
}

void MissDesktopTools::InitUi()
{
    wxDataViewCtrl* pInstalledList;
    pInstalledList = new wxDataViewCtrl(panRuning, wxID_ANY);

    m_pImpl->ptInstalledModel = new MissInstalledModel;
    pInstalledList->AssociateModel( m_pImpl->ptInstalledModel.get() );
    pInstalledList->AppendTextColumn(wxT("小工具名称"), 0);
    bSizerRuning->Add(pInstalledList, 1, wxEXPAND | wxALL, 5 );
    bSizerRuning->Layout();
    m_pImpl->pInstalledList = pInstalledList;
}
