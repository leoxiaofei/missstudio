#include "MissWidgetFrame.h"

#include "../BLL/MissWidgetManager.h"
#include "../BLL/MissPluginManager.h"
#include "../Widget/MissWidget.h"
#include "../Model/MissPluginTreeListData.h"
#include "../../MissAPI/plugin/MissWidgetFactoryBase.h"
#include "../../MissAPI/plugin/MissPluginBase.h"

class MissWidgetFrame::MissWidgetFrameImpl
{
public:

};

MissWidgetFrame::MissWidgetFrame( wxWindow* parent)
    : MissWidgetFrameBase( parent )
    , m_pImpl(new MissWidgetFrameImpl)
{
    InitUI();
    CentreOnScreen();
}

void MissWidgetFrame::InitUI()
{
    /*
    m_listWidgets->InsertColumn(0,_T("ID"),wxLIST_FORMAT_LEFT,0);
    m_listWidgets->InsertColumn(1,_T("插件名称"),wxLIST_FORMAT_LEFT,100);
    m_listWidgets->InsertColumn(2,_T("小工具名称"),wxLIST_FORMAT_LEFT,100);

    m_listRunWidgets->InsertColumn(0,_T("ID"),wxLIST_FORMAT_LEFT,0);
    m_listRunWidgets->InsertColumn(1,_T("小工具名称"),wxLIST_FORMAT_LEFT,100);
    m_listRunWidgets->InsertColumn(2,_T("坐标"),wxLIST_FORMAT_LEFT,50);
    m_listRunWidgets->InsertColumn(3,_T("透明度"),wxLIST_FORMAT_LEFT,50);
    m_listRunWidgets->InsertColumn(4,_T("缩放"),wxLIST_FORMAT_LEFT,50);
    */

    wxTreeItemId idRoot = m_listWidgets->AddRoot(_T("Miss Studio"));
    wxTreeItemId idParent, idItem;

    int nPluginIndex = 0;
    int nFuncIndex   = 0;
    std::vector<shared_ptr<SPluginWidgetData> >& datas =
        MissPluginManager::Instance().GetWidgetManager().GetWidgetData();
    for(std::vector<shared_ptr<SPluginWidgetData> >::iterator itor = datas.begin();
            itor != datas.end(); ++itor)
    {
        nFuncIndex = -1;
        idParent = m_listWidgets->AppendItem(idRoot, wxEmptyString);
        m_listWidgets->SetItemText(idParent, 0,
                                   (*itor)->pFactory->GetPlugin()->GetPlugInfo().strPluginName);

        for(std::vector<wxString>::iterator wnitor = (*itor)->vecWidgetName.begin();
                wnitor != (*itor)->vecWidgetName.end(); ++wnitor)
        {
            idItem = m_listWidgets->AppendItem(idParent, wxEmptyString, -1, -1,
                                               new MissPluginTreeListData(nPluginIndex, ++nFuncIndex));
            m_listWidgets->SetItemText(idItem, 0, *wnitor);
        }
        ++nPluginIndex;
    }
}

void MissWidgetFrame::OnWidgetsListTreeItemActivated(wxTreeEvent& event)
{
    wxTreeItemId idItemIndex = event.GetItem();
    MissPluginTreeListData* pData = static_cast<MissPluginTreeListData*>
                                    (m_listWidgets->GetItemData(idItemIndex));
    if(pData != NULL)
    {
        unsigned int nPlugin = pData->GetPluginIndex();
        unsigned int nWidget = pData->GetFuncIndex();
        SWidgetPara para;
        ///TODO:读取参数

        ///
        MissPluginManager::Instance().GetWidgetManager().CreateWidget(nPlugin, nWidget, para);
    }
}

/*
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
        //SWidgetData data;
        //m_pImpl->m_pManager->CreateWidget(nPlugin,nFunc,data);
    }
}
*/
void MissWidgetFrame::OnRunWidgetsListItemActivated( wxListEvent& event )
{
// TODO: Implement OnRunWidgetsListItemActivated
}

void MissWidgetFrame::OnRunWidgetsListItemRightClick( wxListEvent& event )
{
// TODO: Implement OnRunWidgetsListItemRightClick
}
