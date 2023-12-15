#pragma once

#include "Ws.h"

// TODO: check types
template<Ws::IsSockAddr _SockAddrIn = sockaddr_in, class _SockAddr = Ws::SockAddr4>
class Address
{
public:
	Address() = default;
	Address(const Ws::AddressType& addressType, int port, const std::string& address);
	~Address() = default;

	void setAll(const Ws::AddressType& addressType, int port, const std::string& address);

	void setAddressType(const Ws::AddressType& addressType);
	void setPort(int port);
	void setAddress(const std::string& address);

	[[nodiscard]] int getPort() const;
	[[nodiscard]] std::string getAddressStr() const;
	[[nodiscard]] Ws::AddressType getAddressType() const;
	[[nodiscard]] _SockAddrIn& getSockAddress();
private:
	_SockAddrIn _sockAddress;
	Ws::AddressType _addressType{ Ws::AddressType::None };
	int _port{ 0 };
	std::string _addressStr{ };
};

#include "Address.inl"