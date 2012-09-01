#ifndef MISSWIDGETFUNC_H
#define MISSWIDGETFUNC_H

#include "../MissAPI/plugin/MissWidgetFuncBase.h"


class MissWidgetFunc : public MissWidgetFuncBase
{
    public:
        MissWidgetFunc();
        virtual ~MissWidgetFunc();

        virtual void InitWidget(const WidgetParas& para, wxFrame* pWidget);
        virtual void UpdateUI(wxDC &dc, const tm* tmNow);
        virtual wxSize GetSize(){return wxSize(300,300);}

    protected:
    private:
};

#endif // MISSWIDGETFUNC_H
