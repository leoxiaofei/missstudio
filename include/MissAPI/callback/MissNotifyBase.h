#ifndef MISSNOTIFYBASE_H__
#define MISSNOTIFYBASE_H__

class MissNotifyBase
{
public:
	MissNotifyBase(void* method, void* handler)
		: m_method(method)
		, m_handler(handler) {}

	virtual void operator () () = 0;

protected:
	void* m_method;
	void* m_handler;

	friend class FindSameNotify;
};

class FindSameNotify
{
public:
	FindSameNotify(MissNotifyBase* pBase)
		: m_method(pBase->m_method)
		, m_handler(pBase->m_handler) {}

	FindSameNotify(void* method, void* handler)
		: m_method(method)
		, m_handler(handler) {}

	bool operator()(const MissNotifyBase* pBase) const
	{
		return pBase->m_method == m_method && 
			pBase->m_handler == m_handler;
	}

private:
	void* m_method;
	void* m_handler;
};

template <typename T>   
inline void* FunToVoid(T func)   
{   
	return *(void **)&func;   
}

template <typename T>   
inline T VoidToFun(void* p)   
{   
	return *(T *)&p;   
}

#endif // MISSNOTIFYBASE_H__
