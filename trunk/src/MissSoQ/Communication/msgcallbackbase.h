#ifndef MSGCALLBACKBASE_H__
#define MSGCALLBACKBASE_H__

#include <string>

class MsgCallBackBase
{
public:
	virtual ~MsgCallBackBase(){}
	virtual void ReceiveData(void* szData, unsigned int uPacketBytes, 
		const std::string& addr, unsigned short portNo) = 0;
};

#endif // MSGCALLBACKBASE_H__
