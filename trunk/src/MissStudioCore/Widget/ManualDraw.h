#ifndef MANUALDRAW_H__
#define MANUALDRAW_H__

#include "ILayeredDraw.h"
#include <wx\dcmemory.h>
#include <memory>

class ManualDraw : public ILayeredDraw
{
public:
    ManualDraw(HWND hWnd);
    virtual ~ManualDraw();

    virtual wxDC* DrawBegin();
    virtual void DrawEnd( wxDC* pDc );


protected:
    virtual void ReCaleBuffer();

private:
    wxBitmap                         m_bpUI;
    std::tr1::shared_ptr<wxMemoryDC> m_pMemDc;
    unsigned int*                    m_pBitmap;
    int                              m_nPixCount;
};



#endif // MANUALDRAW_H__
