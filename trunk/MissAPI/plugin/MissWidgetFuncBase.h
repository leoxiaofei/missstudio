#ifndef MISSWIDGETFUNCBASE_H
#define MISSWIDGETFUNCBASE_H

#include <wx/event.h>
#include "../interface/IMissPlugin.h"

class MissWidgetFuncBase : public wxEvtHandler, public IMissPlugin
{
    public:
        MissWidgetFuncBase(MissPluginBase* pPlugin):IMissPlugin(pPlugin){};
        virtual ~MissWidgetFuncBase() {}
        virtual void InitWidget(wxFrame* pWidget){};
        virtual void UpdateUI(wxDC &dc, const tm* tmNow) = 0;
        virtual wxSize GetSize() = 0;
    protected:

    private:
};

#endif // MISSWIDGETFUNCBASE_H
