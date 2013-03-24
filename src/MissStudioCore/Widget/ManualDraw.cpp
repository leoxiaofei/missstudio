#include "ManualDraw.h"


using std::tr1::shared_ptr;

ManualDraw::ManualDraw(HWND hWnd)
    : ILayeredDraw(hWnd)
    , m_pBitmap(NULL)
    , m_nPixCount(0)
{
}

ManualDraw::~ManualDraw()
{
}

wxDC* ManualDraw::DrawBegin()
{
    static int nPixCount;
    static unsigned int* pBitmap;

    nPixCount = m_nPixCount + 1;
    pBitmap = m_pBitmap;

    while (--nPixCount)
    {
        *pBitmap = 0x01000000;
        ++pBitmap;
    }

    return m_pMemDc.get();
}

void ManualDraw::DrawEnd( wxDC* pDc )
{
    static int nPixCount;
    static unsigned int* pBitmap;
    nPixCount = m_nPixCount + 1;
    pBitmap = m_pBitmap;

    while (--nPixCount)
    {
        *pBitmap -= 0x01000000;
        ++pBitmap;
    }

    UpdateWindow(static_cast<HDC>(pDc->GetHDC()));
}

void ManualDraw::ReCaleBuffer()
{
    const SIZE& sz = GetBoundRect();
    m_bpUI = wxBitmap(sz.cx, sz.cy, 32);
    if(m_bpUI.IsOk())
    {
        m_pMemDc = shared_ptr<wxMemoryDC>(new wxMemoryDC(m_bpUI));
        BITMAP bm;
        ::GetObject(static_cast<HBITMAP>(m_bpUI.GetHBITMAP()), sizeof(bm), &bm);
        m_nPixCount = bm.bmWidth * bm.bmHeight;
        m_pBitmap = static_cast<unsigned int*>(bm.bmBits);
    }
}
