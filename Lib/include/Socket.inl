#include "Socket.h"

template<Ws::IsSockAddr _SockAddr>
Socket<_SockAddr>::Socket(const Ws::AddressType& addressType, const SocketType& socketType,
	_SockAddr& sockAddr, SOCKET descriptor)
	: _addressType(addressType), _socketType(socketType), _address(sockAddr)
{
	if (descriptor == INVALID_SOCKET)
	{
		this->create();
	}
	else
	{
		_sockDescriptor = descriptor;
		_wasCreated = true;
	}
}

template<Ws::IsSockAddr _SockAddr>
Socket<_SockAddr>::Socket(const Ws::AddressType& addressType, const Ws::Socket::SocketType& socketType)
	: _addressType(addressType), _socketType(socketType)
{
	this->create();
}

template<Ws::IsSockAddr _SockAddr>
Socket<_SockAddr>::Socket(Socket<_SockAddr>&& other)
{
	this->operator=(std::move(other));
}

template<Ws::IsSockAddr _SockAddr>
Socket<_SockAddr>& Socket<_SockAddr>::operator=(Socket<_SockAddr>&& other)
{
	if (this != &other)
	{
		zeroingData(*this);
		_wasCreated = other._wasCreated;
		_wasBound = other._wasBound;
		_alreadyListening = other._alreadyListening;
		_alreadyConnected = other._alreadyConnected;
		_sockDescriptor = other._sockDescriptor;
		_addressType = other._addressType;
		_socketType = other._socketType;
		_address = other._address;
		zeroingData(other);
	}
	return *this;
}

template<Ws::IsSockAddr _SockAddr>
void Socket<_SockAddr>::zeroingData(Socket<_SockAddr>& sock)
{
	sock._wasCreated = false;
	sock._wasBound = false;
	sock._alreadyListening = false;
	sock._alreadyConnected = false;
	sock._sockDescriptor = INVALID_SOCKET;
	sock._addressType = Ws::AddressType::None;
	sock._socketType = SocketType::UNDEFINED;
	sock._address = _SockAddr();
}

template<Ws::IsSockAddr _SockAddr>
Socket<_SockAddr>::Socket(const Ws::AddressType& addressType,
	const Ws::Socket::SocketType& socketType, _SockAddr& address, bool shouldBind, bool shouldConnect)
	: _addressType(addressType), _socketType(socketType), _address(address)
{
	this->create();
	if (shouldBind && !shouldConnect)
	{
		this->bind(address);
	}
	if (shouldConnect && !shouldBind)
	{
		this->connect(address);
	}
}

template<Ws::IsSockAddr _SockAddr>
Socket<_SockAddr>::~Socket()
{
	this->close();
}

template<Ws::IsSockAddr _SockAddr>
void Socket<_SockAddr>::create()
{
	if (_addressType == Ws::AddressType::None)
	{
		throw std::runtime_error("address type cannot be empty");
	}
	if (_socketType == SocketType::UNDEFINED)
	{
		throw std::runtime_error("socket type cannot be empty");
	}
	if (wasCreated())
	{
		throw std::runtime_error("Socket has already been created");
	}
	_sockDescriptor = Ws::Socket::create(_addressType, _socketType);
	_wasCreated = true;
}

template<Ws::IsSockAddr _SockAddr>
void Socket<_SockAddr>::create(const Ws::AddressType& addressType, const SocketType& socketType)
{
	if (wasCreated())
	{
		throw std::runtime_error("Socket has already been created");
	}
	_sockDescriptor = Ws::Socket::create(addressType, socketType);
	_wasCreated = true;
}

template<Ws::IsSockAddr _SockAddr>
void Socket<_SockAddr>::bind(_SockAddr& address)
{
	if (!wasCreated())
	{
		throw std::runtime_error("You can't bind the socket. Socket was not created by");
	}
	if (wasBound())
	{
		throw std::runtime_error("You can't bind the socket. Socket was not bound");
	}
	Ws::Socket::bind(_sockDescriptor, reinterpret_cast<sockaddr*>(&address));
	_wasBound = true;
}

template<Ws::IsSockAddr _SockAddr>
void Socket<_SockAddr>::listen(int backlog)
{
	if (alreadyListening())
	{
		throw std::runtime_error("Socket is already listening");
	}
	Ws::Socket::listen(_sockDescriptor, backlog);
	_alreadyListening = true;
}

template<Ws::IsSockAddr _SockAddr>
bool Socket<_SockAddr>::wasCreated() const
{
	return _wasCreated;
}

template<Ws::IsSockAddr _SockAddr>
void Socket<_SockAddr>::close()
{
	if (!wasCreated())
	{
		throw std::runtime_error("You can't close socket. Socket was not created");
	}
	Ws::Socket::closeSocket(_sockDescriptor);
	// zeroingData(*this); TODO: If you do not comment this line, the program will crash. Fix it
}

template<Ws::IsSockAddr _SockAddr>
bool Socket<_SockAddr>::wasBound() const
{
	return _wasBound;
}

template<Ws::IsSockAddr _SockAddr>
bool Socket<_SockAddr>::alreadyListening() const
{
	return _alreadyListening;
}

template<Ws::IsSockAddr _SockAddr>
SOCKET Socket<_SockAddr>::getDescriptor() const
{
	return _sockDescriptor;
}

template<Ws::IsSockAddr _SockAddr>
void Socket<_SockAddr>::setAddress(const _SockAddr sockAddr)
{
	if (wasCreated())
	{
		throw std::runtime_error("The socket already has an address. You can't change it");
	}
	if (wasBound())
	{
		throw std::runtime_error("The socket already has an address. You can't change it");
	}
	_address = sockAddr;
}

template<Ws::IsSockAddr _SockAddr>
void Socket<_SockAddr>::setSocketType(const SocketType& socketType)
{
	if (wasBound())
	{
		throw std::runtime_error("The socket already has an address. You can't change it");
	}
	_socketType = socketType;
}

template<Ws::IsSockAddr _SockAddr>
Socket<_SockAddr> Socket<_SockAddr>::accept()
{
	_SockAddr tempSockAddr;
	SOCKET tempDescriptor = Ws::Socket::accept(_sockDescriptor, reinterpret_cast<sockaddr*>(&tempSockAddr));
	Socket tempSocket(_addressType, _socketType, tempSockAddr, tempDescriptor);
	return tempSocket;
}

template<Ws::IsSockAddr _SockAddr>
void Socket<_SockAddr>::connect(_SockAddr& address)
{
	if (!wasCreated())
	{
		throw std::runtime_error("Connection failed. Socket was not created");
	}
	if (alreadyConnected())
	{
		throw std::runtime_error("Connection failed. Socket already connected");
	}
	Ws::Socket::connect(_sockDescriptor, reinterpret_cast<sockaddr*>(&address));
	_alreadyConnected = true;
}

template<Ws::IsSockAddr _SockAddr>
bool Socket<_SockAddr>::alreadyConnected() const
{
	return _alreadyConnected;
}