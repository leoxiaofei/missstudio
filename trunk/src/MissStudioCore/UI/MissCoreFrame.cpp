#include "MissCoreFrame.h"

#include "../BLL/MissHotKeyManager.h"
#include "../BLL/MissPluginManager.h"
#include "../BLL/MissTimerManager.h"
#include "../BLL/MissWidgetManager.h"
#include "../BLL/MissClipboardManager.h"
#include "../BLL/MissExtendManager.h"
#include "../UI/MissTaskBarIcon.h"

#include <wx/dir.h>
#include <wx/event.h>
#include <wx/menu.h>
#include <wx/string.h>
#include <wx/timer.h>
#include <wx/socket.h>
#include <wx/window.h>
#include <wx/app.h>

#include <iostream>

using std::tr1::shared_ptr;

wxDEFINE_EVENT(wxEVT_INITIALIZE, wxEvent);

class MissCoreFrame::Impl
{
public:
	shared_ptr<MissTaskBarIcon> pTrayIcon;
    shared_ptr<wxTimer>         pMainTimer;
	HWND                        hwndNextViewer;

    void SetupUi(wxFrame* parent);

};

void MissCoreFrame::Impl::SetupUi( wxFrame* parent )
{
    wxIcon icon = wxICON(RC_STUDIO_ICON);
    parent->SetIcon(icon); // To Set App Icon

    pTrayIcon = shared_ptr<MissTaskBarIcon>(new MissTaskBarIcon(parent));
    pTrayIcon->SetIcon(icon, wxT("��ʧ������"));

    pMainTimer = shared_ptr<wxTimer>(new wxTimer(parent));
}


MissCoreFrame::MissCoreFrame()
: wxFrame(0, wxID_ANY, wxT("��ʧ������"))
, m_pImpl(new Impl)
{
    m_pImpl->SetupUi(this);
    Center();
    BindEvent();

    ///����һ����ʼ����Ϣ
    wxCommandEvent send(wxEVT_INITIALIZE, GetId());
    wxPostEvent(this, send);
}

MissCoreFrame::~MissCoreFrame()
{
    UnbindEvent();
	DestroyMSW();
}

void MissCoreFrame::BindEvent()
{
    Bind(wxEVT_INITIALIZE, &MissCoreFrame::OnInitWindow, this);

    Bind(wxEVT_TIMER, &MissCoreFrame::OnTimer, this);
    Bind(wxEVT_CLOSE_WINDOW, &MissCoreFrame::OnClose, this);
    Bind(wxEVT_HOTKEY, &MissCoreFrame::OnHotKey, this);
	//Bind(wxEVT_SOCKET, &MissCoreFrame::OnSocket, this);
}

void MissCoreFrame::UnbindEvent()
{
    Unbind(wxEVT_TIMER, &MissCoreFrame::OnTimer, this);
    Unbind(wxEVT_CLOSE_WINDOW, &MissCoreFrame::OnClose, this);
    Unbind(wxEVT_HOTKEY, &MissCoreFrame::OnHotKey, this);
	//Unbind(wxEVT_SOCKET, &MissCoreFrame::OnSocket, this);
}


void MissCoreFrame::OnInitWindow( wxEvent& event )
{
    ///�Ͽ���ʼ���ź�
    Unbind(wxEVT_INITIALIZE, &MissCoreFrame::OnInitWindow, this);

	///��ʼ����չ
	MissExtendManager::Instance().LoadPlugin();

    ///��ʼ�����
	MissPluginManager::Instance().LoadPlugin();

    ///����С����
    MissWidgetManager::Instance().LoadRunWidget();

	///��ʼ������WinAPIʵ�ֵĹ���
	InitMSW();

    ///��ʼʱ��
    m_pImpl->pMainTimer->Start(1000);

}


void MissCoreFrame::OnHotKey( wxKeyEvent& event )
{
    MissHotKeyManager::Instance().RunFuncFromHotKey(event.GetId());
}

void MissCoreFrame::OnClose( wxCloseEvent& event )
{
    ///TODO: ��������
    MissWidgetManager::Instance().SaveRunWidget();

    ///�ر����й���
    MissPluginManager::Instance().ClosePluginAll();

    ///�رմ���
    wxWindowList& list = GetChildren();
    while(!list.IsEmpty())
    {
        delete list[0];
    }

    ///ж�����в��
    MissPluginManager::Instance().UnloadDllALL();

    ///�رճ���
    //Destroy();
    wxApp::GetInstance()->ExitMainLoop();
}

void MissCoreFrame::OnTimer( wxTimerEvent& event )
{
    MissTimerManager::Instance().TimeUp();
}

void MissCoreFrame::InitMSW()
{
	m_pImpl->hwndNextViewer = ::SetClipboardViewer(GetHWND());
}

void MissCoreFrame::DestroyMSW()
{
	::ChangeClipboardChain(GetHWND(), m_pImpl->hwndNextViewer);
}

WXLRESULT MissCoreFrame::MSWWindowProc( WXUINT message, WXWPARAM wParam, WXLPARAM lParam )
{
	switch (message)
	{
	case WM_CHANGECBCHAIN:
		if ((HWND) wParam == m_pImpl->hwndNextViewer)
		{
			m_pImpl->hwndNextViewer = (HWND)lParam; 
		}
		else if (m_pImpl->hwndNextViewer != NULL) 
		{
			::SendMessage(m_pImpl->hwndNextViewer, message, wParam, lParam); 
		}
		break;
	case WM_DRAWCLIPBOARD:
		MissClipboardManager::Instance().Notify();
		break;
	default:
		break;
	}
	return wxFrame::MSWWindowProc(message, wParam, lParam);
}

// void MissCoreFrame::OnSocket( wxSocketEvent& event )
// {
// }
// 
