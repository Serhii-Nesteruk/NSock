#pragma once

#include "Ws.h"

template<Ws::IsSockAddr _SockAddr = sockaddr_in>
class Socket
{
private:
	using SocketType = Ws::Socket::SocketType;
public:
	Socket() = default;
	Socket(const Ws::AddressType& addressType, const SocketType& socketType,
		_SockAddr sockAddr, SOCKET descriptor);
	Socket(const Ws::AddressType& addressType, const SocketType& socketType);
	Socket(const Ws::AddressType& addressType, const SocketType& socketType,
		_SockAddr& address, bool shouldBind = false, bool shouldConnect = false);
	Socket(const Socket&) = delete;
	Socket& operator=(const Socket&) = delete;
	Socket& operator=(Socket&& other);
	Socket(Socket&& other);
	~Socket();

	void bind(_SockAddr& address);
	void create();
	void create(const Ws::AddressType& addressType, const SocketType& socketType);
	void close();
	void listen(int backlog = SOMAXCONN);
	void connect(_SockAddr& address);
	Socket accept();

	void setAddressType();
	void setSocketType(const SocketType& socketType);
	void setAddress(const _SockAddr sockAddr);

	[[nodiscard]] bool wasCreated() const;
	[[nodiscard]] bool wasBound() const;
	[[nodiscard]] bool alreadyListening() const;
	[[nodiscard]] bool alreadyConnected() const;

	[[nodiscard]] SOCKET getDescriptor() const;
private:
	void zeroingData(Socket& sock);
private:
	bool _wasCreated{ false };
	bool _wasBound{ false };
	bool _alreadyConnected{ false };
	bool _alreadyListening{ false };
	SOCKET _sockDescriptor{ INVALID_SOCKET };
	Ws::AddressType _addressType = Ws::AddressType::None;
	SocketType _socketType = SocketType::UNDEFINED;
	_SockAddr _address;
};

#include "Socket.inl"