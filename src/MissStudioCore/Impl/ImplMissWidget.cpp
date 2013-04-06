
#include "ImplMissWidget.h"
#include "../Widget/ManualDraw.h"
#include "../Common/WidgetDef.h"
#include "../UI/MissCoreFrame.h"
#include "../BLL/MissWidgetManager.h"
#include "MissAPI/plugin/MissWidgetFuncBase.h"
#include "../UI/MissWidgetMenu.h"
#include "../Common/WidgetEvent.h"
#include <iostream>

using namespace DTD;

ImplMissWidget::ImplMissWidget(MissWidgetFuncBase* pFunc)
: m_pFunc(pFunc)
, m_bPin(false)
{
    m_ptFrame = std::tr1::shared_ptr<wxFrame>(new wxFrame(
        wxAppFrame, wxID_ANY, wxT("MissWidget"), wxDefaultPosition,
        wxSize( 200,200 ), wxFRAME_TOOL_WINDOW));

    m_ptFrame->Bind( wxEVT_LEFT_DOWN, &ImplMissWidget::OnLeftDown, this);
    m_ptFrame->Bind( wxEVT_MOVE,      &ImplMissWidget::OnMoved,    this);
    m_ptFrame->Bind( wxEVT_RIGHT_UP,  &ImplMissWidget::OnRightUp,  this);

    m_ptDraw  = std::tr1::shared_ptr<ManualDraw>(new ManualDraw(m_ptFrame->GetHandle()));
}

ImplMissWidget::~ImplMissWidget()
{

}

void ImplMissWidget::CloseWidget()
{
    MissWidgetManager::Instance().DelRunWidget(m_uRunID);
}

wxFrame* ImplMissWidget::GetFrame() const
{
    return m_ptFrame.get();
}

void ImplMissWidget::SetSize( const wxSize& size )
{
    m_ptDraw->SetSize(size);
}

wxDC* ImplMissWidget::DrawBegin()
{
    return m_ptDraw->DrawBegin();
}

void ImplMissWidget::DrawEnd( wxDC* pDc )
{
    m_ptDraw->DrawEnd(pDc);
}

void ImplMissWidget::OnLeftDown( wxMouseEvent& event )
{
    if (!m_bPin)
    {
        ::PostMessage(m_ptFrame->GetHandle(), WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(event.GetX(), event.GetY()));
    }
}

void ImplMissWidget::OnRightUp( wxMouseEvent& event )
{
	std::tr1::shared_ptr<wxMenu> ptMenu = MissWidgetMenu::Instance().GetMenu(this);
    m_ptFrame->PopupMenu(ptMenu.get());
}

void ImplMissWidget::OnMoved( wxMoveEvent& event )
{
    SendWidgetDataChanged(WCI_POS);
}

void ImplMissWidget::SetData( const SWidgetPara& data )
{
    m_uRunID = data.m_uRunID;
    m_bPin = data.m_bPin;
    m_ptDraw->SetScale(data.m_uZone / 100.0);
    m_ptDraw->SetOpacity(data.m_uOpacity);
    m_ptFrame->Move(data.m_ptPos);
    SetFrameZPos(data.m_nZPos);
    SetFrameShadow(data.m_bShadow);

    m_pFunc->InitWidget(data.m_vecPara, this);
}

void ImplMissWidget::GetData( SWidgetPara& data ) const
{
    data.m_uRunID   = m_uRunID;
    data.m_bPin     = m_bPin;
    data.m_uZone    = m_ptDraw->GetScale() * 100;
    data.m_uOpacity = m_ptDraw->GetOpacity();
    data.m_ptPos    = m_ptFrame->GetPosition();
    GetZPos(data.m_nZPos);
    GetShadow(data.m_bShadow);

    m_pFunc->GetWidgetParas(data.m_vecPara);
}

unsigned int ImplMissWidget::GetRunID() const
{
    return m_uRunID;
}

void ImplMissWidget::GetPos( wxPoint &pt ) const
{
    pt = m_ptFrame->GetPosition();
}

void ImplMissWidget::SetPos( const wxPoint &pt )
{
    m_ptFrame->Move(pt);
}

void ImplMissWidget::GetScale( float& dZoom ) const
{
    dZoom = m_ptDraw->GetScale();
}

