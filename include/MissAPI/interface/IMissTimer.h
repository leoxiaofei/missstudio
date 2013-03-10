#ifndef IMISSTIMER_H
#define IMISSTIMER_H

#include "../MissApiDef.h"

class MissTimerFuncBase;

INTERFACE_BEGIN(IMissTimer)

IDEF( void RegSecTimer(MissTimerFuncBase* pPlugin)      )
IDEF( void RegMinTimer(MissTimerFuncBase* pPlugin)      )
IDEF( void UnRegSecTimer(MissTimerFuncBase* pPlugin)    )
IDEF( void UnRegMinTimer(MissTimerFuncBase* pPlugin)    )


INTERFACE_END

#endif // IMISSTIMER_H
