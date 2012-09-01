#ifndef IMISSWIDGET_H
#define IMISSWIDGET_H

#include "../MissApiDef.h"
//class MissWidgetFuncBase;
//class MissTimerFuncBase;
//typedef MissTimerFuncBase MissWidgetUpdateFunc;
class MissWidgetFactoryBase;

INTERFACE_BEGIN(IMissWidgetManager)
        //virtual MissWidgetUpdateFunc* CreateWidget(MissWidgetFuncBase * pFunc) = 0;
IDEF( void RegWidgetFactory(MissWidgetFactoryBase* pFactory, const std::vector<wxString>& vecWidget) )

INTERFACE_END
#endif // IMISSWIDGET_H
