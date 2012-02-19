#include "MissWidgetFrame.h"

#include "../BLL/MissWidgetManager.h"
#include "../../MissAPI/plugin/MissWidgetFactoryBase.h"
#include "../../MissAPI/plugin/MissPluginBase.h"

class MissWidgetFrame::MissWidgetFrameImpl
{
public:
    MissWidgetManager* m_pManager;
};

MissWidgetFrame::MissWidgetFrame( wxWindow* parent, MissWidgetManager* pManager)
:
MissWidgetFrameBase( parent ),
m_pImpl(new MissWidgetFrameImpl)
{
    m_pImpl->m_pManager = pManager;

    InitUI();
    Centre( wxBOTH );
}

void MissWidgetFrame::InitUI()
{
    m_listWidgets->InsertColumn(0,_T("ID"),wxLIST_FORMAT_LEFT,0);
    m_listWidgets->InsertColumn(1,_T("插件名称"),wxLIST_FORMAT_LEFT,100);
    m_listWidgets->InsertColumn(2,_T("小工具名称"),wxLIST_FORMAT_LEFT,100);

    m_listRunWidgets->InsertColumn(0,_T("ID"),wxLIST_FORMAT_LEFT,0);
    m_listRunWidgets->InsertColumn(1,_T("小工具名称"),wxLIST_FORMAT_LEFT,100);
    m_listRunWidgets->InsertColumn(2,_T("坐标"),wxLIST_FORMAT_LEFT,50);
    m_listRunWidgets->InsertColumn(3,_T("透明度"),wxLIST_FORMAT_LEFT,50);
    m_listRunWidgets->InsertColumn(4,_T("缩放"),wxLIST_FORMAT_LEFT,50);

    int nItemIndex = 0;
    int nPluginIndex = 0;
    int nFuncIndex = -1;
    std::vector<shared_ptr<SWidget> >& datas = m_pImpl->m_pManager->GetWidgetData();
    for(std::vector<shared_ptr<SWidget> >::iterator itor = datas.begin();
        itor != datas.end(); ++itor)
    {
        nFuncIndex = -2;
        m_listWidgets->InsertItem(nItemIndex, wxEmptyString);
        m_listWidgets->SetItem(nItemIndex,0,wxString::Format(wxT("%d:%d"),nPluginIndex,++nFuncIndex));
        m_listWidgets->SetItem(nItemIndex,1,(*itor)->pFactory->GetPlugin()->GetPlugInfo().strPluginName);
        ++nItemIndex;
        for(std::vector<wxString>::iterator hkitor = (*itor)->vecWidgetName.begin();
            hkitor != (*itor)->vecWidgetName.end(); ++hkitor)
        {
            m_listWidgets->InsertItem(nItemIndex, wxEmptyString);
            //m_listHotKey->SetItem(nItemIndex,0,m_pImpl->m_pData->);
            //m_listHotKey->SetItem(nItemIndex,1,wxString::Format(wxT("%d"),nItemIndex+1));

            m_listWidgets->SetItem(nItemIndex,0,wxString::Format(wxT("%d:%d"),nPluginIndex,++nFuncIndex));
            m_listWidgets->SetItem(nItemIndex,1,wxT("    ┖┄┄┄┄"));
            m_listWidgets->SetItem(nItemIndex,2,*hkitor);
            ++nItemIndex;
        }
        ++nPluginIndex;
    }
}

void MissWidgetFrame::OnWidgetsListItemActivated( wxListEvent& event )
{
// TODO: Implement OnWidgetsListItemActivated
    int nItemIndex = event.GetIndex();
    wxString strID = m_listWidgets->GetItemText(nItemIndex);
    long nFunc = -1;
    strID.AfterLast(':').ToLong(&nFunc);
//    std::wcout << strID.c_str() << " " << strID.AfterLast(':').c_str() <<" " << nFunc << std::endl;

    if(nFunc > -1)
    {
        long nPlugin = -1;
        strID.BeforeFirst(':').ToLong(&nPlugin);

        m_pImpl->m_pManager->CreateWidget(nPlugin,nFunc);

    }
}

void MissWidgetFrame::OnRunWidgetsListItemActivated( wxListEvent& event )
{
// TODO: Implement OnRunWidgetsListItemActivated
}

void MissWidgetFrame::OnRunWidgetsListItemRightClick( wxListEvent& event )
{
// TODO: Implement OnRunWidgetsListItemRightClick
}
