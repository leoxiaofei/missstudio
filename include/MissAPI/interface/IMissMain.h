#ifndef IMISSMAIN_H
#define IMISSMAIN_H

#include "../MissApiDef.h"
#include <memory>
#include <wx/string.h>

class wxFrame;

enum IF_TYPE
{
    IF_TIMER,
    IF_STORAGE,
    IF_HOTKEY,
	IF_SHAREDMEMORY,
	IF_CLIPBOARD,
    IF_WIDGETMANAGER,
    IF_NETWORK,
};


INTERFACE_BEGIN(IMissMain)

IDEF( void     ExitApp()             )
IDEF( wxString GetPluginPath() const )
IDEF( wxFrame* GetMainFrame()  const )

TDEF( std::tr1::shared_ptr<T> QueryIF(IF_TYPE eType) )
{
    return std::tr1::dynamic_pointer_cast<T>(GetInterfacePtr(eType));
}

PDEF( std::tr1::shared_ptr<IMissUnknown> GetInterfacePtr(IF_TYPE eType)   )

INTERFACE_END


#endif // IMISSMAIN_H
