#include "MissEvtHandler.h"
#include "PasswordAidMain.h"
#include "MissAutoInputThread.h"
#include "../Common/MissGlobal.h"
#include <wx/frame.h>
#include "MissTools/OneWinManager.h"
#include <windows.h>

class MissEvtHandler::Impl
{
public:
    Impl() 
	: winManager(MissGlobal::IMain->GetMainFrame())
	, pThread(NULL) {}

	OneWinManager winManager;
    MissAutoInputThread* pThread;
};

MissEvtHandler::MissEvtHandler()
: wxEvtHandler()
, m_pImpl(new Impl)
{
    BindEvent();
}

MissEvtHandler::~MissEvtHandler()
{
    UnbindEvent();
}

void MissEvtHandler::BindEvent()
{
    Bind(wxEVT_COMMAND_AUTOINPUT_COMPLETED, &MissEvtHandler::InputThreadFinished, this);
}

void MissEvtHandler::UnbindEvent()
{
    Unbind(wxEVT_COMMAND_AUTOINPUT_COMPLETED, &MissEvtHandler::InputThreadFinished, this);
}

void MissEvtHandler::OpenPasswordAid()
{
    PasswordAidDialog* pAidDlg = 
    m_pImpl->winManager.CreateWin<PasswordAidDialog>(wxT("PasswordAidDialog"));
	pAidDlg->Raise();
}

void MissEvtHandler::OpenAutoInput()
{
    MissAutoInputThread* pThread = m_pImpl->pThread;
    if (pThread == NULL)
    {
        pThread = new MissAutoInputThread(this);
        if ( pThread->Create() != wxTHREAD_NO_ERROR )
        {
            //wxLogError("Can't create the thread!");
            delete pThread;
            pThread = NULL;
        }
        else
        {
            if (pThread->Run() != wxTHREAD_NO_ERROR )
            {
                //wxLogError("Can't create the thread!");
                delete pThread;
                pThread = NULL;
            }
        }
        m_pImpl->pThread = pThread;
    }
}

void MissEvtHandler::InputThreadFinished( wxThreadEvent& event )
{
    m_pImpl->pThread = NULL;
}
