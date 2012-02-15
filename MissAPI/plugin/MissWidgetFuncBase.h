#ifndef MISSWIDGETFUNCBASE_H
#define MISSWIDGETFUNCBASE_H

#include <wx/event.h>


class MissWidgetFuncBase : public wxEvtHandler
{
    public:
        virtual ~MissWidgetFuncBase() {}
        virtual void InitUI(wxFrame* pWidget) = 0;

    protected:
        MissWidgetFuncBase() {}
    private:
};

#endif // MISSWIDGETFUNCBASE_H
