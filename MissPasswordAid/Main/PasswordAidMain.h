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

class PasswordAidDialog: public GUIDialog
{
    public:
        PasswordAidDialog(wxWindow *dlg);
        ~PasswordAidDialog();

    private:
        //virtual void OnClose(wxCloseEvent& event);
        //virtual void OnQuit(wxCommandEvent& event);
        virtual void OnBtnGenerateClick( wxCommandEvent& event ) ;
};
#endif // PASSWORDAIDMAIN_H
