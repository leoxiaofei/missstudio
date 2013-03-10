#ifndef _CUSTOMID_H__
#define _CUSTOMID_H__

#include <wx\defs.h>


namespace DTD
{
    enum CustomId
    {
        CI_MENU_BEGIN        = wxID_HIGHEST,
        CI_CORE_OPTION,
        CI_PLUGIN_OPTION,
        CI_WIDGET_OPTION,
        CI_ABOUT,
        CI_MENU_END          = CI_MENU_BEGIN + 500,

        ///����˵���ʼID
        CI_PLUGIN_MENU_BEGIN,
        CI_PLUGIN_MENU_END   = CI_PLUGIN_MENU_BEGIN + 2000,

        ///�ȼ���ʼID
        CI_HOTKEY_ID_BEGIN,
        CI_HOTKEY_ID_END     = CI_HOTKEY_ID_BEGIN + 2000,
    };
}

// enum 
// {
//     ///�ȼ���ʼID
//     CI_HOTKEY_ID_BEGIN = 0,
//     CI_HOTKEY_ID_END   = 0xBFFF
// };

#endif // CustomId_h__