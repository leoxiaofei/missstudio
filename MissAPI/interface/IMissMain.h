#ifndef IMISSMAIN_H
#define IMISSMAIN_H

#include <tr1/memory>

class IMissTaskIcon;
class IMissHotKey;
class IMissConfig;
class MissPluginBase;

class IMissMain
{
    public:
        virtual ~IMissMain() {}
        virtual void ExitApp() = 0;
        virtual IMissTaskIcon *GetTaskIcon() = 0;
        virtual IMissHotKey   *GetHotKey()   = 0;
        virtual std::tr1::shared_ptr<IMissConfig> GetConfig(MissPluginBase* pPlugin) = 0;

    protected:
    private:
};

#endif // IMISSMAIN_H
