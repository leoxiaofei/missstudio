#ifndef MISSCLIPBOARDMANAGER_H__
#define MISSCLIPBOARDMANAGER_H__

#include <memory>

class MissNotifyBase;
class MissPluginBase;

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

	void RegNotify  ( MissPluginBase* pPlugMain, MissNotifyBase* pBase );
	void UnRegNotify( void* method, void* handler );
	bool UnloadPlugin(MissPluginBase* pPluginBase);

protected:
	void UnRegNotify(MissNotifyBase* pBase);

private:
	MissClipboardManager();
	~MissClipboardManager();
	MissClipboardManager(const MissClipboardManager&);
	MissClipboardManager& operator=(const MissClipboardManager&);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;

};

#endif // MISSCLIPBOARDMANAGER_H__
