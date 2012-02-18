#include "MissClockWidget.h"
#include <wx/dc.h>

MissClockWidget::MissClockWidget():
    MissWidgetFuncBase()
{
    //ctor
}

MissClockWidget::~MissClockWidget()
{
    //dtor
}

void MissClockWidget::InitWidget(wxFrame* pWidget)
{
    //wxMemoryDC memdc(m_bpUI);
    //memdc.SetBrush(*wxBLUE_BRUSH);
    //memdc.DrawRectangle(0,0,300,300);
    //memdc.SetUserScale(m_dZoom,m_dZoom);
    /*
    m_pSkin->DrawSkin(memdc, tmNow);
    */
}

void MissClockWidget::UpdateUI(wxDC& dc, const tm* tmNow)
{
    dc.SetBrush(*wxBLUE_BRUSH);
    dc.DrawRectangle(0,0,300,300);
}
