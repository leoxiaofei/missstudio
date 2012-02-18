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

    m_pFunc->InitWidget(this);


    m_Blend.BlendOp = AC_SRC_OVER;      ///指定源混合操作。目前，唯一的源和目标混合操作被定义为 AC_SRC_OVER。
    m_Blend.BlendFlags = 0;             ///必须为 0
    m_Blend.AlphaFormat = AC_SRC_ALPHA; ///该成员控制源和目标位图被解释的方式。
    m_Blend.SourceConstantAlpha = 255;

    this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( MissWidget::OnLeftDown ) );
	this->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( MissWidget::OnRightUp ) );
}

void MissWidget::TimeUp(const tm* tmNow, MissTimerType eType)
{
    static HDC s_hdcScreen = ::GetDC(m_hWnd);
    static POINT s_ptSrc = {0, 0};
    SIZE m_SizeWindow = {300, 300};

    wxBitmap m_bpUI(300,300,32);

    BITMAP bm;
    ::GetObject(static_cast<HBITMAP>(m_bpUI.GetHBITMAP()), sizeof(bm), &bm);
    int m_nPixCount = bm.bmWidth * bm.bmHeight;
    unsigned int* m_pBitmap = static_cast<unsigned int*>(bm.bmBits);

    static int nPixCount;
    static unsigned int* pBitmap;

    nPixCount = m_nPixCount;
    pBitmap = m_pBitmap;

    while (--nPixCount)
    {
        *pBitmap = 0x01000000;
        ++pBitmap;
    }

    wxMemoryDC memdc(m_bpUI);
    m_pFunc->UpdateUI(memdc,tmNow);

    nPixCount = m_nPixCount;
    pBitmap = m_pBitmap;
    while (--nPixCount)
    {
        *pBitmap -= 0x01000000;
        ++pBitmap;
    }
    ::UpdateLayeredWindow(m_hWnd, s_hdcScreen, NULL, &m_SizeWindow, static_cast<HDC>(memdc.GetHDC()),
        &s_ptSrc, 0, &m_Blend, ULW_ALPHA);
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
