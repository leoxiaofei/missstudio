#include "MissWidgetFuncMgr.h"
#include <vector>

using std::vector;
using std::pair;
using std::tr1::shared_ptr;

class MissWidgetFuncMgr::Impl
{
public:
    vector<pair<shared_ptr<MissWidgetFuncBase>, shared_ptr<MissTimerFuncBase> > > vecData;


};

MissWidgetFuncMgr::MissWidgetFuncMgr()
: m_pImpl(new Impl)
{
}

MissWidgetFuncMgr::~MissWidgetFuncMgr()
{
}

void MissWidgetFuncMgr::SaveFunc( const std::tr1::shared_ptr<MissWidgetFuncBase>& pFunc,
                                 const std::tr1::shared_ptr<MissTimerFuncBase>& pRefreash )
{
    m_pImpl->vecData.push_back(std::make_pair(pFunc, pRefreash));
}
