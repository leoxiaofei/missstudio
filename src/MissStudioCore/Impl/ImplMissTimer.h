#ifndef IMPLMISSTIMER_H__
#define IMPLMISSTIMER_H__

#include "MissAPI\interface\IMissTimer.h"

class MissPluginBase;

class ImplMissTimer : public IMissTimer
{
public:
    ImplMissTimer(MissPluginBase* pPlugMain);
    ~ImplMissTimer();

    virtual void RegSecTimer( MissTimerFuncBase* pPlugin );
    virtual void RegMinTimer( MissTimerFuncBase* pPlugin );
    virtual void UnRegSecTimer( MissTimerFuncBase* pPlugin );
    virtual void UnRegMinTimer( MissTimerFuncBase* pPlugin );

private:
    MissPluginBase* m_pPlugMain;
};


#endif // ImplMissTimer_h__
