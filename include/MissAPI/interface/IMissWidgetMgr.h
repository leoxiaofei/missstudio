#ifndef IMISSWIDGETMGR_H
#define IMISSWIDGETMGR_H

#include "../MissApiDef.h"
#include <vector>
#include <wx/string.h>

class MissWidgetFactoryBase;

struct SWidgetMajor
{
    int      nWidgetId;        ///С���߱�ʶ��
};

typedef std::vector<SWidgetMajor> WidgetMajorSet;

INTERFACE_BEGIN(IMissWidgetMgr)

IDEF( bool RegWidgetFactory(MissWidgetFactoryBase* pFactory, const WidgetMajorSet& vecWidget) )

INTERFACE_END

#endif // IMISSWIDGETMGR_H
