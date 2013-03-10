#pragma once

#include "MissAPI/interface/IMissStorage.h"

class MissPluginBase;

class ImplMissStorage : public IMissStorage
{
public:
    ImplMissStorage(MissPluginBase* pPlugMain);
    ~ImplMissStorage(void);

    virtual std::tr1::shared_ptr<wxFile> GetCustomFile( const wxString& strName );
    virtual std::tr1::shared_ptr<MissConfigFile> GetConfigFile( const wxString& strName );
    virtual std::tr1::shared_ptr<wxSQLite3Database> GetDBFile( const wxString& strName );

private:
    MissPluginBase* m_pPlugMain;
};

