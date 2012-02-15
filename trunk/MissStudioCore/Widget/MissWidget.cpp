#include "MissWidget.h"

#include "../../MissAPI/plugin/MissWidgetFuncBase.h"

MissWidget::MissWidget(MissWidgetFuncBase * pFunc,
                       wxWindow* parent,
                        wxWindowID id,
                        const wxString& title,
                        const wxPoint& pos,
                        const wxSize& size,
                        long style):
wxFrame(parent,id,title,pos,size,style),
m_pFunc(pFunc)
{
    m_hWnd = static_cast<HWND>(GetHandle());


    long exStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
    exStyle |= WS_EX_LAYERED;
    ::SetWindowLong(m_hWnd, GWL_EXSTYLE, exStyle);

    m_pFunc->InitUI(this);

    this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( MissWidget::OnLeftDown ) );
	this->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( MissWidget::OnRightUp ) );
}

void MissWidget::OnLeftDown(wxMouseEvent& event)
{
    ::PostMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(event.GetX(), event.GetY()));
}

void MissWidget::OnRightUp(wxMouseEvent& event)
{
    /*
    Raise();
    if(m_pOptionDlg == NULL)
        PopupMenu(m_pMainMenu);
    */
}
