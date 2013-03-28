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
#include <memory>

class MissTaskBarIcon : public wxTaskBarIcon
{
	class Impl;
public:
    /** Default constructor */
    MissTaskBarIcon();
    /** Default destructor */
    virtual ~MissTaskBarIcon();

protected:
    virtual wxMenu * CreatePopupMenu();

    void BindEvent();
    void UnbindEvent();
	
	//////////////////////////////////////////////////////////////////////////
	///对话框关闭消息

	//////////////////////////////////////////////////////////////////////////
	/// 菜单信号
    void OnMenuCoreOptionSelection( wxCommandEvent& event );
    void OnMenuPluginOptionSelection( wxCommandEvent& event );
    void OnMenuWidgetsOptionSelection( wxCommandEvent& event );
    void OnMenuAboutSelection( wxCommandEvent& event );
    void OnMenuExitSelection( wxCommandEvent& event );


private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // MISSTASKBARICON_H
