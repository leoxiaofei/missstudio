#include "ImplMissSharedMemory.h"
#include "..\BLL\MissMemoryManager.h"


ImplMissSharedMemory::ImplMissSharedMemory(MissPluginBase* pPlugMain)
: m_pPlugMain(pPlugMain)
{
}

ImplMissSharedMemory::~ImplMissSharedMemory()
{
}

void ImplMissSharedMemory::RegSharedMemory( const wxString& strMemoryName, MissSharedMemoryBase* pPlugin )
{
    MissMemoryManager::Instance().RegSharedMemory(m_pPlugMain, strMemoryName, pPlugin);
}

void ImplMissSharedMemory::UnRegSharedMemory( const wxString& strMemoryName, MissSharedMemoryBase* pPlugin )
{
    MissMemoryManager::Instance().UnRegSharedMemory(strMemoryName, pPlugin);
}

bool ImplMissSharedMemory::GetVariant( const wxString& strMemoryName, wxVariant& varData )
{
    return MissMemoryManager::Instance().GetVariant(m_pPlugMain, strMemoryName, varData);
}

bool ImplMissSharedMemory::SetVariant( const wxString& strMemoryName, const wxVariant& varData )
{
    return MissMemoryManager::Instance().SetVariant(m_pPlugMain, strMemoryName, varData);
}

