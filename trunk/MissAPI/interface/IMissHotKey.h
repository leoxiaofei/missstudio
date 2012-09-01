#ifndef IMISSHOTKEY_H
#define IMISSHOTKEY_H

#include <vector>
#include "../MissApiDef.h"

class MissHotKeyFuncBase;

struct SHotKeyData
{
    int      nID;
    wxString strFuncName;    ///功能名
    wxString strFuncDesc;    ///功能描述
    wxString strHotKey;      ///功能快捷键
};

typedef std::vector<SHotKeyData> HotKeyDataSet;


INTERFACE_BEGIN(IMissHotKey)

IDEF( bool RegHotKeys(const HotKeyDataSet& vecHotKey,
            MissHotKeyFuncBase* pChild) )

INTERFACE_END

#endif // IMISSHOTKEY_H
