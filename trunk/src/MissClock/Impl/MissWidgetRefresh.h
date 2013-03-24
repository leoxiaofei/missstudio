#ifndef MISSWIDGETREFRESH_H__
#define MISSWIDGETREFRESH_H__

#include "MissAPI\plugin\MissTimerFuncBase.h"

class MissWidgetFuncBase;

class MissWidgetRefreash : public MissTimerFuncBase
{
public:
    MissWidgetRefreash(MissWidgetFuncBase* pWidget);
    virtual ~MissWidgetRefreash();

    virtual void TimeUp( const tm* tmNow );

private:
    MissWidgetFuncBase* m_pWidget;
};



#endif // MissWidgetRefresh_h__
