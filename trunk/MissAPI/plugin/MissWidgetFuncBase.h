#ifndef MISSWIDGETFUNCBASE_H
#define MISSWIDGETFUNCBASE_H

#include <wx/event.h>
#include <vector>

typedef std::vector<std::pair<wxString, wxString> > WidgetParas;

class MissWidgetFuncBase : public wxEvtHandler
{
    public:
        MissWidgetFuncBase(){};
        virtual ~MissWidgetFuncBase() {}
        virtual void InitWidget(const WidgetParas& para, wxFrame* pWidget) = 0;
        virtual void UpdateUI(wxDC &dc, const tm* tmNow) = 0;
        virtual wxSize GetSize() = 0;
    protected:

    private:
};

#endif // MISSWIDGETFUNCBASE_H