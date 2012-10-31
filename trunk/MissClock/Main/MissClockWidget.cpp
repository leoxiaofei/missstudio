#include "MissClockWidget.h"
#include <wx/dc.h>
#include "../Data/MissXML.h"
#include "../Data/MissSkin.h"
#include "../../MissAPI/plugin/MissPluginBase.h"
#include "../../MissAPI/interface/IMissMain.h"
#include <iostream>

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
    //GetPlugin()->GetPluginPath() + wxT("\\ClockSkin\\Default");
    MissXML::LoadSkin(m_pSkin.get(),wxGetCwd() + wxT("\\")+ Msp->GetMain()->GetPluginPath() + wxT("\\ClockSkin\\Default\\"));
}

void MissClockWidget::InitWidget(const WidgetParas& para, wxFrame* pWidget)
{
    LoadSkin();
}

void MissClockWidget::GetWidgetParas(WidgetParas& para)
{

}

void MissClockWidget::UpdateUI(wxDC& dc, const tm* tmNow)
{
    m_pSkin->DrawSkin(dc, tmNow);
    //dc.SetBrush(*wxBLUE_BRUSH);
    //dc.DrawRectangle(0,0,300,300);
}

wxSize MissClockWidget::GetSize()
{
    return wxSize(m_pSkin->GetBGBitmap().GetWidth(),m_pSkin->GetBGBitmap().GetHeight());
    //return wxSize(300,300);
}
