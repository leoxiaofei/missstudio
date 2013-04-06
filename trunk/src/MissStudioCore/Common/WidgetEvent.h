#ifndef WIDGETEVENT_H__
#define WIDGETEVENT_H__

#include <wx/event.h>

wxDECLARE_EVENT(wxEVT_RUNNINGWIDGET_CHANGED, wxEvent);

namespace DTD
{
    enum WidgetChangedId
    {
        WCI_ALL,
        WCI_POS,
        WCI_ZPOS,
        WCI_SHADOW,
        WCI_PIN,
        WCI_OPACITY,
        WCI_SCALE,
        WCI_EXIT,
    };
};

#endif // WIDGETEVENT_H__
