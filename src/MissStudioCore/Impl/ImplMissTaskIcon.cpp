#include "ImplMissTaskIcon.h"

#include "../UI/MissTaskBarIcon.h"
#include "MissAPI/plugin/MissPluginBase.h"

ImplMissTaskIcon::ImplMissTaskIcon(MissTaskBarIcon* pIcon, MissPluginBase* pPlugMain)
: m_pIcon(pIcon)
, m_pPlugMain(pPlugMain)
{

}

ImplMissTaskIcon::~ImplMissTaskIcon()
{

}

bool ImplMissTaskIcon::ShowBalloon( const wxString &strMsg,
                                     int iconID,
                                     unsigned int timeout)
{
	return true;
    //return m_pIcon->ShowBalloon(m_pPlugMain->GetPlugInfo().strPluginName, strMsg, iconID, timeout);
}
