#ifndef _CUSTOMID_H__
#define _CUSTOMID_H__

#include <wx\defs.h>


namespace DTD
{
    enum CustomId
    {
        ///���˵���ʼID
        CI_MENU_BEGIN        = wxID_HIGHEST,
        CI_CORE_OPTION,
        CI_PLUGIN_OPTION,
        CI_WIDGET_OPTION,
        CI_ABOUT,
        CI_MENU_END          = CI_MENU_BEGIN + 200,

        ///С���߲˵���ʼID
        CI_WIDGET_MENU_BEGIN,
        CI_WIDGET_WINDOW_OPTION,
        CI_WIDGET_SHADOW,
        CI_WIDGET_PIN,
        CI_WIDGET_ZPOS_TOP,
        CI_WIDGET_ZPOS_NORMAL,
        CI_WIDGET_ZPOS_BOTTOM,
        CI_WIDGET_OPACITY,
        CI_WIDGET_OPACITY_END = CI_WIDGET_OPACITY + 10,
        CI_WIDGET_SCALE,
        CI_WIDGET_SCALE_END = CI_WIDGET_SCALE + 10,
        CI_WIDGET_EXIT,
        CI_WIDGET_MENU_END = CI_WIDGET_MENU_BEGIN + 200,

        ///����˵���ʼID
        CI_PLUGIN_MENU_BEGIN,
        CI_PLUGIN_MENU_END   = CI_PLUGIN_MENU_BEGIN + 2000,

        ///�ȼ���ʼID
        CI_HOTKEY_ID_BEGIN,
        CI_HOTKEY_ID_END     = CI_HOTKEY_ID_BEGIN + 2000,
    };

}

#endif // CustomId_h__
