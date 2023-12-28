#include "Ws.h"

#include "Utils.h"

#include <WS2tcpip.h>
#include <iostream>

bool Ws::Socket::isValid(SOCKET sock)
{
	return sock != INVALID_SOCKET;
}
void Ws::Socket::closeSocket(SOCKET sock)
{
	::closesocket(sock);
}
bool Ws::Socket::isClosed(SOCKET sock)
{
	return sock == INVALID_SOCKET;
}

void Ws::SockAddr6::setType(const Ws::AddressType& addrType, sockaddr_in6& sockAddr)
{
	if (addrType == AddressType::IPv4)
	{
		throw std::runtime_error("SockAddrIPv6 error: address type must be IPv6");
	}
	sockAddr.sin6_family = static_cast<u_short>(addrType);
	_addrType = addrType;
}

void Ws::SockAddr6::setPort(u_short port, sockaddr_in6& sockAddr)
{
	sockAddr.sin6_port = htons(port);
}

void Ws::SockAddr6::setAddress(const std::string& address, sockaddr_in6& sockAddr)
{
	inet_pton(static_cast<int>(_addrType), address.data(), &sockAddr.sin6_addr);
}

std::string Ws::SockAddr6::getAddress(const sockaddr_in6& sockAddr)
{
	std::string buff{ };
	inet_ntop(sockAddr.sin6_family, &sockAddr, buff.data(), buff.size());
	return buff;
}

Ws::AddressType Ws::SockAddr6::getAddrType()
{
	return _addrType;
}

SOCKET Ws::Socket::create(const Ws::AddressType& addressType,
	const Ws::Socket::SocketType& socketType,
	const Ws::Socket::Protocol& aProtocol)
{
	SOCKET tempSocket = ::socket(static_cast<int>(addressType), static_cast<int>(socketType),
		static_cast<int>(aProtocol));
	if (tempSocket == INVALID_SOCKET)
	{
		handleSocketError(tempSocket);
	}
	return tempSocket;
}

void Ws::ThrowAnError()
{
	int errorCode = WSAGetLastError();
	throw std::runtime_error("WSAStartup failed with error: " + std::to_string(errorCode)
		+ " Message: " + Utils::GetWinSockErrorString(errorCode));
}

void Ws::handleSocketError(SOCKET sock)
{
	ThrowAnError();
	//Socket::closeSocket(sock);
}

void Ws::SockAddr4::setType(const Ws::AddressType& addrType, sockaddr_in& sockAddr)
{
	if (addrType == AddressType::IPv6)
	{
		throw std::runtime_error("SockAddrIPv4 error: address type must be IPv4");
	}
	sockAddr.sin_family = static_cast<u_short>(addrType);
	_addrType = addrType;
}

void Ws::SockAddr4::setPort(u_short port, sockaddr_in& sockAddr)
{
	sockAddr.sin_port = htons(port);
}

void Ws::SockAddr4::setAddress(const std::string& address, sockaddr_in& sockAddr)
{
	inet_pton(static_cast<int>(_addrType), address.data(), &sockAddr.sin_addr);
}

void Ws::Socket::bind(SOCKET sock, sockaddr* name)
{
	if (::bind(sock, name, sizeof(*name)) == SOCKET_ERROR)
	{
		handleSocketError(sock);
	}
}

void Ws::Socket::listen(SOCKET sock, int backlog)
{
	if (::listen(sock, backlog) < 0)
	{
		handleSocketError(sock);
	}
}
void Ws::Socket::connect(SOCKET sock, sockaddr* address)
{
	if (::connect(sock, address, sizeof(*address)) == SOCKET_ERROR)
	{
		handleSocketError(sock);
	}
}

std::string Ws::SockAddr4::getAddress(const sockaddr_in& sockAddr)
{
	std::string buff{ };
	inet_ntop(sockAddr.sin_family, &sockAddr, buff.data(), buff.size());
	return buff;
}

SOCKET Ws::Socket::accept(SOCKET sock, sockaddr* addr)
{
	socklen_t addrLen = sizeof(*addr);
	SOCKET tempSock = ::accept(sock, addr, &addrLen);
	if (tempSock == INVALID_SOCKET)
	{
		handleSocketError(tempSock);
	}
	return tempSock;
}

void Ws::Socket::send(SOCKET sock, const char* data, int flags)
{
	int dataSize = strlen(data);
	if (::send(sock, data, dataSize, flags) == SOCKET_ERROR)
	{
		handleSocketError(sock);
	}
}

void Ws::Socket::recv(SOCKET sock, char* buf, int bufSize, int flags)
{
	int bytesRead = ::recv(sock, buf, bufSize - 1, flags);
	if (bytesRead == SOCKET_ERROR)
	{
		handleSocketError(sock);
	}
	else
	{
		buf[bytesRead] = '\0';
	}
}

void Ws::Socket::sendto(SOCKET sock, const char* message, int flags, const sockaddr* to, int tolen)
{
	int sendingResult = ::sendto(sock, message, strlen(message) + 1, flags, to, tolen);
	if (sendingResult == SOCKET_ERROR)
	{
		handleSocketError(sock);
	}
}

void Ws::Socket::recvfrom(SOCKET sock, char* buf, int len, sockaddr* from, int flags, int* fromlen)
{
	int receivingResult = ::recvfrom(sock, buf, len, flags, from, fromlen);
	if (receivingResult == SOCKET_ERROR)
	{
		handleSocketError(sock);
	}
}