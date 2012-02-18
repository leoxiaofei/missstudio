#ifndef MISSWIDGETFUNC_H
#define MISSWIDGETFUNC_H

#include "../MissAPI/plugin/MissWidgetFuncBase.h"


class MissWidgetFunc : public MissWidgetFuncBase
{
    public:
        MissWidgetFunc();
        virtual ~MissWidgetFunc();

        virtual void InitWidget(wxFrame* pWidget);
        virtual void UpdateUI(wxDC &dc, const tm* tmNow);
    protected:
    private:
};

#endif // MISSWIDGETFUNC_H
