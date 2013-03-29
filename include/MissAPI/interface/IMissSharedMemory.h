#ifndef IMISSSHAREDMEMORY_H__
#define IMISSSHAREDMEMORY_H__

#include "../MissApiDef.h"

class MissSharedMemoryBase;
class wxVariant;

INTERFACE_BEGIN(IMissSharedMemory)
    IDEF( void RegSharedMemory(MissSharedMemoryBase* pPlugin)     )
    IDEF( void UnRegSharedMemory(MissSharedMemoryBase* pPlugin)   )
    IDEF( bool operator ()(wxVariant& varData) const              )
    IDEF( bool operator = (const wxVariant& varData)              )

INTERFACE_END

#endif // IMISSSHAREDMEMORY_H__
