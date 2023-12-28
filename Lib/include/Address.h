#pragma once

#include "Ws.h"

// TODO: check types
template<Ws::IsSockAddr _SockAddrIn = sockaddr_in, class _SockAddr = Ws::SockAddr4>
class Address
{
public:
	Address() = default;

	/**
	 * @brief Copy constructor for the address object.
	 *
	 * @param other Another address object whose value will be copied.
	 */
	Address(const Address& other);

	/**
	 * @brief Assignment operator for the address object.
	 *
	 * @param other Another address object whose value will be assigned.
	 * @return Reference to the assigned object.
	 */
	Address& operator=(const Address& other);

	/**
	* @brief Constructor for the Address class.
	*
	* Initializes an address object with the specified type, port, and address.
	*
	* @param addressType The address type (IPv4 or IPv6).
	* @param port The port number.
	* @param address The string representing the address.
	*/
	Address(const Ws::AddressType& addressType, int port, const std::string& address);
	~Address() = default;

	/**
	 * @brief Constructor for the Address class.
	 *
	 * Initializes an address object with the specified type, port, and address.
	 *
	 * @param addressType The address type (IPv4 or IPv6).
	 * @param port The port number.
	 * @param address The string representing the address.
	 */
	void setAll(const Ws::AddressType& addressType, int port, const std::string& address);

	/**
	 * @brief Sets the address type.
	 *
	 * @param addressType The address type (IPv4 or IPv6).
	 */
	void setAddressType(const Ws::AddressType& addressType);

	/**
	 * @brief Sets the port number.
	 *
	 * @param port The port number.
	 */
	void setPort(int port);

	/**
	* @brief Sets the address.
	*
	* @param address The string representing the address.
	*/
	void setAddress(const std::string& address);

	/**
	* @brief Returns the port number.
	*
	* @return The port number.
	*/
	[[nodiscard]] int getPort() const;

	/**
	 * @brief Returns the string representing the address.
	 *
	 * @return String with the address.
	 */
	[[nodiscard]] std::string getAddressStr() const;

	/**
	 * @brief Returns the address type.
	 *
	 * @return The address type (IPv4 or IPv6).
	 */
	[[nodiscard]] Ws::AddressType getAddressType() const;
	/**
	* @brief Returns the address object.
	*
	* @return Reference to the address object.
	*/
	[[nodiscard]] _SockAddrIn& getSockAddress();

	/**
	* @brief Returns the size of the address object.
	*
	* @return Size of the address object.
	*/
	[[nodiscard]] int& getSockAddressSize();

	/**
	* @brief Copies the content of another address object.
	*
	* @param other Another address object to be copied.
	*/
	void copy(const Address& other);

private:
	_SockAddrIn _sockAddress;
	int _sockAddrSize{ };
	Ws::AddressType _addressType{ Ws::AddressType::None };
	int _port{ 0 };
	std::string _addressStr{ };
};

#include "Address.inl"