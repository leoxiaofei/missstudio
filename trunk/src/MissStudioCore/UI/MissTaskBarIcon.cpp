/***************************************************************
 * Name:      MissTaskBarIcon.cpp
 * Purpose:   Task Bar Icon
 * Author:    leoxiaofei (xxffsoft@163.com)
 * Created:   2012-01-21
 * Copyright: leoxiaofei (http://www.leoxiaofei.com)
 * License:
 **************************************************************/

#include "MissTaskBarIcon.h"

#include <wx/menu.h>
#include "../UI/MissCoreFrame.h"
#include "../Common/CustomId.h"
#include "MissPluginOption.h"
#include "MissDesktopTools.h"

using namespace DTD;

MissTaskBarIcon::MissTaskBarIcon()
: wxTaskBarIcon()
{
    //ctor
    BindEvent();
}

MissTaskBarIcon::~MissTaskBarIcon()
{
    //dtor
    UnbindEvent();
}

void MissTaskBarIcon::BindEvent()
{
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MissTaskBarIcon::OnMenuCoreOptionSelection, this, CI_CORE_OPTION);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MissTaskBarIcon::OnMenuPluginOptionSelection, this, CI_PLUGIN_OPTION);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MissTaskBarIcon::OnMenuWidgetsOptionSelection, this, CI_WIDGET_OPTION);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MissTaskBarIcon::OnMenuAboutSelection, this, CI_ABOUT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MissTaskBarIcon::OnMenuExitSelection, this, wxID_EXIT);
}

void MissTaskBarIcon::UnbindEvent()
{
    Unbind(wxEVT_COMMAND_MENU_SELECTED, &MissTaskBarIcon::OnMenuCoreOptionSelection, this);
    Unbind(wxEVT_COMMAND_MENU_SELECTED, &MissTaskBarIcon::OnMenuPluginOptionSelection, this);
    Unbind(wxEVT_COMMAND_MENU_SELECTED, &MissTaskBarIcon::OnMenuWidgetsOptionSelection, this);
    Unbind(wxEVT_COMMAND_MENU_SELECTED, &MissTaskBarIcon::OnMenuAboutSelection, this);
    Unbind(wxEVT_COMMAND_MENU_SELECTED, &MissTaskBarIcon::OnMenuExitSelection, this);
}

wxMenu * MissTaskBarIcon::CreatePopupMenu()
{
    wxMenu* pRet = new wxMenu;
    pRet->Append(CI_CORE_OPTION, wxT("系统设置(&S)"));
    pRet->Append(CI_PLUGIN_OPTION, wxT("插件设置(&P)"));
    pRet->Append(CI_WIDGET_OPTION, wxT("桌面工具管理(&W)"));
    pRet->Append(CI_ABOUT, wxT("关于迷失工作室(&A)"));
    pRet->Append(wxID_EXIT, wxT("退出(&x)"));
    return pRet;
}

void MissTaskBarIcon::OnMenuCoreOptionSelection( wxCommandEvent& event )
{

}

void MissTaskBarIcon::OnMenuPluginOptionSelection( wxCommandEvent& event )
{
    MissPluginOption option(wxAppFrame);
    option.ShowModal();
}

void MissTaskBarIcon::OnMenuWidgetsOptionSelection( wxCommandEvent& event )
{
    MissDesktopTools tools(wxAppFrame);
    tools.ShowModal();
}

void MissTaskBarIcon::OnMenuAboutSelection( wxCommandEvent& event )
{
}

void MissTaskBarIcon::OnMenuExitSelection( wxCommandEvent& event )
{
    wxWindow* p = wxTopLevelWindows.GetLast()->GetData();
    wxCloseEvent send(wxEVT_CLOSE_WINDOW);
    wxPostEvent(wxAppFrame, send);
}



