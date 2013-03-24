#include "ILayeredDraw.h"

ILayeredDraw::ILayeredDraw( HWND hWnd )
: m_hWnd(hWnd)
{
    //m_hWnd = static_cast<HWND>(pFrame->GetHandle());
    m_hdcScreen = ::GetDC(m_hWnd);

    long exStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
    exStyle |= WS_EX_LAYERED;
    ::SetWindowLong(m_hWnd, GWL_EXSTYLE, exStyle);

    m_Blend.BlendOp = AC_SRC_OVER;      ///ָ��Դ��ϲ�����Ŀǰ��Ψһ��Դ��Ŀ���ϲ���������Ϊ AC_SRC_OVER��
    m_Blend.BlendFlags = 0;             ///����Ϊ 0
    m_Blend.AlphaFormat = AC_SRC_ALPHA; ///�ó�Ա����Դ��Ŀ��λͼ�����͵ķ�ʽ��
}

ILayeredDraw::~ILayeredDraw()
{

}

void ILayeredDraw::UpdateWindow( const HDC& hdcSrc )
{
    static POINT s_ptSrc = {0, 0};
    ::UpdateLayeredWindow(m_hWnd, m_hdcScreen, NULL, &m_szWindow, hdcSrc,
        &s_ptSrc, 0, &m_Blend, ULW_ALPHA);
}

void ILayeredDraw::SetSize( const wxSize& size )
{
    m_szSrc = size;
    ReCaleWindowSize();
}

void ILayeredDraw::SetScale( const float& dZoom )
{
    m_dZoom = dZoom;
    ReCaleWindowSize();
}

void ILayeredDraw::SetOpacity( int nOpacity )
{
    ///ָ����������Դλͼ��Alpha͸����ֵ��(0~255)
    m_Blend.SourceConstantAlpha = nOpacity;
}

void ILayeredDraw::ReCaleWindowSize()
{
    m_szWindow.cx = static_cast<int>(m_szSrc.GetWidth()  * m_dZoom);
    m_szWindow.cy = static_cast<int>(m_szSrc.GetHeight() * m_dZoom);
    ReCaleBuffer();
}


const SIZE& ILayeredDraw::GetBoundRect() const
{
    return m_szWindow;
}

const float& ILayeredDraw::GetScale() const
{
    return m_dZoom;
}

int ILayeredDraw::GetOpacity() const
{
    return static_cast<int>(m_Blend.SourceConstantAlpha);
}

