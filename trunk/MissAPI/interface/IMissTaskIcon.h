#ifndef IMISSTASKICON_H
#define IMISSTASKICON_H

#include "../MissApiDef.h"

INTERFACE_BEGIN(IMissTaskIcon)

IDEF( bool ShowBalloon(  const wxString &strMsg,
                         int iconID = 0x00000001,
                         unsigned int timeout = 3000) )

INTERFACE_END

#endif // IMISSTASKICON_H
