/***************************************************************
 * Name:      MissStudioCoreApp.cpp
 * Purpose:   Code for Application Class
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

#include "MissStudioCoreApp.h"
#include "MissStudioCoreMain.h"

#include <wx/filename.h>
#include <wx/dir.h>

#include <mSystem.hpp>

#include "../DAL/MissWidgetsDAL.h"

IMPLEMENT_APP(MissStudioCoreApp);

bool MissStudioCoreApp::OnInit()
{
    wxSetWorkingDirectory(Miss::GetAppExePath());
    wxImage::AddHandler( new wxPNGHandler );
    if(!wxDir::Exists(wxT("config")))
    {
        wxFileName::Mkdir(wxT("config"));
    }

    MissStudioCoreFrame* frame = new MissStudioCoreFrame(0L);
    frame->SetIcon(wxICON(RC_STUDIO_ICON)); // To Set App Icon
    //frame->Show();

    return true;
}