#ifndef MISSMAINENTRY_H__
#define MISSMAINENTRY_H__

#include "MissAPI\interface\IMissMain.h"


class MissPluginBase;
class MissMainEntry;

class MissMainEntry : public IMissMain
{
    class Impl;
public:
    MissMainEntry(MissPluginBase* pPlugMain);
    ~MissMainEntry(void);

    virtual void ExitApp();
    virtual wxString GetPluginPath() const;

protected:
    virtual std::tr1::shared_ptr<IMissUnknown> GetInterfacePtr( IF_TYPE eType );

private:
    IMissUnknown* CreateHotKey();
    IMissUnknown* CreateStorage();
    IMissUnknown* CreateTimer();
    IMissUnknown* CreateWidgetMgr();



private:
    MissPluginBase* m_pPlugMain;
};

#endif // MissMainEntry_h__
