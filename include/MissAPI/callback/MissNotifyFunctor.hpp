#ifndef MISSNOTIFYFUNCTOR_H__
#define MISSNOTIFYFUNCTOR_H__

#include "MissNotifyBase.h"

template <class Class>
class MissNotifyFunctor : public MissNotifyBase
{
public:
	typedef void (Class::*Func)();
	MissNotifyFunctor(Func method, Class* handler)
	: MissNotifyBase(FunToVoid(method), handler){}

	virtual void operator()()
	{
		((Class*)m_handler->*(VoidToFun<Func>(m_method)))();
	}
};

#endif // MISSNOTIFYFUNCTOR_H__

