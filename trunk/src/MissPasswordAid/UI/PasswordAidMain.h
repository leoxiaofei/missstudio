/***************************************************************
 * Name:      PasswordAidMain.h
 * Purpose:   Defines Application Frame
 * Author:    leoxiaofei (fox88324@yahoo.com.cn)
 * Created:   2012-01-11
 * Copyright: leoxiaofei (http://www.leoxiaofei.com)
 * License:
 **************************************************************/

#ifndef PASSWORDAIDMAIN_H
#define PASSWORDAIDMAIN_H

#include "../Generated/GUIDialog.h"
#include <memory>

class PasswordAidDialog: public GUIDialog
{
	class Impl;
public:
	PasswordAidDialog(wxWindow *dlg);
	~PasswordAidDialog();

private:
	virtual void OnCheckAutoCloseBox( wxCommandEvent& event ) ;
	virtual void OnCheckShowPassBox( wxCommandEvent& event ) ;
	virtual void OnBtnGenerateClick( wxCommandEvent& event ) ;
	virtual void OnPasswordTextEnter( wxCommandEvent& event );

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};
#endif // PASSWORDAIDMAIN_H
