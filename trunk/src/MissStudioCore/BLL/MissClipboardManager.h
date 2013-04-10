#ifndef MISSCLIPBOARDMANAGER_H__
#define MISSCLIPBOARDMANAGER_H__

#include <memory>

class MissNotifyBase;

class MissClipboardManager
{
	class Impl;
public:
	static MissClipboardManager& Instance()
	{
		static MissClipboardManager theSingleton;
		return theSingleton;
	}

	void Notify();

	void RegNotify  ( MissNotifyBase* pBase );
	void UnRegNotify( void* method, void* handler );

private:
	MissClipboardManager();
	~MissClipboardManager();
	MissClipboardManager(const MissClipboardManager&);
	MissClipboardManager& operator=(const MissClipboardManager&);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};

#endif // MISSCLIPBOARDMANAGER_H__
