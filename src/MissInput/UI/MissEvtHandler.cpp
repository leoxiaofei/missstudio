#include "MissEvtHandler.h"
#include "MissAutoInputThread.h"
#include "../Common/MissGlobal.h"
#include "MissAPI/interface/IMissSharedMemory.h"

#include <wx/clipbrd.h>
#include <wx/frame.h>
#include <iostream>

class MissEvtHandler::Impl
{
public:
    Impl() 
	: pThread(NULL) {}

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

void MissEvtHandler::OpenAutoInput()
{
    MissAutoInputThread* pThread = m_pImpl->pThread;
    if (pThread == NULL)
    {
		wxVariant varClipbrd;
		if(std::tr1::shared_ptr<IMissSharedMemory> ptSharedMemory 
			= MissGlobal::IMain->QueryIF<IMissSharedMemory>(IF_SHAREDMEMORY))
		{
			ptSharedMemory->GetVariant(wxT("MissInput"), varClipbrd);
		}
        pThread = new MissAutoInputThread(this, varClipbrd.GetString());
        if ( pThread->Create() != wxTHREAD_NO_ERROR )
        {
            delete pThread;
            pThread = NULL;
        }
        else
        {
            if (pThread->Run() != wxTHREAD_NO_ERROR )
            {
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

void MissEvtHandler::ClipboardChanged()
{
	if (wxTheClipboard->Open())
	{
		if (wxTheClipboard->IsSupported( wxDF_TEXT ))
		{
			wxTextDataObject data;
			wxTheClipboard->GetData( data );
			if(std::tr1::shared_ptr<IMissSharedMemory> ptSharedMemory 
				= MissGlobal::IMain->QueryIF<IMissSharedMemory>(IF_SHAREDMEMORY))
			{
				ptSharedMemory->SetVariant(wxT("MissInput"), data.GetText());
			}
		}
		wxTheClipboard->Close();
	}

}
