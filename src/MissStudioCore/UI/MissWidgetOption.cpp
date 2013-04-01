#include "MissWidgetOption.h"
#include "..\Impl\ImplMissWidget.h"

#include <wx/spinctrl.h>
#include <wx/slider.h>

class MissWidgetOption::Impl
{
public:
    Impl():pWidgets(NULL){}
    ImplMissWidget* pWidgets;

};

MissWidgetOption::MissWidgetOption( wxWindow* parent )
: WidgetOptionBase( parent )
, m_pImpl(new Impl)
{
}

void MissWidgetOption::InitData( ImplMissWidget* pWidgets )
{
    m_pImpl->pWidgets = pWidgets;

    wxPoint pt;
    pWidgets->GetPos(pt);
    spinX->SetValue(pt.x);
    spinY->SetValue(pt.y);

    float fZoom(1);
    pWidgets->GetScale(fZoom);
    sldZoom->SetValue(static_cast<int>(fZoom*100));

    int nOpacity(255);
    pWidgets->GetOpacity(nOpacity);
    sldOpacity->SetValue(nOpacity);

    //GetDesktopWindow();
}

void MissWidgetOption::Backup()
{

}

void MissWidgetOption::Restore()
{

}

void MissWidgetOption::OnSpinXCtrl( wxSpinEvent& event )
{
}

void MissWidgetOption::OnSpinYCtrl( wxSpinEvent& event )
{
}

void MissWidgetOption::OnCheckPinBox( wxCommandEvent& event )
{
}

void MissWidgetOption::OnChoZ( wxCommandEvent& event )
{
}

void MissWidgetOption::OnCheckAllowZoomBox( wxCommandEvent& event )
{
}

void MissWidgetOption::OnScrollZoomChanged( wxScrollEvent& event )
{
}

void MissWidgetOption::OnCheckShadowBox( wxCommandEvent& event )
{
}

void MissWidgetOption::OnScrollOpacityChanged( wxScrollEvent& event )
{
}

void MissWidgetOption::OnBtnCloseClick( wxCommandEvent& event )
{
}
