#include "MissClockWidget.h"
#include <wx/dc.h>
#include "../Data/MissXML.h"
#include "../Data/MissSkin.h"

MissClockWidget::MissClockWidget():
    MissWidgetFuncBase(),
    m_pSkin(new MissSkin)
{
    //ctor
}

MissClockWidget::~MissClockWidget()
{
    //dtor
}

void MissClockWidget::LoadSkin()
{
    MissXML::LoadSkin(m_pSkin.get(), wxT(""));
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
    m_pSkin->DrawSkin(dc, tmNow);
    //dc.SetBrush(*wxBLUE_BRUSH);
    //dc.DrawRectangle(0,0,300,300);
}

wxSize MissClockWidget::GetSize()
{

}
