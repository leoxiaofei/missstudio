#include "MissWidgetRefresh.h"
#include "MissClockWidgetFunc.h"

MissWidgetRefreash::MissWidgetRefreash( MissWidgetFuncBase* pWidget )
: m_pWidget(pWidget)
{

}

MissWidgetRefreash::~MissWidgetRefreash()
{

}

void MissWidgetRefreash::TimeUp( const tm* tmNow )
{
    m_pWidget->UpdateUI(tmNow);
}

