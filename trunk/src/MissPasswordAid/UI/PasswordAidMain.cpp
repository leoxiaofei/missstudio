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
#include "MissAutoInputThread.h"
#include "../Encrypt/ProcPwCore.h"
#include "../Common/MissGlobal.h"

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
    int nLen           = m_spLen->GetValue();
    int nVersion       = m_spVersion->GetValue();
    int nType          = m_cboxPassType->GetCurrentSelection();
    wxString strPW     = m_edtPassword->GetValue();
    wxCharBuffer bufIn = strPW.mb_str();
    wxCharBuffer bufOut(nLen);
    ProcPwCore pwCore(nLen, nVersion, static_cast<ProcPwCore::PWTYPE>(nType));
    pwCore.StartProc(bufIn.data(),strlen(bufIn.data()),bufOut.data(),nLen);
    MissGlobal::strClipbrd = wxString(bufOut.data(), wxConvLocal);
    if(m_cboxShowPass->GetValue())
    {
        m_edtOut->SetValue(MissGlobal::strClipbrd);
    }
    if(m_cboxAutoClose->GetValue())
    {
        //SetReturnCode(wxID_OK);
        Close();
    }
}

void PasswordAidDialog::OnCheckAutoCloseBox(wxCommandEvent& event)
{
}

void PasswordAidDialog::OnCheckShowPassBox(wxCommandEvent& event)
{
    bool bShow = event.IsChecked();
    m_edtOut->Show(bShow);
    if(bShow)
    {
        m_edtOut->SetValue(MissGlobal::strClipbrd);
    }
    Layout();
}

void PasswordAidDialog::OnPasswordTextEnter( wxCommandEvent& event )
{
    OnBtnGenerateClick(event);
}
