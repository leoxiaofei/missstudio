#include "MissRunningModel.h"
#include "..\BLL\MissWidgetManager.h"
#include "..\Impl\ImplMissWidget.h"
#include "MissAPI\plugin\MissWidgetFactoryBase.h"


MissRunningModel::MissRunningModel()
: m_vecRunning(MissWidgetManager::Instance().GetRunningWidget())
{
    ///名称 坐标 缩放 透明度 固定位置 鼠标穿透 置顶方式
}

MissRunningModel::~MissRunningModel()
{

}

void MissRunningModel::GetValueByRow( wxVariant &variant, unsigned row, unsigned col ) const
{
    switch (col)
    {
    case 0:
        {
            MissWidgetManager& manager = MissWidgetManager::Instance();
            MissWidgetFactoryBase* pBase;
            if(manager.GetFactoryByRunId(m_vecRunning[row]->GetRunID(), pBase))
            {
                wxString strName;
                pBase->GetWidgetName(m_vecRunning[row]->GetWidgetID(), strName);
                variant = strName;
            }
        }
        break;
    case 1:
        {
            wxPoint pt;
            m_vecRunning[row]->GetPos(pt);
            variant = wxString::Format("%d:%d", pt.x, pt.y);
        }
        break;
    case 2:
        {
            float fZoom;
            m_vecRunning[row]->GetScale(fZoom);
            variant = wxString::Format("%f", fZoom);
        }
        break;
    case 3:
        {
            int nOpacity;
            m_vecRunning[row]->GetOpacity(nOpacity);
            variant = wxString::Format("%d", nOpacity);
        }
        break;
    default:
        break;
    }
    
}

bool MissRunningModel::SetValueByRow( const wxVariant &variant, unsigned row, unsigned col )
{
    return false;
}

unsigned int MissRunningModel::GetColumnCount() const
{
    return 4;
}

wxString MissRunningModel::GetColumnType( unsigned int col ) const
{
    return wxT("string");
}

bool MissRunningModel::GetDataByItem( const wxDataViewItem &item, std::tr1::shared_ptr<ImplMissWidget>& ptRunning ) const
{
    bool bRet(false);
    if (item.IsOk())
    {
        ptRunning = m_vecRunning[GetRow(item)];
        bRet = true;
    }
    return bRet;
}

