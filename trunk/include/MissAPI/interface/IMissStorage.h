#ifndef IMISSCONFIG_H
#define IMISSCONFIG_H

#include "../MissApiDef.h"

class MissConfigFile;
class wxFile;
class wxSQLite3Database;
class wxString;

#include <memory>

INTERFACE_BEGIN(IMissStorage)

IDEF( std::tr1::shared_ptr<wxFile>            GetCustomFile(const wxString& strName) )
IDEF( std::tr1::shared_ptr<MissConfigFile>    GetConfigFile(const wxString& strName) )
IDEF( std::tr1::shared_ptr<wxSQLite3Database> GetDBFile(const wxString& strName) )


INTERFACE_END

#endif // IMISSCONFIG_H
