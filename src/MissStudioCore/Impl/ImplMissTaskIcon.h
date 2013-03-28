#ifndef IMPLMISSTASKBARICON_H
#define IMPLMISSTASKBARICON_H

#include "MissAPI/interface/IMissTaskIcon.h"

class MissTaskBarIcon;
class MissPluginBase;

class ImplMissTaskIcon : public IMissTaskIcon
{
public:
    ImplMissTaskIcon(MissTaskBarIcon* pIcon, MissPluginBase* pPlugMain);
    ~ImplMissTaskIcon();
    bool ShowBalloon(  const wxString &strMsg,
                         int iconID = 0x00000001,
                         unsigned int timeout = 3000);

private:
    MissTaskBarIcon* m_pIcon;
    MissPluginBase* m_pPlugMain;
};

#endif
