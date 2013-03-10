#include "MissWidget.h"
#include "../Common/WidgetDef.h"
#include "MissAPI/plugin/MissWidgetFuncBase.h"

#include <iostream>
#include <wx/menu.h>
#include "../Impl/ImplMissWidget.h"

using std::tr1::shared_ptr;

MissWidget::MissWidget(MissWidgetFuncBase * pFunc,
                       wxWindow* parent,
                       wxWindowID id,
                       const wxString& title,
                       const wxPoint& pos,
                       const wxSize& size,
                       long style)
: wxFrame(parent, id, title, pos, size, style)
, m_pFunc(pFunc)
, m_nWidgetID(-1)
{
    m_hWnd = static_cast<HWND>(GetHandle());

    long exStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
    exStyle |= WS_EX_LAYERED;
    ::SetWindowLong(m_hWnd, GWL_EXSTYLE, exStyle);

    m_Blend.BlendOp = AC_SRC_OVER;      ///ָ��Դ��ϲ�����Ŀǰ��Ψһ��Դ��Ŀ���ϲ���������Ϊ AC_SRC_OVER��
    m_Blend.BlendFlags = 0;             ///����Ϊ 0
    m_Blend.AlphaFormat = AC_SRC_ALPHA; ///�ó�Ա����Դ��Ŀ��λͼ�����͵ķ�ʽ��

    this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( MissWidget::OnLeftDown ) );
    this->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( MissWidget::OnRightUp ) );

}

MissWidget::~MissWidget()
{

}

void MissWidget::SetData(const DTD::SWidgetPara& data)
{
    m_pDraw = shared_ptr<ImplMissWidget>(new ImplMissWidget(this));
    m_pFunc->InitWidget(data.m_vecPata, std::tr1::static_pointer_cast<IMissWidget>(m_pDraw));
    SetScale(data.m_nZone / 100.0);
    SetOpacity(data.m_nOpacity);
    Move(data.m_ptPos);
}


void MissWidget::OnLeftDown(wxMouseEvent& event)
{
    ::PostMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(event.GetX(), event.GetY()));
}

void MissWidget::OnRightUp(wxMouseEvent& event)
{
    Raise();
//     static wxMenu* pWidgetMenu(NULL);// = new wxMenu();
//     if( pWidgetMenu == NULL )
//     {
//         pWidgetMenu = new wxMenu();
// 
//         wxMenuItem* mItem;
//         //pWidgetMenu->Append( mItem );
// 
//         mItem = new wxMenuItem( pWidgetMenu, wxID_ANY, wxString( wxT("��Ӱ����") ) , wxEmptyString, wxITEM_NORMAL );
//         pWidgetMenu->Append( mItem );
// 
//         mItem = new wxMenuItem( pWidgetMenu, wxID_ANY, wxString( wxT("������ǰ") ) , wxEmptyString, wxITEM_NORMAL );
//         pWidgetMenu->Append( mItem );
// 
// 
//         mItem = new wxMenuItem( pWidgetMenu, wxID_ANY, wxString( wxT("ͨ��ѡ��") ) , wxEmptyString, wxITEM_NORMAL );
//         pWidgetMenu->Append( mItem );
// 
//         pWidgetMenu->AppendSeparator();
// 
//         mItem = new wxMenuItem( pWidgetMenu, wxID_ANY, wxString( wxT("�ر�") ) , wxEmptyString, wxITEM_NORMAL );
//         pWidgetMenu->Append( mItem );
//     }
// 
//     PopupMenu(pWidgetMenu);
    std::cout<<"OnRightUp"<<std::endl;
}

void MissWidget::SetScale(const float& dZoom)
{
    m_dZoom = dZoom;
    wxSize szBitmap = GetBoundRect();
    m_SizeWindow.cx = szBitmap.GetWidth();
    m_SizeWindow.cy = szBitmap.GetHeight();
    m_pDraw->UpdateBuffer();
}

const float& MissWidget::GetScale() const
{
    return m_dZoom;
}

void MissWidget::SetOpacity(int nOpacity)
{
    ///ָ����������Դλͼ��Alpha͸����ֵ��(0~255)
    m_Blend.SourceConstantAlpha = nOpacity;
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

void MissWidget::UpdateWindow( const HDC& hdcSrc )
{
    static HDC s_hdcScreen = ::GetDC(m_hWnd);
    static POINT s_ptSrc = {0, 0};
    ::UpdateLayeredWindow(m_hWnd, s_hdcScreen, NULL, &m_SizeWindow, hdcSrc,
        &s_ptSrc, 0, &m_Blend, ULW_ALPHA);
}

void MissWidget::SetSize( const wxSize& size )
{
    m_szSrc = size;
    wxSize szBitmap = GetBoundRect();
    m_SizeWindow.cx = szBitmap.GetWidth();
    m_SizeWindow.cy = szBitmap.GetHeight();
    m_pDraw->UpdateBuffer();
}

wxSize MissWidget::GetBoundRect() const
{
    return wxSize(static_cast<int>(m_szSrc.GetWidth()  * m_dZoom), 
        static_cast<int>(m_szSrc.GetHeight() * m_dZoom));
}
