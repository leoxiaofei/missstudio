#ifndef IMISSHOTKEY_H
#define IMISSHOTKEY_H

#include "../MissApiDef.h"

#include <wx/string.h>
#include <vector>

class MissHotKeyFuncBase;

struct SHotKeyMajor
{
    int      nFuncId;        ///���ܱ�ʶ��
    bool     bEnable;        ///�Ƿ�����
    wxString strHotKey;      ///��ݼ�
};

typedef std::vector<SHotKeyMajor> HotKeyMajorSet;


INTERFACE_BEGIN(IMissHotKeyMgr)

IDEF( bool RegHotKeys(const HotKeyMajorSet& vecHotKeys, MissHotKeyFuncBase* pFunc) )
IDEF( bool UnRegHotKeys(MissHotKeyFuncBase* pFunc) )

INTERFACE_END

#endif // IMISSHOTKEY_H
