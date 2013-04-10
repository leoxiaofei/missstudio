#include "MissClipboardManager.h"

#include "MissAPI\callback\MissNotifyBase.h"

#include <vector>
#include <algorithm>

using std::vector;

class MissClipboardManager::Impl
{
public:
	vector<MissNotifyBase*> vecNotify;

};

MissClipboardManager::MissClipboardManager()
: m_pImpl(new Impl)
{

}

MissClipboardManager::~MissClipboardManager()
{

}

void MissClipboardManager::RegNotify( MissNotifyBase* pBase )
{
	vector<MissNotifyBase*>::iterator iFind = 
		std::find_if(m_pImpl->vecNotify.begin(), m_pImpl->vecNotify.end(), 
		FindSameNotify(pBase));

	if (iFind == m_pImpl->vecNotify.end())
	{
		m_pImpl->vecNotify.push_back(pBase);
	}
}

void MissClipboardManager::UnRegNotify( void* method, void* handler )
{
	vector<MissNotifyBase*>::iterator iFind = 
		std::find_if(m_pImpl->vecNotify.begin(), m_pImpl->vecNotify.end(), 
		FindSameNotify(method, handler));

	if (iFind != m_pImpl->vecNotify.end())
	{
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

