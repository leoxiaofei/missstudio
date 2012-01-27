#ifndef IMISSHOTKEY_H
#define IMISSHOTKEY_H

#include <vector>
class MissHotKeyFuncBase;

struct SHotKey
{
    wxString strDescription;
    wxString strHotKey;
};

class IMissHotKey
{
    public:
        virtual ~IMissHotKey() {}

        virtual bool RegHotKeys(const std::vector<SHotKey>& vecHotKey,
                                MissHotKeyFuncBase* pChild) = 0;

    protected:
    private:
};

#endif // IMISSHOTKEY_H
