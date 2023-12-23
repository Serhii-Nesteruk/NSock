#pragma once

#include "Socket.h"
#include "Address.h"

template<Ws::IsSockAddr _SockAddr = sockaddr_in>
class TCPSocket : public Socket<_SockAddr>
{
public:
	TCPSocket() = default;
	TCPSocket(const Ws::AddressType& addressType, Address<_SockAddr>& socketAddress,
		bool shouldBind = false, bool shouldConnect = false);
	TCPSocket(const Ws::AddressType& addressType, const Address<_SockAddr>& socketAddress,
		SOCKET descriptor);
	~TCPSocket();

	TCPSocket(const TCPSocket&) = delete;
	TCPSocket& operator=(const TCPSocket&) = delete;

	TCPSocket(TCPSocket&& other);
	TCPSocket& operator=(TCPSocket&& other) = delete; // TODO:

	void send(const Socket<_SockAddr>& sock, const std::string& data);
	std::string received();



private:
	Address<_SockAddr> _socketAddress;
};

#include "TCPSocket.inl"