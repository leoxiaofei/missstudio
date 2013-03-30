#include "MissWidgetFactory.h"
#include "MissClockWidgetFunc.h"
#include "MissAPI\interface\IMissMain.h"
#include "..\BLL\MissWidgetFuncMgr.h"
#include "..\DAL\MissXML.h"
#include "..\BLL\MissSkin.h"
#include "..\Common\MissGlobal.h"

using std::tr1::shared_ptr;

MissWidgetFactory::MissWidgetFactory()
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
            wxString strPath = MissGlobal::IMain->GetPluginPath();
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
    MissWidgetFuncMgr::Instance().AddClockWidget(static_cast<MissClockWidgetFunc*>(pWidgetFunc));

}

