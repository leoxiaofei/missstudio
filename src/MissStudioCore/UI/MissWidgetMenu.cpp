#include "MissWidgetMenu.h"

#include "../Common/CustomId.h"
#include "../Impl/ImplMissWidget.h"
#include "MissTools/OneWinManager.h"

#include <iostream>
#include <wx/menu.h>
#include "MissWidgetOption.h"
#include "MissCoreFrame.h"

using namespace DTD;

class MissWidgetMenu::Impl
{
public:
    Impl()
    : pWidgets(NULL)
    , winManager(wxAppFrame){}
    wxEvtHandler    hHandle;
    ImplMissWidget* pWidgets;
    OneWinManager   winManager;
};

MissWidgetMenu::MissWidgetMenu()
: m_pImpl(new Impl)
{
    BindEvent();
}

MissWidgetMenu::~MissWidgetMenu()
{
    UnbindEvent();
}

std::tr1::shared_ptr<wxMenu> MissWidgetMenu::GetMenu( ImplMissWidget* pWidgets )
{
    m_pImpl->pWidgets = pWidgets;
    wxMenu* pRet = new wxMenu;
    wxMenu* mnuWindow = new wxMenu;
    wxMenuItem* pItem;

    wxMenu* mnuZPos = new wxMenu;
    mnuZPos->AppendCheckItem(CI_WIDGET_ZPOS_TOP, wxT("�ö�"));
    mnuZPos->AppendCheckItem(CI_WIDGET_ZPOS_NORMAL, wxT("����"));
    int nPosition;
    pWidgets->GetZPos(nPosition);
    pItem = mnuZPos->FindItemByPosition(nPosition);
    pItem->Check(true);
    mnuWindow->AppendSubMenu(mnuZPos, wxT("Z��λ��"));

    wxMenu* mnuOpacity = new wxMenu;
    for (int ix = 0; ix != 9; ++ix)
    {
        mnuOpacity->AppendCheckItem(CI_WIDGET_OPACITY + ix, wxString::Format(wxT("%d%%"), ix*10));
    }
    int nOpacity;
    pWidgets->GetOpacity(nOpacity);
    pItem = mnuOpacity->FindItemByPosition((255 - nOpacity) / 255.0 * 10);
    pItem->Check(true);
    mnuWindow->AppendSubMenu(mnuOpacity, wxT("͸����"));

    wxMenu* mnuScale = new wxMenu;
    for (int ix = 0; ix != 7; ++ix)
    {
        mnuScale->AppendCheckItem(CI_WIDGET_SCALE + ix, wxString::Format(wxT("%d%%"), 50 + ix * 25));
    }
    float fZoom;
    pWidgets->GetScale(fZoom);
    pItem = mnuScale->FindItemByPosition((int)(fZoom * 100 - 50) / 25);
    pItem->Check(true);
    mnuWindow->AppendSubMenu(mnuScale, wxT("����"));

    
    bool bCheck(false);
    pItem = mnuWindow->Append(CI_WIDGET_SHADOW, wxT("��Ӱ����"), wxT("��괩͸"), wxITEM_CHECK);
    pWidgets->GetShadow(bCheck);
    pItem->Check(bCheck);

    pItem = mnuWindow->Append(CI_WIDGET_PIN, wxT("�̶�λ��"), wxT("��ֹ�϶�"), wxITEM_CHECK);
    pWidgets->GetPin(bCheck);
    pItem->Check(bCheck);

    pRet->AppendSubMenu(mnuWindow, wxT("����"));

    pRet->Append(CI_WIDGET_WINDOW_OPTION, wxT("����"));
    pRet->Append(CI_WIDGET_EXIT, wxT("�ر�(&C)"));

    pRet->SetNextHandler(&m_pImpl->hHandle);
	return std::tr1::shared_ptr<wxMenu>(pRet);
}

void MissWidgetMenu::BindEvent()
{
    for (int ix = CI_WIDGET_OPACITY; ix != CI_WIDGET_OPACITY_END; ++ix)
    {
        m_pImpl->hHandle.Bind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetOpacity, this, ix);
    }
    for (int ix = CI_WIDGET_SCALE; ix != CI_WIDGET_SCALE_END; ++ix)
    {
        m_pImpl->hHandle.Bind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetScale, this, ix);
    }
    m_pImpl->hHandle.Bind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetZPos, this, CI_WIDGET_ZPOS_TOP);
    m_pImpl->hHandle.Bind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetZPos, this, CI_WIDGET_ZPOS_NORMAL);
    m_pImpl->hHandle.Bind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetShadow, this, CI_WIDGET_SHADOW);
    m_pImpl->hHandle.Bind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetPin, this, CI_WIDGET_PIN);
    m_pImpl->hHandle.Bind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetOption, this, CI_WIDGET_WINDOW_OPTION);
    m_pImpl->hHandle.Bind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetExit, this, CI_WIDGET_EXIT);
}

void MissWidgetMenu::UnbindEvent()
{
    m_pImpl->hHandle.Unbind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetShadow, this);
    m_pImpl->hHandle.Unbind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetPin, this);
    m_pImpl->hHandle.Unbind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetOption, this);
    m_pImpl->hHandle.Unbind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetExit, this);
}

void MissWidgetMenu::OnMenuWidgetOption( wxCommandEvent& event )
{
    MissWidgetOption* pWin = m_pImpl->winManager.CreateWin<MissWidgetOption, ImplMissWidget*>
        (wxString::Format("0x%04X", (int)m_pImpl->pWidgets), m_pImpl->pWidgets);
    pWin->Raise();
}


void MissWidgetMenu::OnMenuWidgetExit( wxCommandEvent& event )
{
    m_pImpl->pWidgets->CloseWidget();
}

void MissWidgetMenu::OnMenuWidgetShadow( wxCommandEvent& event )
{
    m_pImpl->pWidgets->SetShadow(event.IsChecked());
}

void MissWidgetMenu::OnMenuWidgetPin( wxCommandEvent& event )
{
    m_pImpl->pWidgets->SetPin(event.IsChecked());
}

void MissWidgetMenu::OnMenuWidgetZPos( wxCommandEvent& event )
{
    int nZPos = event.GetId() - CI_WIDGET_ZPOS_TOP;
    m_pImpl->pWidgets->SetZPos(nZPos);
}

void MissWidgetMenu::OnMenuWidgetOpacity( wxCommandEvent& event )
{
    int nOpacity = event.GetId() - CI_WIDGET_OPACITY;
    nOpacity = 255 - (nOpacity / 10.0) * 255;
    m_pImpl->pWidgets->SetOpacity(nOpacity);
}

void MissWidgetMenu::OnMenuWidgetScale( wxCommandEvent& event )
{
    int nScale = event.GetId() - CI_WIDGET_SCALE;
    float fZoom = (50 + nScale * 25) / 100.0;
    m_pImpl->pWidgets->SetScale(fZoom);
}
