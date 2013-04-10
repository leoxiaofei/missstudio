#ifndef IMISSCLIPBOARD_H__
#define IMISSCLIPBOARD_H__

#include "../MissApiDef.h"
#include "../callback/MissNotifyFunctor.hpp"

class MissNotifyBase;

INTERFACE_BEGIN(IMissClipboard)

	TDEF( void RegNotify(void (T::*method)(), T* handler)  )
	{
		RegNotify(new MissNotifyFunctor<T>(method, handler));
	}

    TDEF( void UnRegNotify(void (T::*method)(), T* handler) )
	{
		UnRegNotify(FunToVoid(method), handler);
	}

	PDEF( void RegNotify(MissNotifyBase* pBase));
	PDEF( void UnRegNotify(void* method, void* handler));

INTERFACE_END

#endif // IMISSCLIPBOARD_H__
