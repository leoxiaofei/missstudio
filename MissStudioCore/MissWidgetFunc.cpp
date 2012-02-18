#include "MissWidgetFunc.h"
#include <winuser.h>

MissWidgetFunc::MissWidgetFunc():
    MissWidgetFuncBase()
{
    //ctor
}

MissWidgetFunc::~MissWidgetFunc()
{
    //dtor
}

void MissWidgetFunc::InitWidget(wxFrame* pWidget)
{
    //wxMemoryDC memdc(m_bpUI);
    //memdc.SetBrush(*wxBLUE_BRUSH);
    //memdc.DrawRectangle(0,0,300,300);
    //memdc.SetUserScale(m_dZoom,m_dZoom);
    /*
    m_pSkin->DrawSkin(memdc, tmNow);
    */
}

void MissWidgetFunc::UpdateUI(wxDC& dc, const tm* tmNow)
{
    dc.SetBrush(*wxBLUE_BRUSH);
    dc.DrawRectangle(0,0,300,300);
}
