#include "ImplMissWidget.h"

#include "../Widget/ManualDraw.h"
#include "../Common/WidgetDef.h"
#include "../UI/MissCoreFrame.h"
#include "../BLL/MissWidgetManager.h"
#include "MissAPI/plugin/MissWidgetFuncBase.h"
#include "../UI/MissWidgetMenu.h"

ImplMissWidget::ImplMissWidget(MissWidgetFuncBase* pFunc)
: m_pFunc(pFunc)
{
    m_ptFrame = std::tr1::shared_ptr<wxFrame>(new wxFrame(
        wxAppFrame, wxID_ANY, wxT("MissWidget"), wxDefaultPosition,
        wxSize( 200,200 ), 0 | wxTAB_TRAVERSAL));

    m_ptFrame->Bind( wxEVT_LEFT_DOWN, &ImplMissWidget::OnLeftDown, this);
    m_ptFrame->Bind( wxEVT_RIGHT_UP,  &ImplMissWidget::OnRightUp, this);

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
    ::PostMessage(m_ptFrame->GetHandle(), WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(event.GetX(), event.GetY()));
}

void ImplMissWidget::OnRightUp( wxMouseEvent& event )
{
	std::tr1::shared_ptr<wxMenu> ptMenu = MissWidgetMenu::Instance().GetMenu(this);
    m_ptFrame->PopupMenu(ptMenu.get());
}

void ImplMissWidget::SetData( const DTD::SWidgetPara& data )
{
    m_uRunID = data.m_uRunID;
    m_ptDraw->SetScale(data.m_uZone / 100.0);
    m_ptDraw->SetOpacity(data.m_uOpacity);
    m_ptFrame->Move(data.m_ptPos);
    m_pFunc->InitWidget(data.m_vecPata, this);
}

void ImplMissWidget::GetData( DTD::SWidgetPara& data ) const
{
    data.m_uRunID   = m_uRunID;
    data.m_uZone    = m_ptDraw->GetScale() * 100;
    data.m_uOpacity = m_ptDraw->GetOpacity();
    data.m_ptPos    = m_ptFrame->GetPosition();
    m_pFunc->GetWidgetParas(data.m_vecPata);
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
}

void ImplMissWidget::GetOpacity( int& nOpacity ) const
{
    nOpacity = m_ptDraw->GetOpacity();
}

void ImplMissWidget::SetOpacity( const int& nOpacity )
{
    m_ptDraw->SetOpacity(nOpacity);
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
}

void ImplMissWidget::UpdateUI()
{
    m_pFunc->UpdateUI();
}

