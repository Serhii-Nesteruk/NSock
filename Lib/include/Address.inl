#include "Address.h"

template<Ws::IsSockAddr _SockAddrIn, class _SockAddr>
Address<_SockAddrIn, _SockAddr>::Address(const Ws::AddressType& addressType, int port,
	const std::string& address)
{
	setAll(addressType, port, address);
}

template<Ws::IsSockAddr _SockAddrIn, class _SockAddr>
void Address<_SockAddrIn, _SockAddr>::setAll(const Ws::AddressType& addressType, int port, const std::string& address)
{
	setAddressType(addressType);
	setPort(port);
	setAddress(address);
}

template<Ws::IsSockAddr _SockAddrIn, class _SockAddr>
void Address<_SockAddrIn, _SockAddr>::setAddressType(const Ws::AddressType& addressType)
{
	_SockAddr::setType(addressType, _sockAddress);
	_addressType = addressType;
}

template<Ws::IsSockAddr _SockAddrIn, class _SockAddr>
void Address<_SockAddrIn, _SockAddr>::setPort(int port)
{
	_SockAddr::setPort(port, _sockAddress);
	_port = port;
}

template<Ws::IsSockAddr _SockAddrIn, class _SockAddr>
void Address<_SockAddrIn, _SockAddr>::setAddress(const std::string& address)
{
	_SockAddr::setAddress(address, _sockAddress);
	_addressStr = address;
}

template<Ws::IsSockAddr _SockAddrIn, class _SockAddr>
_SockAddrIn& Address<_SockAddrIn, _SockAddr>::getSockAddress()
{
	return _sockAddress;
}

template<Ws::IsSockAddr _SockAddrIn, class _SockAddr>
int Address<_SockAddrIn, _SockAddr>::getPort() const
{
	return _port;
}

template<Ws::IsSockAddr _SockAddrIn, class _SockAddr>
Ws::AddressType Address<_SockAddrIn, _SockAddr>::getAddressType() const
{
	return _addressType;
}

template<Ws::IsSockAddr _SockAddrIn, class _SockAddr>
std::string Address<_SockAddrIn, _SockAddr>::getAddressStr() const
{
	return _addressStr;
}

template<Ws::IsSockAddr _SockAddrIn, class _SockAddr>
int& Address<_SockAddrIn, _SockAddr>::getSockAddressSize()
{
	_sockAddrSize =  sizeof(_sockAddress);
	return _sockAddrSize;
}

template<Ws::IsSockAddr _SockAddrIn, class _SockAddr>
void Address<_SockAddrIn, _SockAddr>::copy(const Address<_SockAddrIn, _SockAddr>& other)
{
	_sockAddress = other._sockAddress;
	_addressType = other._addressType;
	_port = other._port;
	_addressStr = other._addressStr;
}

template<Ws::IsSockAddr _SockAddrIn, class _SockAddr>
Address<_SockAddrIn, _SockAddr>& Address<_SockAddrIn, _SockAddr>::operator=(const Address<_SockAddrIn, _SockAddr>& other)
{
	if (this != &other)
	{
		copy(other);
	}

	return *this;
}

template<Ws::IsSockAddr _SockAddrIn, class _SockAddr>
Address<_SockAddrIn, _SockAddr>::Address(const Address<_SockAddrIn, _SockAddr>& other)
{
	*this = other;
}