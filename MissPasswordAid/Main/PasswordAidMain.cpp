/***************************************************************
 * Name:      PasswordAidMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    leoxiaofei (fox88324@yahoo.com.cn)
 * Created:   2012-01-11
 * Copyright: leoxiaofei (http://www.leoxiaofei.com)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "PasswordAidMain.h"
#include "ProcPwCore.h"
#include "../Common/MissGlobal.h"
#include "MissAutoInputThread.h"

//helper functions


PasswordAidDialog::PasswordAidDialog(wxWindow *dlg)
    : GUIDialog(dlg)
{

}

PasswordAidDialog::~PasswordAidDialog()
{
}

void PasswordAidDialog::OnBtnGenerateClick(wxCommandEvent& event)
{
    int nLen = m_spLen->GetValue();
    int nVersion = m_spVersion->GetValue();
    wxString strPW = m_edtPassword->GetValue();
    wxCharBuffer bufIn = strPW.mb_str();
    wxCharBuffer bufOut(nLen);
    ProcPwCore pwCore(nLen, nVersion);
    pwCore.StartProc(bufIn.data(),strlen(bufIn.data()),bufOut.data(),nLen);
    MissGlobal::strClipbrd = wxString(bufOut.data(), wxConvLocal);
    m_edtOut->SetValue(MissGlobal::strClipbrd);
    /*
    MissAutoInputThread* m_pThread = new MissAutoInputThread();
    if ( m_pThread->Create() != wxTHREAD_NO_ERROR )
        {
            wxLogError("Can't create the thread!");
            delete m_pThread;
            m_pThread = NULL;
        }
        else
        {
            if (m_pThread->Run() != wxTHREAD_NO_ERROR )
            {
                wxLogError("Can't create the thread!");
                delete m_pThread;
                m_pThread = NULL;
            }
        }
    */
    //m_edtOut->SetValue(MissGlobal::strClipbrd);
}
