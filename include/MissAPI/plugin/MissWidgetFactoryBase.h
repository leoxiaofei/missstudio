#ifndef MISSCREATEWIDGETBASE_H
#define MISSCREATEWIDGETBASE_H

#include <wx\string.h>

class MissWidgetFuncBase;
class MissTimerFuncBase;
typedef MissTimerFuncBase MissWidgetUpdateFunc;


class MissWidgetFactoryBase
{
    public:
        virtual ~MissWidgetFactoryBase() {}
        virtual MissWidgetFuncBase* CreateWidgetFunc(int nWidgetId) = 0;
        virtual void CreateSuccessed(MissWidgetFuncBase* pWidgetFunc) = 0;
        virtual void GetWidgetName(int nWidgetId, wxString& strWidgetName) = 0;

    protected:
    private:
};

#endif // MISSCREATEWIDGETBASE_H
