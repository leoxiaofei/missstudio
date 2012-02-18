#ifndef MISSWIDGETFUNC_H
#define MISSWIDGETFUNC_H

#include "../MissAPI/plugin/MissWidgetFuncBase.h"


class MissClockWidget : public MissWidgetFuncBase
{
    public:
        MissClockWidget();
        virtual ~MissClockWidget();

        virtual void InitWidget(wxFrame* pWidget);
        virtual void UpdateUI(wxDC &dc, const tm* tmNow);
        virtual wxSize GetSize(){return wxSize(300,300);}

    protected:
    private:
};

#endif // MISSWIDGETFUNC_H
