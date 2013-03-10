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

class MissTaskBarIcon : public wxTaskBarIcon
{
public:
    /** Default constructor */
    MissTaskBarIcon();
    /** Default destructor */
    virtual ~MissTaskBarIcon();

protected:
    virtual wxMenu * CreatePopupMenu();

    void BindEvent();
    void UnbindEvent();

    void OnMenuCoreOptionSelection( wxCommandEvent& event );
    void OnMenuPluginOptionSelection( wxCommandEvent& event );
    void OnMenuWidgetsOptionSelection( wxCommandEvent& event );
    void OnMenuAboutSelection( wxCommandEvent& event );
    void OnMenuExitSelection( wxCommandEvent& event );

private:

};

#endif // MISSTASKBARICON_H
