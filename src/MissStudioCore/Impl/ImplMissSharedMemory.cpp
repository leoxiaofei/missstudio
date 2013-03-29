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

bool ImplMissSharedMemory::operator=( const wxVariant& varData )
{
    return false;
}

bool ImplMissSharedMemory::operator()( wxVariant& varData )
{
    return false;
}
