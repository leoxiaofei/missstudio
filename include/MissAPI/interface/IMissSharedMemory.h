#ifndef IMISSSHAREDMEMORY_H__
#define IMISSSHAREDMEMORY_H__

#include "../MissApiDef.h"

class MissSharedMemoryBase;
class wxString;

INTERFACE_BEGIN(IMissSharedMemory)
    IDEF( void RegSharedMemory(MissSharedMemoryBase* pPlugin)     )
    IDEF( void UnRegSharedMemory(MissSharedMemoryBase* pPlugin)   )
    IDEF( bool GetSharedMemory(wxString& strMemory) const         )
    IDEF( bool SetSharedMemory(const wxString& strMemory)         )
INTERFACE_END

#endif // IMISSSHAREDMEMORY_H__
