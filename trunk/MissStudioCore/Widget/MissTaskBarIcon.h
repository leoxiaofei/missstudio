/***************************************************************
 * Name:      MissTaskBarIcon.h
 * Purpose:   Defines Task Bar Icon
 * Author:    leoxiaofei (xxffsoft@163.com)
 * Created:   2012-01-21
 * Copyright: leoxiaofei (http://www.leoxiaofei.com)
 * License:
 **************************************************************/

#ifndef MISSTASKBARICON_H
#define MISSTASKBARICON_H

#include <wx/taskbar.h>
#include "../../MissAPI/interface/IMissTaskIcon.h"

//#define NIIF_INFO  0x00000001

class MissTaskBarIcon : public wxTaskBarIcon, public IMissTaskIcon
{
public:
    /** Default constructor */
    MissTaskBarIcon();
    /** Default destructor */
    virtual ~MissTaskBarIcon();

    bool ShowBalloon(const wxString &strTitle,
                     const wxString &strMsg,
                     int iconID = NIIF_INFO,
                     unsigned int timeout = 3000);

protected:
private:
};

#endif // MISSTASKBARICON_H
