#include "TCPSocket.h"

template<Ws::IsSockAddr _SockAddr>
TCPSocket<_SockAddr>::TCPSocket(const Ws::AddressType& addressType, const Address<_SockAddr>& socketAddress,
	SOCKET descriptor)
	: Socket<_SockAddr>(addressType, Ws::Socket::SocketType::STREAM, socketAddress.getSockAddress(), descriptor),
	  _socketAddress(socketAddress)
{
}

template<Ws::IsSockAddr _SockAddr>
TCPSocket<_SockAddr>::TCPSocket(const Ws::AddressType& addressType,
	Address<_SockAddr>& socketAddress,
	bool shouldBind,
	bool shouldConnect)
	: Socket<_SockAddr>(addressType,
	Ws::Socket::SocketType::STREAM,
	socketAddress.getSockAddress(),
	shouldBind,
	shouldConnect), _socketAddress(socketAddress)
{
}

template<Ws::IsSockAddr _SockAddr>
TCPSocket<_SockAddr>::TCPSocket(TCPSocket&& other) : Socket<_SockAddr>(other)
{
	if (this != &other)
	{
		this->_socketAddress = Address();
		_socketAddress = other._socketAddress;
		other._socketAddress = Address();
	}
}

template<Ws::IsSockAddr _SockAddr>
TCPSocket<_SockAddr>::~TCPSocket()
{
	this->close();
	_socketAddress = Address();
}

template<Ws::IsSockAddr _SockAddr>
void TCPSocket<_SockAddr>::send(const Socket<_SockAddr>& sock, const std::string& data)
{
	int messageSize = data.size();
	Ws::Socket::send(sock.getDescriptor(), reinterpret_cast<const char*>(&messageSize));
	Ws::Socket::send(sock.getDescriptor(), data.data());
}

template<Ws::IsSockAddr _SockAddr>
std::string TCPSocket<_SockAddr>::received()
{
	int messageSize = 0;
	Ws::Socket::recv(this->getDescriptor(), reinterpret_cast<char*>(&messageSize), sizeof(messageSize));
	std::string recvMessage{ };
	recvMessage.resize(messageSize);
	Ws::Socket::recv(this->getDescriptor(), recvMessage.data(), messageSize);
	return recvMessage;
}
