#ifndef MISSWIDGETFUNC_H
#define MISSWIDGETFUNC_H

#include "../MissAPI/plugin/MissWidgetFuncBase.h"


class MissWidgetFunc : public MissWidgetFuncBase
{
    public:
        MissWidgetFunc();
        virtual ~MissWidgetFunc();

        virtual void InitUI(wxFrame* pWidget);

    protected:
    private:
};

#endif // MISSWIDGETFUNC_H
