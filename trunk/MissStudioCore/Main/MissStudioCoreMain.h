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
#include "../../MissAPI/interface/IMissMain.h"


#include "../Generated/GUIFrame.h"

class MissPluginBase;
class MissTaskBarIcon;
class MissHotKeyManager;
class MissPluginManager;
class IMissTaskIcon;
class IMissHotKey;
class wxTimer;

class MissStudioCoreFrame: public GUIFrame, public IMissMain
{
    public:
        MissStudioCoreFrame(wxFrame *frame);
        ~MissStudioCoreFrame();

        virtual void OnHotKey(wxKeyEvent& event);

    protected:
        void InitEvent();
        void InitPlugin();

    private:
        ///UI事件
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnTimer(wxTimerEvent& event);
        virtual void OnMenuHotKeySettingSelection( wxCommandEvent& event );
        virtual void OnMenuExitSelection(wxCommandEvent& event);
        virtual void OnMenuAboutSelection( wxCommandEvent& event );

        ///自定义事件
        void OnInitWindow(wxCommandEvent& event);

        ///托盘图标事件
        void OnRightUp(wxMouseEvent& event);


    private:
        shared_ptr<MissTaskBarIcon>      m_pTaskBarIcon;
        shared_ptr<MissHotKeyManager>    m_pHotKeyManager;
        shared_ptr<wxTimer>              m_pMainTimer;

    ///以下是接口实现
    public:
        virtual void           ExitApp();
        virtual IMissTaskIcon *GetTaskIcon();
        virtual IMissHotKey   *GetHotKey();
};

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_LOCAL_EVENT_TYPE(wxEVT_INITIALIZE, -1)
END_DECLARE_EVENT_TYPES()
#endif // MISSSTUDIOCOREMAIN_H
