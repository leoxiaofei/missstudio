#include "MissWidgetMenu.h"
#include <wx/menu.h>
#include "../Common/CustomId.h"
#include <iostream>
#include "../Impl/ImplMissWidget.h"

using namespace DTD;

class MissWidgetMenu::Impl
{
public:
    Impl():pWidgets(NULL){}
    wxEvtHandler    hHandle;
    ImplMissWidget* pWidgets;
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
    pRet->Append(CI_WIDGET_EXIT, wxT("ÍË³ö(&x)"));
    pRet->SetNextHandler(&m_pImpl->hHandle);
    return std::shared_ptr<wxMenu>(pRet);
}

void MissWidgetMenu::BindEvent()
{
    m_pImpl->hHandle.Bind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetExit, this, CI_WIDGET_EXIT);

}

void MissWidgetMenu::UnbindEvent()
{
    m_pImpl->hHandle.Unbind(wxEVT_COMMAND_MENU_SELECTED, &MissWidgetMenu::OnMenuWidgetExit, this);

}

void MissWidgetMenu::OnMenuWidgetExit( wxCommandEvent& event )
{
    if (m_pImpl->pWidgets)
    {
        m_pImpl->pWidgets->CloseWidget();
    }
}


