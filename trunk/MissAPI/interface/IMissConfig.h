#ifndef IMISSCONFIG_H
#define IMISSCONFIG_H

#include "../MissApiDef.h"

INTERFACE_BEGIN(IMissConfig)

IDEF( bool Write(const wxString& key, const wxString& value) )
IDEF( bool Write(const wxString& key, long value) )
IDEF( bool Write(const wxString& key, double value) )
IDEF( bool Write(const wxString& key, bool value) )

IDEF( bool Read(const wxString& key, wxString& value) const )
IDEF( bool Read(const wxString& key, long& value) const )
IDEF( bool Read(const wxString& key, double& value) const )
IDEF( bool Read(const wxString& key, bool& value) const )

INTERFACE_END

#endif // IMISSCONFIG_H
