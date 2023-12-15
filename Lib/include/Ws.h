#pragma once

#include <WinSock2.h>
#include <string>
#include <ws2ipdef.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

namespace Ws
{
	enum class AddressType
	{
		None,
		IPv4 = AF_INET,
		IPv6 = AF_INET6
	};

	class Socket
	{
	public:
		enum class SocketType
		{
			UNDEFINED,
			DGRAM = SOCK_DGRAM,
			STREAM = SOCK_STREAM
		};

		enum class Protocol
		{
			AUTO = 0,
			TCP = IPPROTO_TCP,
			UDP = IPPROTO_UDP,
		};

		Socket() = delete;

		static SOCKET create(const AddressType& addressType,
			const SocketType& socketType,
			const Protocol& aProtocol = Protocol::AUTO);
		static void bind(SOCKET sock, sockaddr* name);
		static void listen(SOCKET sock, int backlog = SOMAXCONN);
		static void connect(SOCKET sock, sockaddr* address);
		static void send(SOCKET sock, const char* data, int flags = 0);
		static void recv(SOCKET sock, char* buf, int bufSize, int flags = 0);
		[[nodiscard]] static SOCKET accept(SOCKET sock, sockaddr* addr);

		static void closeSocket(SOCKET sock);
		[[nodiscard]] static bool isClosed(SOCKET sock);
		static bool isValid(SOCKET sock);
	};

	static void ThrowAnError();
	static void handleSocketError(SOCKET sock);

	template<class T> class SockAddr
	{
	};

	template<>
	class SockAddr<sockaddr_in>
	{
	public:
		static void setType(const AddressType& addrType, sockaddr_in& sockAddr);
		static void setPort(u_short port, sockaddr_in& sockAddr);
		static void setAddress(const std::string& address, sockaddr_in& sockAddr);
		[[nodiscard]] static std::string getAddress(const sockaddr_in& sockAddr);
		[[nodiscard]] static AddressType getAddrType();
	private:
		inline static AddressType _addrType = AddressType::IPv4;
	};

	template<>
	class SockAddr<sockaddr_in6>
	{
	public:
		static void setType(const AddressType& addrType, sockaddr_in6& sockAddr);
		static void setPort(u_short port, sockaddr_in6& sockAddr);
		static void setAddress(const std::string& address, sockaddr_in6& sockAddr);
		[[nodiscard]] static std::string getAddress(const sockaddr_in6& sockAddr);
		[[nodiscard]] static AddressType getAddrType();
	private:
		inline static AddressType _addrType = AddressType::IPv6;
	};
	using SockAddr4 = SockAddr<sockaddr_in>;
	using SockAddr6 = SockAddr<sockaddr_in6>;

	template<class T>
	concept IsSockAddr = std::is_same_v<T, sockaddr_in>;//std::is_same_v<T, SockAddr4> || std::is_same_v<T, SockAddr6>
		 // TODO: fix it
}