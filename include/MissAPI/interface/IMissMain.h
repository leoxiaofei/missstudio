#ifndef IMISSMAIN_H
#define IMISSMAIN_H

#include "../MissApiDef.h"
#include <memory>
#include <wx/string.h>

// class IMissTaskIcon;
// class IMissHotKey;
// class IMissWidgetManager;
// class IMissConfig;
// class MissPluginBase;
// class wxSQLite3Database;

enum IF_TYPE
{
    IF_TIMER,
    IF_STORAGE,
    IF_HOTKEY,
    IF_WIDGETMANAGER,
    IF_SQLITE3DATABASE
};


INTERFACE_BEGIN(IMissMain)

IDEF( void     ExitApp()             )
IDEF( wxString GetPluginPath() const )

TDEF( std::tr1::shared_ptr<T> QueryIF(IF_TYPE eType) )
{
    return std::tr1::dynamic_pointer_cast<T>(GetInterfacePtr(eType));
}

PDEF( std::tr1::shared_ptr<IMissUnknown> GetInterfacePtr(IF_TYPE eType)   )

// IDEF( wxString GetPluginPath()       )
// IDEF( std::tr1::shared_ptr<IMissTaskIcon>      GetTaskIcon()       )
// IDEF( std::tr1::shared_ptr<IMissHotKey>        GetHotKey()         )
// IDEF( std::tr1::shared_ptr<IMissWidgetManager> GetWidgetManager()  )
// IDEF( std::tr1::shared_ptr<IMissConfig>        GetConfig()         )
// IDEF( std::tr1::shared_ptr<wxSQLite3Database>  GetDataBase()       )

INTERFACE_END


#endif // IMISSMAIN_H
