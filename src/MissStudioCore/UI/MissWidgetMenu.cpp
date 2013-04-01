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

std::shared_ptr<wxMenu> MissWidgetMenu::GetMenu( ImplMissWidget* pWidgets )
{
    m_pImpl->pWidgets = pWidgets;
    wxMenu* pRet = new wxMenu;
    wxMenu* mnuWindow = new wxMenu;
    pRet->AppendSubMenu(mnuWindow, wxT("´°¿Ú"));
    pRet->Append(CI_WIDGET_WINDOW_OPTION, wxT("ÉèÖÃ"));
    pRet->Append(CI_WIDGET_EXIT, wxT("ÍË³ö(&x)"));
    pRet->SetNextHandler(&m_pImpl->hHandle);
    return std::shared_ptr<wxMenu>(pRet);
}

void MissWidgetMenu::BindEvent()
{
    m_pImpl->hHandle.Bind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetOption, this, CI_WIDGET_WINDOW_OPTION);
    m_pImpl->hHandle.Bind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetExit, this, CI_WIDGET_EXIT);

}

void MissWidgetMenu::UnbindEvent()
{
    m_pImpl->hHandle.Unbind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetExit, this);

}

void MissWidgetMenu::OnMenuWidgetOption( wxCommandEvent& event )
{
    MissWidgetOption* pWin = m_pImpl->winManager.CreateWin<MissWidgetOption>
        (wxString::Format("0x%04X", (int)m_pImpl->pWidgets));
    pWin->InitData(m_pImpl->pWidgets);
    pWin->Raise();
}


void MissWidgetMenu::OnMenuWidgetExit( wxCommandEvent& event )
{
    if (m_pImpl->pWidgets)
    {
        m_pImpl->pWidgets->CloseWidget();
    }
}
