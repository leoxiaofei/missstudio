
#ifndef __MISSWIDGET__
#define __MISSWIDGET__

#include <wx\frame.h>
#include "../Common/Targetver.h"
#include <windows.h>
#include <memory>

namespace DTD
{
    struct SWidgetPara;
}

class MissWidgetFuncBase;
class ImplMissWidget;

class MissWidget : public wxFrame
{
public:
    /** Constructor */
    MissWidget( MissWidgetFuncBase * pFunc,
                wxWindow* parent, wxWindowID id = wxID_ANY,
                const wxString& title = wxT("MissWidget"),
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxSize( 200,200 ),
                long style = 0 | wxTAB_TRAVERSAL );
    ~MissWidget();

    void SetData(const DTD::SWidgetPara& data);
    void GetData(DTD::SWidgetPara& data);

    int  GetWidgetID() const;
    void SetWidgetID(int nID);

    void SetScale(const float& dZoom);
    void SetOpacity(int nOpacity);

    const float& GetScale() const;
    int          GetOpacity() const;
    void SetSize( const wxSize& size );
    const wxSize& GetSize() const;

    wxSize GetBoundRect() const;

    void UpdateWindow(const HDC& hdcSrc);

private:
    virtual void OnLeftDown( wxMouseEvent& event );
    virtual void OnRightUp( wxMouseEvent& event );

private:
    //std::tr1::shared_ptr<MissWidgetFuncBase> m_pFunc;
    MissWidgetFuncBase*                      m_pFunc;
    std::tr1::shared_ptr<ImplMissWidget>     m_pDraw;

    BLENDFUNCTION      m_Blend;
    float              m_dZoom;
    SIZE               m_SizeWindow;
    wxSize             m_szSrc;
    HWND               m_hWnd;

    int                m_nWidgetID;
};

#endif // __MissWidget__
