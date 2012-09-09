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
#include "MissWidgetFrame.h"
#include "../Widget/MissTaskBarIcon.h"
#include "../BLL/MissPluginManager.h"
#include "../BLL/MissHotKeyManager.h"
#include "../BLL/MissWidgetManager.h"
#include "../../MissTools/MissConfigFile.h"
#include "../../MissAPI/plugin/MissTimerFuncBase.h"
#include "../Widget/MissWidget.h"

#include <wx/dir.h>
#include <wx/wxsqlite3.h>
#include <algorithm>

#include <iostream>

//#include "../MissWidgetFunc.h"

DEFINE_LOCAL_EVENT_TYPE(wxEVT_INITIALIZE);

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

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
      m_pMainTimer(new wxTimer(this))
{
    MissPluginManager::Instance().Init(this);

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
            MissPluginManager::Instance().LoadDll(diraddr + filename, this);
            cont = dir.GetNext(&filename);
        }
    }
}

void MissStudioCoreFrame::InitAboutMenu()
{
    std::vector<wxString> vecNames;
    MissPluginManager::Instance().GetPluginNameList(vecNames);

    for(std::vector<wxString>::const_iterator citor = vecNames.begin();
        citor != vecNames.end(); ++citor)
    {
        wxMenuItem* item = new wxMenuItem( m_mnuPluginAbout, wxID_ANY, *citor , wxEmptyString, wxITEM_NORMAL );
        m_mnuPluginAbout->Append(item);
        this->Connect( item->GetId(), wxEVT_COMMAND_MENU_SELECTED,
                      wxCommandEventHandler( MissStudioCoreFrame::OnMenuPluginAboutSelection ) );
    }
}

void MissStudioCoreFrame::OnInitWindow(wxCommandEvent& event)
{
    //wxString strPath = wxGetCwd() + wxT("\\plugin\\MissPluginTest.dll");
    InitPlugin();
    InitAboutMenu();
}

void MissStudioCoreFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void MissStudioCoreFrame::OnTimer(wxTimerEvent& event)
{
    std::cout<<"OnTimer"<<std::endl;
    m_ttNow = time(NULL);
    m_tmNow = localtime(&m_ttNow);
    static int s_savemin = m_tmNow->tm_min;

    ///秒钟定时器
    for(std::vector<MissTimerFuncBase*>::iterator itor = m_vecSecUp.begin();
            itor != m_vecSecUp.end(); ++itor)
    {
        (*itor)->TimeUp(m_tmNow,MTT_SEC);
    }

    ///分钟定时器
    if (s_savemin != m_tmNow->tm_min)
    {
        s_savemin = m_tmNow->tm_min;
        for(std::vector<MissTimerFuncBase*>::iterator itor = m_vecMinUp.begin();
                itor != m_vecMinUp.end(); ++itor)
        {
            (*itor)->TimeUp(m_tmNow,MTT_MIN);
        }
    }
}

void MissStudioCoreFrame::OnMenuHotKeySettingSelection(wxCommandEvent& event)
{
    MissHotKeyFrame* hotkey = new MissHotKeyFrame(this);
    hotkey->Show();
    //hotkey->Move( 100, 100);
}

void MissStudioCoreFrame::OnMenuWidgetsSettingSelection(wxCommandEvent& event)
{
    MissWidgetFrame* widget = new MissWidgetFrame(this);
    widget->Show();
}

void MissStudioCoreFrame::OnMenuAboutSelection(wxCommandEvent& event)
{
    MissStudioAbout* about = new MissStudioAbout(this);
    about->ShowModal();
}

void MissStudioCoreFrame::OnMenuPluginAboutSelection(wxCommandEvent& event)
{
    MissStudioAbout* about = new MissStudioAbout(this);
    about->ShowModal();
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
        MissPluginManager::Instance().GetHotKeyManager().RunFuncFromHotKey(event.GetId());
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

MissTaskBarIcon* MissStudioCoreFrame::GetTaskIcon()
{
    return m_pTaskBarIcon.get();
}

void MissStudioCoreFrame::RegSecTimer(MissTimerFuncBase* pPlugin)
{
    std::vector<MissTimerFuncBase*>::iterator itor =
        std::find(m_vecSecUp.begin(),m_vecSecUp.end(),pPlugin);
    if(itor == m_vecSecUp.end())
    {
        m_vecSecUp.push_back(pPlugin);
    }
}

void MissStudioCoreFrame::RegMinTimer(MissTimerFuncBase* pPlugin)
{
    std::vector<MissTimerFuncBase*>::iterator itor =
        std::find(m_vecMinUp.begin(),m_vecMinUp.end(),pPlugin);
    if(itor == m_vecMinUp.end())
    {
        m_vecMinUp.push_back(pPlugin);
    }
}
