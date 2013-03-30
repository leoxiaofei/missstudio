#ifndef IMPLMISSWIDGET_H__
#define IMPLMISSWIDGET_H__

#include "MissAPI\interface\IMissWidget.h"
#include <memory>
namespace DTD
{
    struct SWidgetPara;
}

class ILayeredDraw;
class MissWidgetFuncBase;
class wxMouseEvent;
class wxPoint;

class ImplMissWidget : public IMissWidget
{
public:
    ImplMissWidget(MissWidgetFuncBase* pFunc);
    ~ImplMissWidget();

    virtual wxFrame*     GetFrame() const;
    virtual wxDC*        DrawBegin();
    virtual void         DrawEnd( wxDC* pDc );
    virtual void         CloseWidget();
    virtual void         SetSize( const wxSize& size );
    virtual unsigned int GetRunID() const;

    void GetPos(wxPoint& pt) const;
    void SetPos(const wxPoint& pt);

    void GetScale(float& dZoom) const;
    void SetScale(const float& dZoom);

    void GetOpacity(int& nOpacity) const;
    void SetOpacity(const int& nOpacity);

    void SetData(const DTD::SWidgetPara& data);
    void GetData(DTD::SWidgetPara& data) const;

    int  GetWidgetID() const;
    void SetWidgetID(int nID);

    void PreClose();
    void UpdateUI();

protected:
    virtual void OnLeftDown( wxMouseEvent& event );
    virtual void OnRightUp( wxMouseEvent& event );

private:
    std::tr1::shared_ptr<wxFrame>      m_ptFrame;
    std::tr1::shared_ptr<ILayeredDraw> m_ptDraw;
    MissWidgetFuncBase*                m_pFunc;
    unsigned int                       m_uRunID;
    int                                m_nWidgetID;
};


#endif // IMPLMISSWIDGET_H__
