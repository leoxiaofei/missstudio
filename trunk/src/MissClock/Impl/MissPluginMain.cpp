#include "MissPluginMain.h"

#include <vector>

#include "MissAPI/interface/IMissMain.h"
#include "MissAPI/interface/IMissHotKeyMgr.h"
#include "MissAPI/interface/IMissStorage.h"
#include "MissAPI/interface/IMissWidgetMgr.h"
#include "MissWidgetFactory.h"
#include "../Common/MissGlobal.h"


using std::tr1::shared_ptr;

class MissPluginMain::Impl
{
public:
    shared_ptr<MissWidgetFactory> pWidgetFactory;
};

MissPluginMain::MissPluginMain()
: MissPluginBase()
, m_pImpl(new Impl)
{
    //ctor
}

MissPluginMain::~MissPluginMain()
{
    //dtor
}

void MissPluginMain::LoadPlugin()
{
    MissGlobal::IMain = GetMain();
    if (shared_ptr<IMissWidgetMgr> pt = GetMain()->QueryIF<IMissWidgetMgr>(IF_WIDGETMANAGER))
    {
        m_pImpl->pWidgetFactory = shared_ptr<MissWidgetFactory>(new MissWidgetFactory);
        WidgetMajorSet widgetSet(1);
        widgetSet[0].nWidgetId = MissWidgetFactory::WT_CLOCK;
        pt->RegWidgetFactory(m_pImpl->pWidgetFactory.get(), widgetSet);
    }
}

void MissPluginMain::UnloadPlugin()
{
}

bool MissPluginMain::GetPlugInfo( SPlugInfo& info ) const
{
    info.strPluginName = wxT("√‘ ß◊¿√Ê ±÷”");
    info.strVersion = wxT("1.0.0");
    info.strSpecification = wxT("");
    info.strAuthor = wxT("leoxiaofei");
    info.strEmail = wxT("xxffsoft@163.com");
    info.strWeb = wxT("http://www.leoxiaofei.com");
    return true;
}

wxString MissPluginMain::GetPluginName() const
{
    return wxT("√‘ ß◊¿√Ê ±÷”");
}

wxString MissPluginMain::GetPluginGUID() const
{
    return wxT("DAD2F0D0-3C45-49EF-933D-0680C5D8471D");
}

