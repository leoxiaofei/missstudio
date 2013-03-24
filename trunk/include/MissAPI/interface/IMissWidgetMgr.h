#ifndef IMISSWIDGETMGR_H
#define IMISSWIDGETMGR_H

#include "../MissApiDef.h"
#include <vector>
#include <wx/string.h>

class MissWidgetFactoryBase;

struct SWidgetMajor
{
    int      nWidgetId;        ///小工具标识符
};

class FindWidgetMajor
{
public:
    FindWidgetMajor(int nWidgetId) : m_nWidgetId(nWidgetId){};
    bool operator()(const SWidgetMajor& major)
    {
        return major.nWidgetId == m_nWidgetId;
    }

private:
    int m_nWidgetId;
};

typedef std::vector<SWidgetMajor> WidgetMajorSet;

INTERFACE_BEGIN(IMissWidgetMgr)

IDEF( bool RegWidgetFactory(MissWidgetFactoryBase* pFactory, const WidgetMajorSet& vecWidget) )

INTERFACE_END

#endif // IMISSWIDGETMGR_H
