#ifndef MISSCLOCKWIDGETFUNC_H__
#define MISSCLOCKWIDGETFUNC_H__

#include "MissAPI\plugin\MissWidgetFuncBase.h"

class MissSkin;

class MissClockWidgetFunc : public MissWidgetFuncBase
{
public:
    MissClockWidgetFunc(const std::tr1::shared_ptr<MissSkin>& pSkin);
    ~MissClockWidgetFunc();

    void UpdateUI(const tm* tmNow);

protected:
    virtual void SetWidgetPara( const CustomPara& para );
    virtual void GetWidgetParas( CustomPara& para );
    virtual void PreClose();

private:
    std::tr1::shared_ptr<MissSkin> m_pSkin;
};



#endif // MISSCLOCKWIDGETFUNC_H__
