#ifndef IMPLMISSHOTKEY_H
#define IMPLMISSHOTKEY_H

#include "MissAPI\interface\IMissHotKeyMgr.h"

class MissPluginBase;

class ImplMissHotKeyMgr : public IMissHotKeyMgr
{
    public:
        ImplMissHotKeyMgr(MissPluginBase* pPlugMain);
        virtual ~ImplMissHotKeyMgr();

        virtual bool RegHotKeys(const HotKeyMajorSet& vecHotKey, MissHotKeyFuncBase* pFunc);
        virtual bool UnRegHotKeys( MissHotKeyFuncBase* pFunc );

    protected:
    private:
        MissPluginBase* m_pPlugMain;
};

#endif // IMPLMISSHOTKEY_H
