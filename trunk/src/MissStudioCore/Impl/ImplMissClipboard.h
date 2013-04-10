#ifndef IMPLMISSCLIPBOARD_H__
#define IMPLMISSCLIPBOARD_H__

#include "MissAPI\interface\IMissClipboard.h"

#include <memory>

class MissPluginBase;

class ImplMissClipboard : public IMissClipboard
{
	class Impl;
public:
	ImplMissClipboard(MissPluginBase* pPlugMain);
	~ImplMissClipboard();
	virtual void RegNotify( MissNotifyBase* pBase );
	virtual void UnRegNotify( void* method, void* handler );

private:
	MissPluginBase* m_pPlugMain;
};

#endif // IMPLMISSCLIPBOARD_H__
