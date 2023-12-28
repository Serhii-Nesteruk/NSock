#pragma once

#include "Socket.h"
#include "Address.h"

template<Ws::IsSockAddr _SockAddr = sockaddr_in>
class TCPSocket : public Socket<_SockAddr>
{
public:
	TCPSocket() = default;

	/**
		* @brief Constructor for the TCPSocket class with optional binding and connecting.
		*
		* Initializes a TCP socket object with the specified address type, socket address, and optional binding and connecting.
		*
		* @param addressType The address type (IPv4 or IPv6).
		* @param socketAddress The address object associated with the socket.
		* @param shouldBind Flag indicating whether the socket should be bound.
		* @param shouldConnect Flag indicating whether the socket should be connected.
		*/
	TCPSocket(const Ws::AddressType& addressType, Address<_SockAddr>& socketAddress,
		bool shouldBind = false, bool shouldConnect = false);

	/**
	 * @brief Constructor for the TCPSocket class.
	 *
	 * Initializes a TCP socket object with the specified address type, socket address, and descriptor.
	 *
	 * @param addressType The address type (IPv4 or IPv6).
	 * @param socketAddress The address object associated with the socket.
	 * @param descriptor The socket descriptor.
	 */
	TCPSocket(const Ws::AddressType& addressType, const Address<_SockAddr>& socketAddress,
		SOCKET descriptor);

	/**
	 * @brief Destructor for the TCPSocket class.
	 *
	 * Closes the socket and releases associated resources.
	 */
	~TCPSocket();

	TCPSocket(const TCPSocket&) = delete;
	TCPSocket& operator=(const TCPSocket&) = delete;

	/**
	* @brief Move constructor for the TCPSocket class.
	*
	* Moves the content of another TCPSocket object.
	*
	* @param other Another TCPSocket object to be moved.
	*/
	TCPSocket(TCPSocket&& other);
	TCPSocket& operator=(TCPSocket&& other) = delete; // TODO:

	/**
	 * @brief Sends data through the specified socket.
	 *
	 * @param sock The socket through which the data will be sent.
	 * @param data The data to be sent.
	 */
	void send(const Socket<_SockAddr>& sock, const std::string& data);

	/**
	 * @brief Receives data from the socket.
	 *
	 * @return The received data as a string.
	 */
	std::string received();

private:
	Address<_SockAddr> _socketAddress;
};

#include "TCPSocket.inl"