void ImplMissWidget::SetScale( const float& dZoom )
{
    m_ptDraw->SetScale(dZoom);
    m_pFunc->UpdateUI();
    SendWidgetDataChanged(WCI_SCALE);
}

void ImplMissWidget::GetOpacity( int& nOpacity ) const
{
    nOpacity = m_ptDraw->GetOpacity();
}

void ImplMissWidget::SetOpacity( const int& nOpacity )
{
    m_ptDraw->SetOpacity(nOpacity);
    m_ptDraw->UpdateLayered();
    SendWidgetDataChanged(WCI_OPACITY);
}

int ImplMissWidget::GetWidgetID() const
{
    return m_nWidgetID;
}

void ImplMissWidget::SetWidgetID( int nID )
{
    m_nWidgetID = nID;
}

void ImplMissWidget::PreClose()
{
    m_pFunc->PreClose();
    SendWidgetDataChanged(WCI_EXIT);
}

void ImplMissWidget::UpdateUI()
{
    m_pFunc->UpdateUI();
}

void ImplMissWidget::GetShadow( bool& bShadow ) const
{
    long exStyle = ::GetWindowLong(m_ptFrame->GetHWND(), GWL_EXSTYLE);
    bShadow = (exStyle & WS_EX_TRANSPARENT) ? true : false;
}

void ImplMissWidget::SetShadow( const bool& bShadow )
{
    SetFrameShadow(bShadow);
    SendWidgetDataChanged(WCI_SHADOW);
}

void ImplMissWidget::GetPin( bool& bPin ) const
{
    bPin = m_bPin;
}

void ImplMissWidget::SetPin( const bool& bPin )
{
    m_bPin = bPin;
    SendWidgetDataChanged(WCI_PIN);
}

void ImplMissWidget::SetFrameShadow( const bool& bShadow )
{
    long exStyle = ::GetWindowLong(m_ptFrame->GetHWND(), GWL_EXSTYLE);
    if (bShadow)
    {
        exStyle |= WS_EX_TRANSPARENT;
    }
    else
    {
        exStyle &= ~WS_EX_TRANSPARENT;
    }
    ::SetWindowLong(m_ptFrame->GetHWND(), GWL_EXSTYLE, exStyle);
}

void ImplMissWidget::GetZPos( int& nPos ) const
{
    if(m_ptFrame->GetWindowStyleFlag() & wxSTAY_ON_TOP)
    {
        nPos = ZP_TOP;
    }
    else if (::GetParent(m_ptFrame->GetHWND()) == ::GetDesktopWindow())
    {
        nPos = ZP_BOTTOM;
    }
    else
    {
        nPos = ZP_NORMAL;
    }
}

void ImplMissWidget::SetZPos( const int& nPos )
{
    SetFrameZPos(nPos);
    SendWidgetDataChanged(WCI_ZPOS);
}

void ImplMissWidget::SetFrameZPos( const int& nZPos )
{
    long lStyle = m_ptFrame->GetWindowStyleFlag();
    if (ZP_TOP == nZPos)
    {
        lStyle |= wxSTAY_ON_TOP;
    }
    else
    {
        lStyle &= ~wxSTAY_ON_TOP;
    }
    m_ptFrame->SetWindowStyleFlag(lStyle);
//     if (ZP_BOTTOM == nZPos)
//     {
//         HWND hWnd = ::GetDesktopWindow();
//         hWnd = ::GetWindow(hWnd, GW_CHILD);
//         ::SetParent(m_ptFrame->GetHWND(), hWnd);
//     }
//     else
//     {
//         HWND hWnd = ::GetParent(m_ptFrame->GetHWND());
//         if (::GetDesktopWindow() == hWnd)
//         {
//             ::SetParent(m_ptFrame->GetHWND(), hWnd);
//         }
//     }
}

void ImplMissWidget::SendWidgetDataChanged( int nFlag )
{
    ///发送一个数据改变消息
    wxCommandEvent send(wxEVT_RUNNINGWIDGET_CHANGED, nFlag);
    m_ptFrame->HandleWindowEvent(send);

    ///为什么不用wxPostEvent? 
    ///因为关闭Widget时，消息发送了会收不到。
    ///wxPostEvent(m_ptFrame.get(), send);
}
