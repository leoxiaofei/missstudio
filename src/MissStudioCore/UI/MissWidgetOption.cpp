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

MissWidgetOption::MissWidgetOption( wxWindow* parent, ImplMissWidget* pWidgets )
: WidgetOptionBase( parent )
, m_pImpl(new Impl)
{
    InitData(pWidgets);
}

void MissWidgetOption::InitData( ImplMissWidget* pWidgets )
{
    m_pImpl->pWidgets = pWidgets;

    wxPoint pt;
    pWidgets->GetPos(pt);
    spinX->SetValue(pt.x);
    spinY->SetValue(pt.y);

    float fZoom(1.0f);
    pWidgets->GetScale(fZoom);
    sldZoom->SetValue(static_cast<int>(fZoom*100));
    cbtnAllowZoom->SetValue(sldZoom->GetValue() != 100);
    sldZoom->Enable(cbtnAllowZoom->GetValue());


    int nOpacity(255);
    pWidgets->GetOpacity(nOpacity);
    sldOpacity->SetValue(nOpacity);

    bool bCheck(false);
    pWidgets->GetPin(bCheck);
    cbtnPin->SetValue(bCheck);

    //bool bCheck(false);
    pWidgets->GetShadow(bCheck);
    cbtnShadow->SetValue(bCheck);

    int nZPos;
    pWidgets->GetZPos(nZPos);
    choZ->SetSelection(nZPos);
    //
}

void MissWidgetOption::Backup()
{

}

void MissWidgetOption::Restore()
{

}

void MissWidgetOption::OnSpinXCtrl( wxSpinEvent& event )
{
    wxPoint pos(spinX->GetValue(), spinY->GetValue());
    m_pImpl->pWidgets->SetPos(pos);
}

void MissWidgetOption::OnSpinYCtrl( wxSpinEvent& event )
{
    wxPoint pos(spinX->GetValue(), spinY->GetValue());
    m_pImpl->pWidgets->SetPos(pos);
}

void MissWidgetOption::OnCheckPinBox( wxCommandEvent& event )
{
    m_pImpl->pWidgets->SetPin(event.IsChecked());
}

void MissWidgetOption::OnChoZ( wxCommandEvent& event )
{
    m_pImpl->pWidgets->SetZPos(event.GetSelection());
}

void MissWidgetOption::OnCheckAllowZoomBox( wxCommandEvent& event )
{
    sldZoom->Enable(event.IsChecked());
    if (!event.IsChecked())
    {
        sldZoom->SetValue(100);
        m_pImpl->pWidgets->SetScale(1);
    }
}

void MissWidgetOption::OnScrollZoomChanged( wxScrollEvent& event )
{
    float fZoom = event.GetPosition() / 100.0;
    m_pImpl->pWidgets->SetScale(fZoom);
}

void MissWidgetOption::OnCheckShadowBox( wxCommandEvent& event )
{
    m_pImpl->pWidgets->SetShadow(event.IsChecked());
}

void MissWidgetOption::OnScrollOpacityChanged( wxScrollEvent& event )
{
    int nOpacity = event.GetPosition();
    m_pImpl->pWidgets->SetOpacity(nOpacity);
}

void MissWidgetOption::OnBtnCloseClick( wxCommandEvent& event )
{
    Close();
}

void MissWidgetOption::UpdateUI( int nFlag )
{

}
