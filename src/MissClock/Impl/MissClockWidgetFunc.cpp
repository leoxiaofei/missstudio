#include "MissClockWidgetFunc.h"
#include "..\BLL\MissSkin.h"
#include "MissAPI\plugin\MissWidgetFuncBase.h"
#include "MissAPI\interface\IMissWidget.h"


MissClockWidgetFunc::MissClockWidgetFunc(const std::tr1::shared_ptr<MissSkin>& pSkin)
: m_pSkin( pSkin )
{
    //GetWidget()->SetSize(m_pSkin->GetBGBitmap().GetSize());
}

MissClockWidgetFunc::~MissClockWidgetFunc()
{
}

void MissClockWidgetFunc::SetWidgetPara( const CustomPara& para )
{
    GetWidget()->SetSize(m_pSkin->GetBGBitmap().GetSize());
}

void MissClockWidgetFunc::GetWidgetParas( CustomPara& para )
{
}

void MissClockWidgetFunc::UpdateUI(const tm* tmNow)
{
    wxDC* dc = GetWidget()->DrawBegin();
    m_pSkin->DrawSkin(*dc, tmNow);
    GetWidget()->DrawEnd(dc);
}

void MissClockWidgetFunc::PreClose()
{
}
