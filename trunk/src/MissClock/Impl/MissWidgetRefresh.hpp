#ifndef MISSWIDGETREFRESH_H__
#define MISSWIDGETREFRESH_H__

#include "MissAPI\plugin\MissTimerFuncBase.h"

template <class T>
class MissWidgetRefreash : public MissTimerFuncBase
{
public:
    MissWidgetRefreash(T* pWidget):m_pWidget(pWidget){}

    virtual void TimeUp( const tm* tmNow )
    {
        m_pWidget->UpdateUI(tmNow);
    }

private:
    T* m_pWidget;
};



#endif // MissWidgetRefresh_h__
