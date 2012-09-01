#ifndef IMPLMISSMAIN_H
#define IMPLMISSMAIN_H

#include "../../MissAPI/interface/IMissMain.h"

class MissStudioCoreFrame;
class MissPluginBase;

class ImplMissMain : public IMissMain
{
    public:
        ImplMissMain(MissStudioCoreFrame* pCore, MissPluginBase* pPlugMain);
        virtual ~ImplMissMain();

        void ExitApp();
        void RegSecTimer(MissTimerFuncBase* pPlugin);
        void RegMinTimer(MissTimerFuncBase* pPlugin);
        wxString GetPluginPath();

        std::tr1::shared_ptr<IMissTaskIcon>      GetTaskIcon();
        std::tr1::shared_ptr<IMissHotKey>        GetHotKey();
        std::tr1::shared_ptr<IMissWidgetManager> GetWidgetManager();
        std::tr1::shared_ptr<IMissConfig>        GetConfig();
        std::tr1::shared_ptr<wxSQLite3Database>  GetDataBase();

    protected:
    private:
        MissStudioCoreFrame* m_pCore;
        MissPluginBase*      m_pPlugMain;

};

#endif // IMPLMISSMAIN_H
