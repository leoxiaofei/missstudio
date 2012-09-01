#ifndef IMPLMISSHOTKEY_H
#define IMPLMISSHOTKEY_H

#include "../../MissAPI/interface/IMissHotKey.h"

class MissPluginBase;
class ImplMissHotKey : public IMissHotKey
{
    public:
        ImplMissHotKey(MissPluginBase* pPlugMain);
        virtual ~ImplMissHotKey();

        bool RegHotKeys(const HotKeyDataSet& vecHotKey,
                                MissHotKeyFuncBase* pChild);
    protected:
    private:
        MissPluginBase* m_pPlugMain;
};

#endif // IMPLMISSHOTKEY_H
