/***************************************************************
 * Name:      MissStudioCoreMain.h
 * Purpose:   Defines Application Frame
 * Author:    leoxiaofei (xxffsoft@163.com)
 * Created:   2012-01-21
 * Copyright: leoxiaofei (http://www.leoxiaofei.com)
 * License:
 **************************************************************/

#ifndef MISSSTUDIOCOREMAIN_H
#define MISSSTUDIOCOREMAIN_H

#include "MissStudioCoreApp.h"

#include "../Generated/GUIFrame.h"

class MissPluginBase;
class MissTaskBarIcon;
class MissHotKeyManager;
class MissPluginManager;
class MissWidgetManager;
class MissTimerFuncBase;
class IMissHotKey;
class IMissWidget;
class wxTimer;

class MissStudioCoreFrame: public GUIFrame
{
public:
    MissStudioCoreFrame(wxFrame *frame);
    ~MissStudioCoreFrame();

    virtual void OnHotKey(wxKeyEvent& event);

protected:
    void InitEvent();
    void InitPlugin();
    void InitAboutMenu();

private:
    ///UI事件
    virtual void OnClose(wxCloseEvent& event);
    virtual void OnTimer(wxTimerEvent& event);
    virtual void OnMenuHotKeySettingSelection( wxCommandEvent& event );
    virtual void OnMenuWidgetsSettingSelection( wxCommandEvent& event );
    virtual void OnMenuExitSelection(wxCommandEvent& event);
    virtual void OnMenuAboutSelection( wxCommandEvent& event );
    virtual void OnMenuPluginAboutSelection( wxCommandEvent& event );

    ///自定义事件
    void OnInitWindow(wxCommandEvent& event);

    ///托盘图标事件
    void OnRightUp(wxMouseEvent& event);

private:
    tm                              *m_tmNow;
    time_t                           m_ttNow;

private:
    shared_ptr<MissTaskBarIcon>      m_pTaskBarIcon;
    shared_ptr<wxTimer>              m_pMainTimer;

    std::vector<MissTimerFuncBase*>  m_vecSecUp;
    std::vector<MissTimerFuncBase*>  m_vecMinUp;

    ///以下是接口实现
public:
    virtual void           ExitApp();
    MissTaskBarIcon       *GetTaskIcon();
    virtual void RegSecTimer(MissTimerFuncBase* pPlugin);
    virtual void RegMinTimer(MissTimerFuncBase* pPlugin);
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_LOCAL_EVENT_TYPE(wxEVT_INITIALIZE, -1)
END_DECLARE_EVENT_TYPES()
#endif // MISSSTUDIOCOREMAIN_H
