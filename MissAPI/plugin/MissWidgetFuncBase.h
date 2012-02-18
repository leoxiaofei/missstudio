#ifndef MISSWIDGETFUNCBASE_H
#define MISSWIDGETFUNCBASE_H

#include <wx/event.h>
//#include "../interface/IMissPlugin.h"

class MissWidgetFuncBase : public wxEvtHandler/*, public IMissPlugin*/
{
    public:
        //MissWidgetFuncBase(MissPluginBase* pPlugin):IMissPlugin(pPlugin){};
        virtual ~MissWidgetFuncBase() {}
        virtual void InitWidget(wxFrame* pWidget) = 0;
        virtual void UpdateUI(wxDC &dc, const tm* tmNow){};

    protected:

    private:
};

#endif // MISSWIDGETFUNCBASE_H
