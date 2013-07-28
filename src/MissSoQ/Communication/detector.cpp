#include "detector.h"

#include <boost\asio\placeholders.hpp>
#include <boost\bind.hpp>
#include <boost\asio\ip\udp.hpp>

#include <thread>
#include <iostream>
#include "msgcallbackbase.h"


using namespace boost::asio;
using boost::system::error_code;
using std::tr1::shared_ptr;

class Detector::Impl
{
public:
	Impl(io_service& io)
		: ios(io)
	{}

	io_service& ios;
	shared_ptr<ip::udp::socket> ptSock;
	ip::udp::endpoint epReceive;
	std::tr1::array<char, 1024> arBuffer;

	std::tr1::shared_ptr<MsgCallBackBase> pCallBack;
};

Detector::Detector( boost::asio::io_service& io )
: m_pImpl(new Impl(io))
{
	Listen();
}

Detector::~Detector( void )
{

}

void Detector::SetCallBack( std::tr1::shared_ptr<MsgCallBackBase> pBase )
{
	m_pImpl->pCallBack = pBase;
}

bool Detector::Listen(unsigned short uPort)
{
	m_pImpl->ptSock = shared_ptr<ip::udp::socket>
		(new ip::udp::socket(m_pImpl->ios, ip::udp::endpoint(ip::udp::v4(), uPort)));
	m_pImpl->ptSock->set_option(socket_base::broadcast(true));
	m_pImpl->ptSock->set_option(ip::udp::socket::reuse_address(true));
	ReadyRead();
	return true;
}

void Detector::ReadyRead()
{
	m_pImpl->ptSock->async_receive_from(buffer(m_pImpl->arBuffer), m_pImpl->epReceive,
		boost::bind(&Detector::ReadHandler, this, placeholders::error, placeholders::bytes_transferred));
}

void Detector::ReadHandler( const boost::system::error_code& ec, std::size_t packet_bytes )
{
	if (ec)
	{
		return;
	}

	m_pImpl->arBuffer[packet_bytes] = '\0';
	std::cout<<packet_bytes<<":"<<m_pImpl->arBuffer.data()<<std::endl;
	if (m_pImpl->pCallBack)
	{
		m_pImpl->pCallBack->ReceiveData(m_pImpl->arBuffer.data(), packet_bytes,
			m_pImpl->epReceive.address().to_string(), m_pImpl->epReceive.port());
	}

	ReadyRead();
}

void Detector::Broadcast(void* szData, unsigned int uSize, unsigned short uPort)
{
// 	boost::system::error_code error;
// 	shared_ptr<ip::udp::socket> ptSocket(new ip::udp::socket(m_pImpl->ios));
// 
// 	ptSocket->open(ip::udp::v4(), error);
// 	if (!error)
// 	{
// 		ptSocket->set_option(ip::udp::socket::reuse_address(true));
// 		ptSocket->set_option(socket_base::broadcast(true));
// 
// 		ip::udp::endpoint senderEndpoint(ip::address_v4::broadcast(), uPort);
// 		//ip::udp::endpoint senderEndpoint(ip::address_v4::from_string("192.168.0.255"), 2425);
// 
// 		ptSocket->async_send_to(buffer(szData, uSize), senderEndpoint, 
// 			boost::bind(&Detector::BroadcastHandler, this, placeholders::error, ptSocket));
// 	}

	ip::udp::endpoint senderEndpoint(ip::address_v4::broadcast(), uPort);
	m_pImpl->ptSock->async_send_to(buffer(szData, uSize), senderEndpoint,
		boost::bind(&Detector::BroadcastHandler, this, placeholders::error));
}

void Detector::BroadcastHandler( const boost::system::error_code& ec)
{
}

void Detector::SendTo( void* szData, unsigned int uSize, 
					   const std::string& strAddr, unsigned short uPort /*= 2425*/ )
{
	ip::udp::endpoint senderEndpoint(ip::address_v4::from_string(strAddr), uPort);
	m_pImpl->ptSock->async_send_to(buffer(szData, uSize), senderEndpoint,
		boost::bind(&Detector::SendToHandler, this, placeholders::error));
}

void Detector::SendToHandler( const boost::system::error_code& ec )
{

}

