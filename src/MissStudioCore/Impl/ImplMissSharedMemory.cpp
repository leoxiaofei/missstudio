#include "ImplMissSharedMemory.h"


ImplMissSharedMemory::ImplMissSharedMemory(MissPluginBase* pPlugMain)
: m_pPlugMain(pPlugMain)
{
}

ImplMissSharedMemory::~ImplMissSharedMemory()
{
}

void ImplMissSharedMemory::RegSharedMemory( MissSharedMemoryBase* pPlugin )
{
}

void ImplMissSharedMemory::UnRegSharedMemory( MissSharedMemoryBase* pPlugin )
{
}

bool ImplMissSharedMemory::GetSharedMemory( wxString& strMemory ) const
{
    return false;
}

bool ImplMissSharedMemory::SetSharedMemory( const wxString& strMemory )
{
    return false;
}
