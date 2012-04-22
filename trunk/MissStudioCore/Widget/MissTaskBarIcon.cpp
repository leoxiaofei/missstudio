/***************************************************************
 * Name:      MissTaskBarIcon.cpp
 * Purpose:   Task Bar Icon
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


#include "MissTaskBarIcon.h"
#include <windef.h>
#include <shellapi.h>

#include <wx/frame.h>

class wxTaskBarIconWindow: public wxFrame
{
public:
    wxTaskBarIconWindow(wxTaskBarIcon* icon): wxFrame(NULL, wxID_ANY,
                wxEmptyString, wxDefaultPosition, wxDefaultSize, 0), m_icon(icon) {}

    WXLRESULT MSWWindowProc(WXUINT msg, WXWPARAM wParam, WXLPARAM lParam)
    {
        return 0;
    }
private:
    wxTaskBarIcon* m_icon;
};

MissTaskBarIcon::MissTaskBarIcon():
    wxTaskBarIcon()
{
    //ctor
}

MissTaskBarIcon::~MissTaskBarIcon()
{
    //dtor
}


bool MissTaskBarIcon::ShowBalloon(const wxString &strTitle,
                                  const wxString &strMsg,
                                  int iconID,
                                  unsigned int timeout)
{
    if (!IsOk())
    {
        return false;
    }
    ///微软规定的...又不是我。
    assert(strTitle.Length() < 64);
    assert(strMsg.Length() < 256);

    NOTIFYICONDATA notifyData;
    notifyData.cbSize = sizeof(notifyData);
    notifyData.hWnd = (HWND)m_win->GetHWND();
    notifyData.uFlags = NIF_INFO;
    wcsncpy(notifyData.szInfoTitle,strTitle.c_str(),64);
    wcsncpy(notifyData.szInfo,strMsg.c_str(),256);

    //lstrcpyn(notifyData.szInfo, strMsg.c_str(), sizeof(notifyData.szInfo));
    //lstrcpyn(notifyData.szInfoTitle, strTitle.c_str(), sizeof(notifyData.szInfoTitle));
    notifyData.dwInfoFlags = iconID; // | NIIF_NOSOUND; modified by palinx
    notifyData.uTimeout = timeout;
    notifyData.uID = 99;

    if (m_iconAdded)
    {
        return (Shell_NotifyIcon(NIM_MODIFY, &notifyData) != 0);
    }
    else
    {
        return false;
    }
}
