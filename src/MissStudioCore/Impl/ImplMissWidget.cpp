#include "ImplMissWidget.h"
#include "..\Widget\MissWidget.h"
#include <wx\dc.h>

using std::tr1::shared_ptr;

ImplMissWidget::ImplMissWidget( MissWidget* pMissWidget )
: m_pMissWidget(pMissWidget)
, m_pBitmap(NULL)
, m_nPixCount(0)
{

}

ImplMissWidget::~ImplMissWidget()
{

}

wxFrame* ImplMissWidget::GetFrame() const
{
    return m_pMissWidget;
}

void ImplMissWidget::SetSize( const wxSize& size )
{
    m_pMissWidget->SetSize(size);
}

wxDC* ImplMissWidget::DrawBegin()
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

void ImplMissWidget::DrawEnd( wxDC* pDc )
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

    m_pMissWidget->UpdateWindow(static_cast<HDC>(pDc->GetHDC()));
}

void ImplMissWidget::CloseWidget()
{
    throw std::exception("The method or operation is not implemented.");
}

void ImplMissWidget::UpdateBuffer()
{
    wxSize size = m_pMissWidget->GetBoundRect();
    m_bpUI = wxBitmap(size, 32);
    if(m_bpUI.IsOk())
    {
        m_pMemDc = shared_ptr<wxMemoryDC>(new wxMemoryDC(m_bpUI));
        BITMAP bm;
        ::GetObject(static_cast<HBITMAP>(m_bpUI.GetHBITMAP()), sizeof(bm), &bm);
        m_nPixCount = bm.bmWidth * bm.bmHeight;
        m_pBitmap = static_cast<unsigned int*>(bm.bmBits);
    }
}

