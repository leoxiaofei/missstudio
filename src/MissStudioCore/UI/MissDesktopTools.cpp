#include "MissDesktopTools.h"
#include <wx/dataview.h>
#include "../Model/MissInstalledModel.h"
#include "../Common/AutoColumnWidth.h"
#include "../Model/MissRunningModel.h"
#include "../BLL/MissWidgetManager.h"
#include "../Common/WidgetDef.h"

class MissDesktopTools::Impl
{
public:
    wxDataViewCtrl*                     pInstalledList;
    wxObjectDataPtr<MissInstalledModel> ptInstalledModel;
    AutoColumnWidth                     acwInstalledList;

    wxDataViewCtrl*                     pRunningList;
    wxObjectDataPtr<MissRunningModel>   ptRunningModel;
    AutoColumnWidth                     acwRunningList;

};

MissDesktopTools::MissDesktopTools( wxWindow* parent )
: DesktopToolsBase( parent )
, m_pImpl(new Impl)
{
    InitUi();
    BindEvent();
}

MissDesktopTools::~MissDesktopTools()
{

}

void MissDesktopTools::InitUi()
{
    wxDataViewCtrl* pInstalledList;
    pInstalledList = new wxDataViewCtrl(panInstalled, wxID_ANY);
    m_pImpl->acwInstalledList.SetViewCtrl(pInstalledList);
    m_pImpl->acwInstalledList.SetAutoColumn(0);
    m_pImpl->acwInstalledList.SetMinWidth(80);

    m_pImpl->ptInstalledModel = new MissInstalledModel;
    pInstalledList->AssociateModel( m_pImpl->ptInstalledModel.get() );
    m_pImpl->acwInstalledList << pInstalledList->AppendTextColumn(wxT("小工具名称"), 0);
    bSizerInstalled->Add(pInstalledList, 1, wxEXPAND | wxALL, 5 );
    bSizerInstalled->Layout();
    m_pImpl->pInstalledList = pInstalledList;


    wxDataViewCtrl* pRunningList;
    pRunningList = new wxDataViewCtrl(panRuning, wxID_ANY);
    m_pImpl->acwRunningList.SetViewCtrl(pRunningList);
    m_pImpl->acwRunningList.SetAutoColumn(0);
    m_pImpl->acwRunningList.SetMinWidth(80);

    m_pImpl->ptRunningModel = new MissRunningModel();
    pRunningList->AssociateModel( m_pImpl->ptRunningModel.get() );
    m_pImpl->acwRunningList << pRunningList->AppendTextColumn(wxT("小工具名称"), 0);
    m_pImpl->acwRunningList << pRunningList->AppendTextColumn(wxT("坐标"), 1);
    m_pImpl->acwRunningList << pRunningList->AppendTextColumn(wxT("缩放"), 2);
    m_pImpl->acwRunningList << pRunningList->AppendTextColumn(wxT("透明度"), 3);
    bSizerRuning->Add(pRunningList, 1, wxEXPAND | wxALL, 5 );
    bSizerRuning->Layout();
    m_pImpl->pRunningList = pRunningList;

    SetSize(650, 450);
    m_pImpl->ptRunningModel->Reset(MissWidgetManager::Instance().GetRunningWidget().size());
}

void MissDesktopTools::BindEvent()
{
    m_pImpl->pInstalledList->Bind(wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, &MissDesktopTools::DClickInstalledItem, this);
}

void MissDesktopTools::DClickInstalledItem( wxDataViewEvent& event )
{
    wxDataViewItem item = event.GetItem();

    MissWidgetFactoryBase* pBase;
    int nWigetId;
    if(m_pImpl->ptInstalledModel->GetDataByItem(item, pBase, nWigetId))
    {
        MissWidgetManager::Instance().CreateWidget(pBase, nWigetId);
        m_pImpl->ptRunningModel->Reset(MissWidgetManager::Instance().GetRunningWidget().size());
    }

}


