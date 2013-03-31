#ifndef IMISSSHAREDMEMORY_H__
#define IMISSSHAREDMEMORY_H__

#include "../MissApiDef.h"

class MissSharedMemoryBase;
class wxVariant;
class wxString;

INTERFACE_BEGIN(IMissSharedMemory)
    IDEF( void RegSharedMemory(const wxString& strMemoryName, MissSharedMemoryBase* pPlugin)     )
    IDEF( void UnRegSharedMemory(const wxString& strMemoryName, MissSharedMemoryBase* pPlugin)   )
    IDEF( bool GetVariant(const wxString& strMemoryName, wxVariant& varData)                     )
    IDEF( bool SetVariant(const wxString& strMemoryName, const wxVariant& varData)               )

INTERFACE_END

#endif // IMISSSHAREDMEMORY_H__
