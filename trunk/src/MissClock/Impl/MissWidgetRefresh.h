#ifndef MISSWIDGETREFRESH_H__
#define MISSWIDGETREFRESH_H__

#include "MissAPI\plugin\MissTimerFuncBase.h"

class MissClockWidgetFunc;

class MissWidgetRefreash : public MissTimerFuncBase
{
public:
    MissWidgetRefreash(MissClockWidgetFunc* pWidget);
    virtual ~MissWidgetRefreash();

    virtual void TimeUp( const tm* tmNow );

private:
    MissClockWidgetFunc* m_pWidget;
};



#endif // MissWidgetRefresh_h__
