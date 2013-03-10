/***************************************************************
 * Name:      MissStudioCoreApp.cpp
 * Purpose:   Code for Application Class
 * Author:    leoxiaofei (xxffsoft@163.com)
 * Created:   2012-01-21
 * Copyright: leoxiaofei (http://www.leoxiaofei.com)
 * License:
 **************************************************************/

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "MissCoreApp.h"
#include "MissCoreFrame.h"

#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/image.h>
#include "../BLL/MissCoreConfig.h"

//#include <mSystem.hpp>


IMPLEMENT_APP(MissStudioCoreApp);

wxFrame* wxAppFrame;

bool MissStudioCoreApp::OnInit()
{
    //wxSetWorkingDirectory(Miss::GetAppExePath());
    wxImage::AddHandler( new wxPNGHandler );
    //_CrtSetBreakAlloc(9129);

    MissCoreConfig::Instance().Init();
    wxAppFrame = new MissCoreFrame;
	//wxAppFrame->Show();
    return true;
}
