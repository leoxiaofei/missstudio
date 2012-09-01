#ifndef IMISSMAIN_H
#define IMISSMAIN_H

#include <tr1/memory>
#include "../MissApiDef.h"

class IMissTaskIcon;
class IMissHotKey;
class IMissWidgetManager;
class IMissConfig;
class MissPluginBase;
class MissTimerFuncBase;
class wxSQLite3Database;


INTERFACE_BEGIN(IMissMain)

IDEF( void ExitApp()                                               )
IDEF( void RegSecTimer(MissTimerFuncBase* pPlugin)                 )
IDEF( void RegMinTimer(MissTimerFuncBase* pPlugin)                 )
IDEF( wxString GetPluginPath()                                     )
IDEF( std::tr1::shared_ptr<IMissTaskIcon>      GetTaskIcon()       )
IDEF( std::tr1::shared_ptr<IMissHotKey>        GetHotKey()         )
IDEF( std::tr1::shared_ptr<IMissWidgetManager> GetWidgetManager()  )
IDEF( std::tr1::shared_ptr<IMissConfig>        GetConfig()         )
IDEF( std::tr1::shared_ptr<wxSQLite3Database>  GetDataBase()       )

INTERFACE_END


#endif // IMISSMAIN_H
