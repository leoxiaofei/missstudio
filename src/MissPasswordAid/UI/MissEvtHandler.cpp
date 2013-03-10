#include "MissEvtHandler.h"
#include "PasswordAidMain.h"
#include "MissAutoInputThread.h"

class MissEvtHandler::Impl
{
public:
    Impl() 
    : pAidDlg(NULL)
    , pThread(NULL) {}

    PasswordAidDialog* pAidDlg;
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
    PasswordAidDialog* pAidDlg = m_pImpl->pAidDlg;
    if (pAidDlg == NULL)
    {
        pAidDlg = new PasswordAidDialog(NULL);
        m_pImpl->pAidDlg = pAidDlg;
        pAidDlg->Bind(wxEVT_CLOSE_WINDOW, &MissEvtHandler::AidDlgClosed, this);
        pAidDlg->Show();
    }
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

void MissEvtHandler::AidDlgClosed( wxCloseEvent& event )
{
    PasswordAidDialog* pAidDlg = m_pImpl->pAidDlg;
    if (pAidDlg != NULL)
    {
        pAidDlg->Unbind(wxEVT_CLOSE_WINDOW, &MissEvtHandler::AidDlgClosed, this);
        pAidDlg->Destroy();
        m_pImpl->pAidDlg = NULL;
    }
}

void MissEvtHandler::InputThreadFinished( wxThreadEvent& event )
{
    m_pImpl->pThread = NULL;
}
