#ifndef IMISSWIDGET_H
#define IMISSWIDGET_H

#include "../MissApiDef.h"
#include <wx/gdicmn.h>

class wxFrame;
class wxDC;


INTERFACE_BEGIN(IMissWidget)

    IDEF( void CloseWidget() )
    IDEF( wxFrame* GetFrame() const )
    IDEF( void  SetSize(const wxSize& size) )
    IDEF( wxDC* DrawBegin() )   
    IDEF( void  DrawEnd(wxDC* pDc) )

INTERFACE_END

#endif // IMISSWIDGET_H
