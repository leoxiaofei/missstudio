#include "MissWidgetFactory.h"
#include "MissClockWidgetFunc.h"
//#include "MissAPI\interface\IMissWidgetMgr.h"
#include "MissAPI\interface\IMissMain.h"
#include "MissAPI\interface\IMissTimer.h"
#include "MissWidgetRefresh.h"
#include "..\BLL\MissWidgetFuncMgr.h"
#include "..\DAL\MissXML.h"
#include "..\BLL\MissSkin.h"

using std::tr1::shared_ptr;

MissWidgetFactory::MissWidgetFactory( const std::tr1::shared_ptr<IMissMain>& pMissMain )
: m_pMissMain(pMissMain)
{

}

MissWidgetFuncBase* MissWidgetFactory::CreateWidgetFunc( int nWidgetId )
{
    MissWidgetFuncBase* pRet(NULL);
    switch (nWidgetId)
    {
    case WT_CLOCK:
        {
            std::tr1::shared_ptr<MissSkin> pSkin(new MissSkin);
            wxString strPath = m_pMissMain->GetPluginPath();
            MissXML::LoadSkin(pSkin.get(), strPath + wxT("ClockSkin/Default/"));
            pRet = new MissClockWidgetFunc(pSkin);
        }
        break;
    default:
        break;
    }
    return pRet;
}

void MissWidgetFactory::GetWidgetName( int nWidgetId, wxString& strWidgetName )
{
    switch (nWidgetId)
    {
    case WT_CLOCK:
        strWidgetName = wxT("√‘ ß ±÷”");
        break;
    default:
        break;
    }
}

void MissWidgetFactory::CreateSuccessed( MissWidgetFuncBase* pWidgetFunc )
{
    if (shared_ptr<IMissTimer> pt = m_pMissMain->QueryIF<IMissTimer>(IF_TIMER))
    {
        MissWidgetRefreash* pRefreash = new MissWidgetRefreash(pWidgetFunc);
        pt->RegSecTimer(pRefreash);
        MissWidgetFuncMgr::Instance().SaveFunc(shared_ptr<MissWidgetFuncBase>(pWidgetFunc),
            shared_ptr<MissTimerFuncBase>(pRefreash));
    }
}

