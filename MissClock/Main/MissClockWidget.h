#ifndef MISSWIDGETFUNC_H
#define MISSWIDGETFUNC_H

#include "../../MissAPI/plugin/MissWidgetFuncBase.h"

class MissSkin;

class MissClockWidget : public MissWidgetFuncBase
{
    public:
        MissClockWidget(MissPluginBase* pPlugin);
        virtual ~MissClockWidget();

        void LoadSkin();
    ///接口实现
    public:
        virtual void InitWidget(wxFrame* pWidget);
        virtual void UpdateUI(wxDC &dc, const tm* tmNow);
        virtual wxSize GetSize();

    protected:
    private:
        shared_ptr<MissSkin> m_pSkin;
};

#endif // MISSWIDGETFUNC_H
