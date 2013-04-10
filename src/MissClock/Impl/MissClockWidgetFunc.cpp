#include "MissClockWidgetFunc.h"
#include "..\BLL\MissSkin.h"
#include "MissAPI\plugin\MissWidgetFuncBase.h"
#include "MissAPI\interface\IMissWidget.h"
#include "MissAPI\interface\IMissWidget.h"
#include "..\BLL\MissWidgetFuncMgr.h"


MissClockWidgetFunc::MissClockWidgetFunc(const std::tr1::shared_ptr<MissSkin>& pSkin)
: m_pSkin( pSkin )
{
}

MissClockWidgetFunc::~MissClockWidgetFunc()
{
}

void MissClockWidgetFunc::SetWidgetPara( const CustomPara& para )
{
    GetWidget()->SetSize(m_pSkin->GetBGBitmap().GetSize());
}

void MissClockWidgetFunc::GetWidgetPara( CustomPara& para ) const
{
}

void MissClockWidgetFunc::UpdateUI(const tm* tmNow)
{
    wxDC* dc = GetWidget()->DrawBegin();
    m_pSkin->DrawSkin(*dc, tmNow);
    GetWidget()->DrawEnd(dc);
}

void MissClockWidgetFunc::UpdateUI()
{
    time_t ttNow = time(NULL);
    UpdateUI(localtime(&ttNow));
}

void MissClockWidgetFunc::PreClose()
{
    MissWidgetFuncMgr::Instance().RemoveWidget(GetRunID());
}

unsigned int MissClockWidgetFunc::GetRunID() const
{
    return GetWidget()->GetRunID();
}
