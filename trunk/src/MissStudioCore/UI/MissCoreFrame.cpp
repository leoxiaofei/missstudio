#include "MissCoreFrame.h"

#include "../BLL/MissHotKeyManager.h"
#include "../BLL/MissPluginManager.h"
#include "../BLL/MissTimerManager.h"
#include "../BLL/MissWidgetManager.h"
#include "../UI/MissTaskBarIcon.h"

#include <wx/dir.h>
#include <wx/event.h>
#include <wx/menu.h>
#include <wx/string.h>
#include <wx/timer.h>
#include <iostream>
#include <wx/window.h>
#include <wx/app.h>

using std::tr1::shared_ptr;

DEFINE_LOCAL_EVENT_TYPE(wxEVT_INITIALIZE);

// BEGIN_EVENT_TABLE(MissCoreFrame, wxFrame)
//     EVT_MENU(CI_HOTKEY_OPTION, MissCoreFrame::OnMenuHotKeyOptionSelection)
// END_EVENT_TABLE()

class MissCoreFrame::Impl
{
public:
	shared_ptr<MissTaskBarIcon> pTrayIcon;
    shared_ptr<wxTimer>         pMainTimer;

    void SetupUi(wxFrame* parent);
private:

};

void MissCoreFrame::Impl::SetupUi( wxFrame* parent )
{
    wxIcon icon = wxICON(RC_STUDIO_ICON);
    parent->SetIcon(icon); // To Set App Icon

    pTrayIcon = shared_ptr<MissTaskBarIcon>(new MissTaskBarIcon(parent));
    pTrayIcon->SetIcon(icon, wxT("迷失工作室"));

    pMainTimer = shared_ptr<wxTimer>(new wxTimer(parent));
}


MissCoreFrame::MissCoreFrame()
: wxFrame(0, wxID_ANY, wxT("迷失工作室"))
, m_pImpl(new Impl)
{
    m_pImpl->SetupUi(this);
    Center();
    BindEvent();

    ///发送一个初始化消息
    wxCommandEvent send(wxEVT_INITIALIZE, GetId());
    AddPendingEvent(send);
}

MissCoreFrame::~MissCoreFrame()
{
    UnbindEvent();
}

void MissCoreFrame::BindEvent()
{
    Bind(wxEVT_INITIALIZE, &MissCoreFrame::OnInitWindow, this);

    Bind(wxEVT_TIMER, &MissCoreFrame::OnTimer, this);
    Bind(wxEVT_CLOSE_WINDOW, &MissCoreFrame::OnClose, this);
    Bind(wxEVT_HOTKEY, &MissCoreFrame::OnHotKey, this);

}

void MissCoreFrame::UnbindEvent()
{
    Unbind(wxEVT_TIMER, &MissCoreFrame::OnTimer, this);
    Unbind(wxEVT_CLOSE_WINDOW, &MissCoreFrame::OnClose, this);
    Unbind(wxEVT_HOTKEY, &MissCoreFrame::OnHotKey, this);
}


void MissCoreFrame::OnInitWindow( wxEvent& event )
{
    ///断开初始化信号
    Unbind(wxEVT_INITIALIZE, &MissCoreFrame::OnInitWindow, this);

    ///初始化插件
    InitPlugin();

    ///加载小工具
    MissWidgetManager::Instance().LoadRunWidget();

    ///开始时钟
    m_pImpl->pMainTimer->Start(1000);

}

void MissCoreFrame::InitPlugin()
{
    MissPluginManager::Instance().LoadPlugin();
}

void MissCoreFrame::OnHotKey( wxKeyEvent& event )
{
    MissHotKeyManager::Instance().RunFuncFromHotKey(event.GetId());
}

void MissCoreFrame::OnClose( wxCloseEvent& event )
{
    ///TODO: 保存数据
    MissWidgetManager::Instance().SaveRunWidget();

//     for (wxWindowList::compatibility_iterator it = wxTopLevelWindows.GetFirst();
//         it; )

    ///关闭所有功能
    MissPluginManager::Instance().ClosePluginAll();

    ///关闭窗口
    wxWindowList& list = GetChildren();
    while(!list.IsEmpty())
    {
        delete list[0];
    }

    ///卸载所有插件
    MissPluginManager::Instance().UnloadDllALL();

    ///关闭程序
    //Destroy();
     wxApp::GetInstance()->ExitMainLoop();
}

void MissCoreFrame::OnTimer( wxTimerEvent& event )
{
    MissTimerManager::Instance().TimeUp();
}

