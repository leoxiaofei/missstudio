#ifndef IMISSMAIN_H
#define IMISSMAIN_H

#include <tr1/memory>

class IMissTaskIcon;
class IMissHotKey;
class IMissWidget;
class IMissConfig;
class MissPluginBase;
class MissTimerFuncBase;
class wxSQLite3Database;


class IMissMain
{
    public:
        virtual ~IMissMain() {}
        virtual void ExitApp() = 0;
        virtual IMissTaskIcon *GetTaskIcon() = 0;
        virtual IMissHotKey   *GetHotKey()   = 0;
        virtual IMissWidget   *GetWidget()   = 0;
        virtual std::tr1::shared_ptr<IMissConfig> GetConfig(MissPluginBase* pPlugin) = 0;
        virtual std::tr1::shared_ptr<wxSQLite3Database> GetDataBase(MissPluginBase* pPlugin) = 0;
        virtual void RegSecTimer(MissTimerFuncBase* pPlugin) = 0;
        virtual void RegMinTimer(MissTimerFuncBase* pPlugin) = 0;

    protected:
    private:
};

#endif // IMISSMAIN_H
