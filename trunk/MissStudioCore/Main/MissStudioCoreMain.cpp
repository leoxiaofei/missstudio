/***************************************************************
 * Name:      MissStudioCoreMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    leoxiaofei (xxffsoft@163.com)
 * Created:   2012-01-21
 * Copyright: leoxiaofei (http://www.leoxiaofei.com)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "../wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "MissStudioCoreMain.h"
#include "MissHotKeyFrame.h"
#include "../Widget/MissTaskBarIcon.h"
#include "../BLL/MissHotKeyManager.h"
#include "../BLL/MissPluginManager.h"
#include "../../MissTools/MissConfigFile.h"
#include "../../MissAPI/plugin/MissPluginBase.h"

#include <wx/dir.h>

#include <iostream>

DEFINE_LOCAL_EVENT_TYPE(wxEVT_INITIALIZE);

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


MissStudioCoreFrame::MissStudioCoreFrame(wxFrame *frame)
    : GUIFrame(frame),
    m_pTaskBarIcon(new MissTaskBarIcon),
    m_pHotKeyManager(new MissHotKeyManager(this)),
    m_pMainTimer(new wxTimer(this))
{
    m_pTaskBarIcon->SetIcon(wxICON(RC_STUDIO_ICON), wxT("迷失工作室"));

    ///初始化事件
    InitEvent();

    ///启动定时器
    m_pMainTimer->Start(1000);

    ///发送一个初始化窗口消息
    wxCommandEvent send(wxEVT_INITIALIZE, GetId());
    AddPendingEvent(send);
}

MissStudioCoreFrame::~MissStudioCoreFrame()
{
}

void MissStudioCoreFrame::InitEvent()
{
    this->Connect(wxEVT_TIMER, wxTimerEventHandler(MissStudioCoreFrame::OnTimer));
    this->Connect(wxEVT_INITIALIZE, wxCommandEventHandler(
                                    MissStudioCoreFrame::OnInitWindow), NULL, this);
    m_pTaskBarIcon->Connect(wxEVT_TASKBAR_RIGHT_UP, wxMouseEventHandler(
                                    MissStudioCoreFrame::OnRightUp), NULL, this);
    //m_pTaskBarIcon->Connect(wxEVT_TASKBAR_LEFT_UP, (wxObjectEventFunction)&MissStudioCoreFrame::OnTaskBarIconLeftUP, NULL, this);
}

void MissStudioCoreFrame::InitPlugin()
{
    wxString diraddr = wxT("Plugin\\");
    wxDir dir(diraddr);
    if (dir.IsOpened())
    {
        wxString filename;
        bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
        while (cont)
        {
            MissPluginManager::GetInstance().LoadDll(diraddr + filename, this);
            cont = dir.GetNext(&filename);
        }
    }
}

void MissStudioCoreFrame::OnInitWindow(wxCommandEvent& event)
{
    wxString strPath = wxGetCwd() + wxT("\\plugin\\MissPluginTest.dll");
    InitPlugin();
}

void MissStudioCoreFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void MissStudioCoreFrame::OnTimer(wxTimerEvent& event)
{
}

void MissStudioCoreFrame::OnMenuHotKeySettingSelection(wxCommandEvent& event)
{
    MissHotKeyFrame* hotkey = new MissHotKeyFrame(this, m_pHotKeyManager.get());
    hotkey->Show();
}

void MissStudioCoreFrame::OnMenuAboutSelection(wxCommandEvent& event)
{
}

void MissStudioCoreFrame::OnMenuExitSelection(wxCommandEvent& event)
{
    ExitApp();
}

void MissStudioCoreFrame::OnHotKey(wxKeyEvent& event)
{
    int nID = event.GetId();
    if(nID >999)
    {
        m_pHotKeyManager->RunFuncFromHotKey(event.GetId());
    }
    //std::cout<<event.GetId()<<std::endl;
}

void MissStudioCoreFrame::OnRightUp(wxMouseEvent& event)
{
    Raise();
    PopupMenu(m_mnuMain);
}


void MissStudioCoreFrame::ExitApp()
{
    wxCloseEvent send(wxEVT_CLOSE_WINDOW);
    AddPendingEvent(send);
}

IMissTaskIcon* MissStudioCoreFrame::GetTaskIcon()
{
    return m_pTaskBarIcon.get();
}

IMissHotKey* MissStudioCoreFrame::GetHotKey()
{
    return m_pHotKeyManager.get();
}

std::tr1::shared_ptr<IMissConfig> MissStudioCoreFrame::GetConfig(MissPluginBase* pPlugin)
{
    std::tr1::shared_ptr<IMissConfig> conf(new MissConfigFile(wxT("config\\") + pPlugin->GetPlugInfo().strPluginName +wxT(".ini")));
    return conf;
}
