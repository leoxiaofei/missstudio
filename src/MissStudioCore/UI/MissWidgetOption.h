﻿#ifndef __MISSWIDGETOPTION__
#define __MISSWIDGETOPTION__

#include "../Generated/GUIFrame.h"
#include <memory>

class ImplMissWidget;

class MissWidgetOption : public WidgetOptionBase
{
    class Impl;
public:
    MissWidgetOption( wxWindow* parent, ImplMissWidget* pWidgets );
    ~MissWidgetOption();

protected:
    void InitData(ImplMissWidget* pWidgets);
    void BindEvent();

    void Backup();
    void Restore();

    virtual void OnSpinXCtrl( wxSpinEvent& event );
    virtual void OnSpinYCtrl( wxSpinEvent& event );
    virtual void OnCheckPinBox( wxCommandEvent& event );
    virtual void OnChoZ( wxCommandEvent& event );
    virtual void OnCheckAllowZoomBox( wxCommandEvent& event );
    virtual void OnScrollZoomChanged( wxScrollEvent& event );
    virtual void OnCheckShadowBox( wxCommandEvent& event );
    virtual void OnScrollOpacityChanged( wxScrollEvent& event );
    virtual void OnBtnCloseClick( wxCommandEvent& event );

    void OnWidgetDataChanged(wxEvent& event);

    void UpdatePos();
    void UpdateZPos();
    void UpdateShadow();
    void UpdatePin();
    void UpdateOpacity();
    void UpdateScale();
    void UpdateExit();

private:
    std::tr1::shared_ptr<Impl> m_pImpl;

};

#endif // __MISSWIDGETOPTION__
