#ifndef MISSTIMERMANAGER_H__
#define MISSTIMERMANAGER_H__

#include <memory>

class MissPluginBase;
class MissTimerFuncBase;

enum MissTimerType {MTT_SEC, MTT_MIN};

class MissTimerManager
{
    class Impl;
public:
    static MissTimerManager& Instance()
    {
        static MissTimerManager theSingleton;
        return theSingleton;
    }

    bool UnloadPlugin(MissPluginBase* pPluginBase);

    bool RegTimer(MissPluginBase* pPluginBase, int nType, MissTimerFuncBase* pFunc);
    bool UnRegTimer(int nType, MissTimerFuncBase* pFunc);
    void TimeUp();

protected:
    bool FindTimerFunc(MissTimerFuncBase* pFunc) const;

private:
    MissTimerManager();
    ~MissTimerManager();
    MissTimerManager(const MissTimerManager&);
    MissTimerManager& operator=(const MissTimerManager&);

private:
    std::tr1::shared_ptr<Impl> m_pImpl;
};


#endif // MissTimerManager_h__
