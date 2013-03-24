#include "ILayeredDraw.h"

ILayeredDraw::ILayeredDraw( HWND hWnd )
: m_hWnd(hWnd)
{
    //m_hWnd = static_cast<HWND>(pFrame->GetHandle());
    m_hdcScreen = ::GetDC(m_hWnd);

    long exStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
    exStyle |= WS_EX_LAYERED;
    ::SetWindowLong(m_hWnd, GWL_EXSTYLE, exStyle);

    m_Blend.BlendOp = AC_SRC_OVER;      ///指定源混合操作。目前，唯一的源和目标混合操作被定义为 AC_SRC_OVER。
    m_Blend.BlendFlags = 0;             ///必须为 0
    m_Blend.AlphaFormat = AC_SRC_ALPHA; ///该成员控制源和目标位图被解释的方式。
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
    ///指定用于整张源位图的Alpha透明度值。(0~255)
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

