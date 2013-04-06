#ifndef ILAYEREDDRAW_H__
#define ILAYEREDDRAW_H__

#include <windows.h>
#include <wx/gdicmn.h>

class wxDC;

class ILayeredDraw
{
public:
    ILayeredDraw(HWND hWnd);
    virtual ~ILayeredDraw();

    void SetSize( const wxSize& size );
    void SetScale(const float& dZoom);
    void SetOpacity(int nOpacity);

    const float& GetScale() const;
    int          GetOpacity() const;
    const SIZE&  GetBoundRect() const;

    void UpdateWindow(const HDC& hdcSrc);

    virtual wxDC* DrawBegin() = 0;
    virtual void DrawEnd( wxDC* pDc ) = 0;
    virtual void UpdateLayered() = 0;

protected:
    void ReCaleWindowSize();
    virtual void ReCaleBuffer() = 0;

private:
    BLENDFUNCTION      m_Blend;
    float              m_dZoom;
    SIZE               m_szWindow;
    HWND               m_hWnd;
    HDC                m_hdcScreen;
    wxSize             m_szSrc;

};

#endif // ILAYEREDDRAW_H__
