#include "MissWidgetOption.h"
#include "../Impl/ImplMissWidget.h"
#include "../Common/WidgetEvent.h"

#include <wx/spinctrl.h>
#include <wx/slider.h>
#include <map>

typedef void (MissWidgetOption::*UpdataFunc)();
typedef std::map<int, UpdataFunc> MapUpdataFunc;

using namespace DTD;

class MissWidgetOption::Impl
{
public:
    Impl():pWidgets(NULL){}
    ImplMissWidget* pWidgets;
    static MapUpdataFunc mapUpdateFunc;
};

MapUpdataFunc MissWidgetOption::Impl::mapUpdateFunc;

MissWidgetOption::MissWidgetOption( wxWindow* parent, ImplMissWidget* pWidgets )
: WidgetOptionBase( parent )
, m_pImpl(new Impl)
{
    if (m_pImpl->mapUpdateFunc.empty())
    {
        MapUpdataFunc& mapUpdateFunc = m_pImpl->mapUpdateFunc;
        mapUpdateFunc.insert(MapUpdataFunc::value_type(WCI_POS, &MissWidgetOption::UpdatePos));
        mapUpdateFunc.insert(MapUpdataFunc::value_type(WCI_ZPOS, &MissWidgetOption::UpdateZPos));
        mapUpdateFunc.insert(MapUpdataFunc::value_type(WCI_SHADOW, &MissWidgetOption::UpdateShadow));
        mapUpdateFunc.insert(MapUpdataFunc::value_type(WCI_PIN, &MissWidgetOption::UpdatePin));
        mapUpdateFunc.insert(MapUpdataFunc::value_type(WCI_OPACITY, &MissWidgetOption::UpdateOpacity));
        mapUpdateFunc.insert(MapUpdataFunc::value_type(WCI_SCALE, &MissWidgetOption::UpdateScale));
        mapUpdateFunc.insert(MapUpdataFunc::value_type(WCI_EXIT, &MissWidgetOption::UpdateExit));
    }
    InitData(pWidgets);
    BindEvent();
}

MissWidgetOption::~MissWidgetOption()
{
}

void MissWidgetOption::InitData( ImplMissWidget* pWidgets )
{
    m_pImpl->pWidgets = pWidgets;
    for (MapUpdataFunc::iterator itor = m_pImpl->mapUpdateFunc.begin();
        itor != m_pImpl->mapUpdateFunc.end(); ++itor)
    {
        if (itor->first != WCI_EXIT)
        {
            (this->*(itor->second))();
        }
    }
}

void MissWidgetOption::BindEvent()
{
    m_pImpl->pWidgets->GetFrame()->Bind(wxEVT_RUNNINGWIDGET_CHANGED, &MissWidgetOption::OnWidgetDataChanged, this);
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

void MissWidgetOption::OnWidgetDataChanged( wxEvent& event )
{
    MapUpdataFunc::iterator iFind = m_pImpl->mapUpdateFunc.find(event.GetId());
    if (iFind != m_pImpl->mapUpdateFunc.end())
    {
        (this->*(iFind->second))();
    }
}

void MissWidgetOption::UpdatePos()
{
    wxPoint pt;
    m_pImpl->pWidgets->GetPos(pt);
    spinX->SetValue(pt.x);
    spinY->SetValue(pt.y);
}

void MissWidgetOption::UpdateZPos()
{
    int nZPos;
    m_pImpl->pWidgets->GetZPos(nZPos);
    choZ->SetSelection(nZPos);
}

void MissWidgetOption::UpdateShadow()
{
    bool bCheck(false);
    m_pImpl->pWidgets->GetShadow(bCheck);
    cbtnShadow->SetValue(bCheck);
}

void MissWidgetOption::UpdatePin()
{
    bool bCheck(false);
    m_pImpl->pWidgets->GetPin(bCheck);
    cbtnPin->SetValue(bCheck);
}

void MissWidgetOption::UpdateOpacity()
{
    int nOpacity(255);
    m_pImpl->pWidgets->GetOpacity(nOpacity);
    sldOpacity->SetValue(nOpacity);
}

void MissWidgetOption::UpdateScale()
{
    float fZoom(1.0f);
    m_pImpl->pWidgets->GetScale(fZoom);
    sldZoom->SetValue(static_cast<int>(fZoom*100));
    cbtnAllowZoom->SetValue(sldZoom->GetValue() != 100);
    sldZoom->Enable(cbtnAllowZoom->GetValue());
}

void MissWidgetOption::UpdateExit()
{
    Close();
}

