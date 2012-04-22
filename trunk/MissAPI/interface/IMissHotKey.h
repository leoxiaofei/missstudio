#ifndef IMISSHOTKEY_H
#define IMISSHOTKEY_H

#include <vector>
class MissHotKeyFuncBase;

struct SHotKeyData
{
    wxString strFuncName;    ///功能名
    wxString strFuncDesc;    ///功能描述
    wxString strHotKey;      ///功能快捷键
};

class IMissHotKey
{
    public:
        virtual ~IMissHotKey() {}

        virtual bool RegHotKeys(const std::vector<SHotKeyData>& vecHotKey,
                                MissHotKeyFuncBase* pChild) = 0;

    protected:
    private:
};

#endif // IMISSHOTKEY_H
