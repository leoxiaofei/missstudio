#ifndef MISSWIDGETFACTORY_H__
#define MISSWIDGETFACTORY_H__

#include "MissAPI\plugin\MissWidgetFactoryBase.h"
#include <memory>

class IMissMain;

class MissWidgetFactory : public MissWidgetFactoryBase
{
public:
    MissWidgetFactory();
    virtual ~MissWidgetFactory() {};

    enum WIDGET_TYPE { WT_CLOCK };

    virtual MissWidgetFuncBase* CreateWidgetFunc( int nWidgetId );
    virtual void CreateSuccessed( MissWidgetFuncBase* pWidgetFunc );
    virtual void GetWidgetName( int nWidgetId, wxString& strWidgetName );

private:

};



#endif // MissWidgetFactory_h__
