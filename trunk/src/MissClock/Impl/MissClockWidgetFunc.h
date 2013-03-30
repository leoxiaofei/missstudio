#ifndef MISSCLOCKWIDGETFUNC_H__
#define MISSCLOCKWIDGETFUNC_H__

#include "MissAPI\plugin\MissWidgetFuncBase.h"

class MissSkin;

class MissClockWidgetFunc : public MissWidgetFuncBase
{
public:
    MissClockWidgetFunc(const std::tr1::shared_ptr<MissSkin>& pSkin);
    ~MissClockWidgetFunc();

    virtual void UpdateUI();

    void UpdateUI(const tm* tmNow);

    unsigned int GetRunID() const;

protected:
    virtual void SetWidgetPara( const CustomPara& para );
    virtual void GetWidgetParas( CustomPara& para ) const;
    virtual void PreClose();

private:
    std::tr1::shared_ptr<MissSkin> m_pSkin;
};



#endif // MISSCLOCKWIDGETFUNC_H__
