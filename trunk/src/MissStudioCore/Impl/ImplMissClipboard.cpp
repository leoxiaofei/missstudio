#include "ImplMissClipboard.h"
#include "..\BLL\MissClipboardManager.h"

ImplMissClipboard::ImplMissClipboard(MissPluginBase* pPlugMain)
: m_pPlugMain(pPlugMain)
{

}

ImplMissClipboard::~ImplMissClipboard()
{

}

void ImplMissClipboard::RegNotify( MissNotifyBase* pBase )
{
	MissClipboardManager::Instance().RegNotify(pBase);
}

void ImplMissClipboard::UnRegNotify( void* method, void* handler )
{
	MissClipboardManager::Instance().UnRegNotify(method, handler);
}

