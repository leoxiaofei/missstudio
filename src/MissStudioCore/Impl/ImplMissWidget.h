#ifndef IMPLMISSWIDGET_H__
#define IMPLMISSWIDGET_H__

#include "MissAPI\interface\IMissWidget.h"
#include <wx\dcmemory.h>
#include <memory>

class MissWidget;

class ImplMissWidget : public IMissWidget
{
public:
    ImplMissWidget(MissWidget* pMissWidget);
    ~ImplMissWidget();

    virtual wxFrame* GetFrame() const;

    virtual void SetSize( const wxSize& size );

    virtual wxDC* DrawBegin();

    virtual void DrawEnd( wxDC* pDc );

    virtual void CloseWidget();

protected:
    void UpdateBuffer();

private:
    wxBitmap           m_bpUI;
    std::tr1::shared_ptr<wxMemoryDC> m_pMemDc;
    unsigned int       *m_pBitmap;
    int                m_nPixCount;
    MissWidget*        m_pMissWidget;
    friend class MissWidget;
};


#endif // IMPLMISSWIDGET_H__
