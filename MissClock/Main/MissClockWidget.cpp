#include "MissClockWidget.h"
#include <wx/dc.h>
#include "../Data/MissXML.h"
#include "../Data/MissSkin.h"
#include "../../MissAPI/plugin/MissPluginBase.h"
#include <iostream>

MissClockWidget::MissClockWidget(MissPluginBase* pPlugin):
    MissWidgetFuncBase(pPlugin),
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
    MissXML::LoadSkin(m_pSkin.get(),wxGetCwd() + wxT("\\")+ GetPlugin()->GetPluginPath() + wxT("\\ClockSkin\\Default\\"));
}

void MissClockWidget::InitWidget(wxFrame* pWidget)
{
    //wxMemoryDC memdc(m_bpUI);
    //memdc.SetBrush(*wxBLUE_BRUSH);
    //memdc.DrawRectangle(0,0,300,300);
    //memdc.SetUserScale(m_dZoom,m_dZoom);
    //m_pSkin->DrawSkin(memdc, tmNow);
    LoadSkin();
    std::wcout<<wxGetCwd().c_str()<<std::endl;
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
