#include "MissClipboardManager.h"

#include "MissAPI\callback\MissNotifyBase.h"
#include "..\Common\MissFuncFinder.hpp"

#include <vector>
#include <algorithm>

using std::vector;

class MissClipboardManager::Impl
{
public:
	vector<MissNotifyBase*>         vecNotify;
	MissFuncFinder<MissNotifyBase>  funcFinder;

};

MissClipboardManager::MissClipboardManager()
: m_pImpl(new Impl)
{

}

MissClipboardManager::~MissClipboardManager()
{

}

void MissClipboardManager::RegNotify( MissPluginBase* pPlugMain, MissNotifyBase* pBase )
{
	vector<MissNotifyBase*>::iterator iFind = 
		std::find_if(m_pImpl->vecNotify.begin(), m_pImpl->vecNotify.end(), 
		FindSameNotify(pBase));
	if (iFind == m_pImpl->vecNotify.end())
	{
		m_pImpl->funcFinder.RegPluginFunc(pPlugMain, pBase);
		m_pImpl->vecNotify.push_back(pBase);
	}
	else
	{
		delete pBase;
	}
}

void MissClipboardManager::UnRegNotify( void* method, void* handler )
{
	vector<MissNotifyBase*>::iterator iFind = 
		std::find_if(m_pImpl->vecNotify.begin(), m_pImpl->vecNotify.end(), 
		FindSameNotify(method, handler));
	if (iFind != m_pImpl->vecNotify.end())
	{
		m_pImpl->funcFinder.UnRegPluginFunc(*iFind);
		delete *iFind;
		m_pImpl->vecNotify.erase(iFind);
	}
}

void MissClipboardManager::UnRegNotify( MissNotifyBase* pBase )
{
	vector<MissNotifyBase*>::iterator iFind = 
		std::find(m_pImpl->vecNotify.begin(), m_pImpl->vecNotify.end(), pBase);
	if (iFind != m_pImpl->vecNotify.end())
	{
		m_pImpl->funcFinder.UnRegPluginFunc(*iFind);
		delete *iFind;
		m_pImpl->vecNotify.erase(iFind);
	}
}

void MissClipboardManager::Notify()
{
	for (vector<MissNotifyBase*>::const_iterator citor = m_pImpl->vecNotify.begin();
		citor != m_pImpl->vecNotify.end(); ++citor)
	{
		(**citor)();
	}
}

bool MissClipboardManager::UnloadPlugin( MissPluginBase* pPluginBase )
{
	std::vector<MissNotifyBase*> vecFunc;
	m_pImpl->funcFinder.QueryFuncByPlugin(pPluginBase, vecFunc);
	for (std::vector<MissNotifyBase*>::size_type ix = 0; ix != vecFunc.size(); ++ix)
	{
		UnRegNotify(vecFunc[ix]);
	}
	return true;
}

