#include "MissWidget.h"
#include "../../MissAPI/plugin/MissWidgetFuncBase.h"
#include "../DAL/MissDataTypeDef.h"

#include <iostream>

MissWidget::MissWidget(MissWidgetFuncBase * pFunc,
                       wxWindow* parent,
                       wxWindowID id,
                       const wxString& title,
                       const wxPoint& pos,
                       const wxSize& size,
                       long style)
: wxFrame(parent, id, title, pos, size, style)
, m_pFunc(pFunc)
, m_pBitmap(NULL)
, m_nPixCount(0)
, m_nWidgetID(-1)
{
    m_hWnd = static_cast<HWND>(GetHandle());

    long exStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
    exStyle |= WS_EX_LAYERED;
    ::SetWindowLong(m_hWnd, GWL_EXSTYLE, exStyle);

    m_Blend.BlendOp = AC_SRC_OVER;      ///指定源混合操作。目前，唯一的源和目标混合操作被定义为 AC_SRC_OVER。
    m_Blend.BlendFlags = 0;             ///必须为 0
    m_Blend.AlphaFormat = AC_SRC_ALPHA; ///该成员控制源和目标位图被解释的方式。

    this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( MissWidget::OnLeftDown ) );
    this->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( MissWidget::OnRightUp ) );

}

void MissWidget::InitData(const DTD::SWidgetPara& data)
{
    m_pFunc->InitWidget(data.m_vecPata, this);
    SetScale(data.m_nZone / 100.0);
    SetOpacity(data.m_nOpacity);
    Move(data.m_ptPos);
}

void MissWidget::TimeUp(const tm* tmNow, MissTimerType eType)
{
    static HDC s_hdcScreen = ::GetDC(m_hWnd);
    static POINT s_ptSrc = {0, 0};

    static int nPixCount;
    static unsigned int* pBitmap;

    nPixCount = m_nPixCount + 1;
    pBitmap = m_pBitmap;

    while (--nPixCount)
    {
        *pBitmap = 0x01000000;
        ++pBitmap;
    }

    wxMemoryDC memdc(m_bpUI);
    //memdc.SetUserScale(m_dZoom,m_dZoom);

    m_pFunc->UpdateUI(memdc,tmNow);

    nPixCount = m_nPixCount + 1;
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
    Raise();
    //if(m_pOptionDlg == NULL)
    static wxMenu* pWidgetMenu(NULL);// = new wxMenu();
    if( pWidgetMenu == NULL )
    {
        pWidgetMenu = new wxMenu();

        wxMenuItem* mItem;
        mItem = new wxMenuItem( pWidgetMenu, wxID_ANY, wxString( wxT("固定位置") ) , wxEmptyString, wxITEM_NORMAL );
        pWidgetMenu->Append( mItem );

        mItem = new wxMenuItem( pWidgetMenu, wxID_ANY, wxString( wxT("有影无形") ) , wxEmptyString, wxITEM_NORMAL );
        pWidgetMenu->Append( mItem );

        mItem = new wxMenuItem( pWidgetMenu, wxID_ANY, wxString( wxT("总在最前") ) , wxEmptyString, wxITEM_NORMAL );
        pWidgetMenu->Append( mItem );


        mItem = new wxMenuItem( pWidgetMenu, wxID_ANY, wxString( wxT("通用选项") ) , wxEmptyString, wxITEM_NORMAL );
        pWidgetMenu->Append( mItem );

        pWidgetMenu->AppendSeparator();


        mItem = new wxMenuItem( pWidgetMenu, wxID_ANY, wxString( wxT("关闭") ) , wxEmptyString, wxITEM_NORMAL );
        pWidgetMenu->Append( mItem );
    }


    PopupMenu(pWidgetMenu);
    std::cout<<"OnRightUp"<<std::endl;
}

void MissWidget::SetScale(const float& dZoom)
{
    m_dZoom = dZoom;
    wxSize szBitmap = m_pFunc->GetSize();
    m_SizeWindow.cx = static_cast<int>(szBitmap.GetWidth()  * dZoom);
    m_SizeWindow.cy = static_cast<int>(szBitmap.GetHeight() * dZoom);
    m_bpUI = wxBitmap(m_SizeWindow.cx, m_SizeWindow.cy, 32);
    if(m_bpUI.IsOk())
    {
        BITMAP bm;
        ::GetObject(static_cast<HBITMAP>(m_bpUI.GetHBITMAP()), sizeof(bm), &bm);
        m_nPixCount = bm.bmWidth * bm.bmHeight;
        m_pBitmap = static_cast<unsigned int*>(bm.bmBits);
    }
}

void MissWidget::SetOpacity(int nOpacity)
{
    ///指定用于整张源位图的Alpha透明度值。(0~255)
    m_Blend.SourceConstantAlpha = nOpacity;
}

const float& MissWidget::GetScale() const
{
    return m_dZoom;
}

int MissWidget::GetOpacity() const
{
    return static_cast<int>(m_Blend.SourceConstantAlpha);
}

int MissWidget::GetWidgetID() const
{
    assert(m_nWidgetID != -1);
    return m_nWidgetID;
}

void MissWidget::SetWidgetID(int nID)
{
    m_nWidgetID = nID;
}
