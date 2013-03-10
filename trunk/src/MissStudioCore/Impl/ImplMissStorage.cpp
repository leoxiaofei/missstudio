#include "ImplMissStorage.h"

#include "MissTools\MissConfigFile.h"
#include "..\BLL\MissPluginManager.h"

#include <wx\file.h>
#include <wx\wxsqlite3.h>


ImplMissStorage::ImplMissStorage(MissPluginBase* pPlugMain)
: m_pPlugMain(pPlugMain)
{
}


ImplMissStorage::~ImplMissStorage(void)
{
}

std::tr1::shared_ptr<wxFile> ImplMissStorage::GetCustomFile( const wxString& strName )
{
    wxString strPath;
    MissPluginManager::Instance().GetPluginConfigPath(m_pPlugMain, strPath);
    std::tr1::shared_ptr<wxFile> pt(new wxFile(strPath + strName, wxFile::read_write));
    return pt;
}

std::tr1::shared_ptr<MissConfigFile> ImplMissStorage::GetConfigFile( const wxString& strName )
{
    wxString strPath;
    MissPluginManager::Instance().GetPluginConfigPath(m_pPlugMain, strPath);
    std::tr1::shared_ptr<MissConfigFile> pt(new MissConfigFile(strPath + strName));
    return pt;
}


std::tr1::shared_ptr<wxSQLite3Database> ImplMissStorage::GetDBFile( const wxString& strName )
{
    wxString strPath;
    MissPluginManager::Instance().GetPluginConfigPath(m_pPlugMain, strPath);
    std::tr1::shared_ptr<wxSQLite3Database> pt(new wxSQLite3Database());
    pt->Open(strPath + strName);
    return pt;
}

