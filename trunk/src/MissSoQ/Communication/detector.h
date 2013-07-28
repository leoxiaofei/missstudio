#ifndef DETECTOR_H__
#define DETECTOR_H__


#include <memory>
#include <boost\asio\io_service.hpp>
#include <boost\asio\error.hpp>

class MsgCallBackBase;

class Detector
{
	class Impl;
public:
	Detector(boost::asio::io_service& io);
	~Detector(void);

	bool Listen(unsigned short sPort = 5123);

	void Broadcast(void* szData, unsigned int uSize, unsigned short uPort = 2425);
	void SendTo(void* szData, unsigned int uSize,
		const std::string& strAddr, unsigned short uPort = 2425);

	void SetCallBack(std::tr1::shared_ptr<MsgCallBackBase> pBase);


protected:
	void ReadyRead();
	void ReadHandler( const boost::system::error_code& ec, 
		std::size_t packet_bytes );

	void BroadcastHandler( const boost::system::error_code& ec);
	void SendToHandler( const boost::system::error_code& ec);

private:
	std::tr1::shared_ptr<Impl> m_pImpl;
};

#endif // DETECTOR_H__
