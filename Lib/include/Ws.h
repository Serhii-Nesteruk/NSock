#pragma once

#include <WinSock2.h>
#include <string>
#include <ws2ipdef.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

namespace Ws
{
	/**
     * Enumeration representing the address types.
     */
	enum class AddressType
	{
		None, /**< No address type. */
		IPv4 = AF_INET,  /**< IPv4 address type. */
		IPv6 = AF_INET6 /**< IPv6 address type. */
	};

	/**
		* Class representing a socket with static methods for socket operations.
		*/
	class Socket
	{
	public:

		/**
         * Enumeration representing the socket types.
         */
		enum class SocketType
		{
			UNDEFINED, /**< Undefined socket type. */
			DGRAM = SOCK_DGRAM,  /**< Datagram socket type. */
			STREAM = SOCK_STREAM /**< Stream socket type. */
		};

		/**
		* Enumeration representing socket protocols.
		*/
		enum class Protocol
		{
			AUTO = 0, /**< Automatically determine the protocol. */
			TCP = IPPROTO_TCP, /**< TCP protocol. */
			UDP = IPPROTO_UDP, /**< UDP protocol. */
		};


		Socket() = delete;

		/**
         * Creates a socket with the specified parameters.
         *
         * @param addressType The address type of the socket.
         * @param socketType The type of the socket.
         * @param aProtocol The protocol to use.
         * @return The created socket descriptor.
         */
		static SOCKET create(const AddressType& addressType,
			const SocketType& socketType,
			const Protocol& aProtocol = Protocol::AUTO);

		/**
		* Binds a socket to a specific address.
		*
		* @param sock The socket descriptor.
		* @param name The sockaddr structure representing the address.
		*/
		static void bind(SOCKET sock, sockaddr* name);

		/**
         * Listens for incoming connections on a socket.
         *
         * @param sock The socket descriptor.
         * @param backlog The maximum length of the queue for pending connections.
         */
		static void listen(SOCKET sock, int backlog = SOMAXCONN);

		/**
		* Connects a socket to a specific address.
		*
		* @param sock The socket descriptor.
		* @param address The sockaddr structure representing the address.
		*/
		static void connect(SOCKET sock, sockaddr* address);

		/**
         * Sends data over a connected socket.
         *
         * @param sock The socket descriptor.
         * @param data The data to send.
         * @param flags Optional flags.
         */
		static void send(SOCKET sock, const char* data, int flags = 0);

		/**
		 * Receives data from a connected socket.
		 *
		 * @param sock The socket descriptor.
		 * @param buf The buffer to store received data.
		 * @param bufSize The size of the buffer.
		 * @param flags Optional flags.
		 */
		static void recv(SOCKET sock, char* buf, int bufSize, int flags = 0);

		/**
		* Accepts an incoming connection on a listening socket.
		*
		* @param sock The listening socket descriptor.
		* @param addr The sockaddr structure representing the client's address.
		* @return The socket descriptor for the accepted connection.
		*/
		[[nodiscard]] static SOCKET accept(SOCKET sock, sockaddr* addr);

		/**
		* Closes a socket.
		*
		* @param sock The socket descriptor to close.
		*/
		static void closeSocket(SOCKET sock);

		/**
         * Checks if a socket is closed.
         *
         * @param sock The socket descriptor.
         * @return True if the socket is closed, false otherwise.
         */
		[[nodiscard]] static bool isClosed(SOCKET sock);

		/**
         * Checks if a socket is valid.
         *
         * @param sock The socket descriptor.
         * @return True if the socket is valid, false otherwise.
         */
		static bool isValid(SOCKET sock);

		/**
         * @brief Sends data to a specific destination using the given socket.
         *
         * @param sock The socket descriptor.
         * @param message A pointer to the buffer containing the data to be sent.
         * @param flags A set of flags that modify the behavior of the function.
         * @param to A pointer to the destination address.
         * @param tolen The size, in bytes, of the address structure pointed to by 'to'.
         *
         * @note This function is a wrapper around the system-level sendto function.
         * @see sendto
         */
		static void sendto(SOCKET sock, const char* message, int flags, const sockaddr* to, int tolen);

		/**
         * @brief Receives data along with information about the sender using the given socket.
         *
         * @param sock The socket descriptor.
         * @param buf A pointer to the buffer to receive the incoming data.
         * @param len The length, in bytes, of the buffer pointed to by 'buf'.
         * @param from A pointer to a sockaddr structure that will be filled with the source address.
         * @param flags A set of flags that modify the behavior of the function.
         * @param fromlen A pointer to the size, in bytes, of the address structure pointed to by 'from'.
         *
         * @note This function is a wrapper around the system-level recvfrom function.
         * @see recvfrom
         */
		static void recvfrom(SOCKET sock, char* buf, int len, sockaddr* from,int flags, int* fromlen);
	};

	/**
	* Throws an error related to Winsock operations.
	*/
	static void ThrowAnError();

	/**
     * Handles a socket error by throwing an exception.
     *
     * @param sock The socket descriptor associated with the error.
     */
	static void handleSocketError(SOCKET sock);

	template<class T> class SockAddr
	{
	};

	/**
     * Template class for sockaddr structure with IPv4 address.
     */
	template<>
	class SockAddr<sockaddr_in>
	{
	public:
		/**
         * Sets the address type for sockaddr_in.
         *
         * @param addrType The address type.
         * @param sockAddr The sockaddr_in structure.
         */
		static void setType(const AddressType& addrType, sockaddr_in& sockAddr);

		/**
		* Sets the port for sockaddr_in.
		*
		* @param port The port number.
		* @param sockAddr The sockaddr_in structure.
		*/
		static void setPort(u_short port, sockaddr_in& sockAddr);

		/**
         * Sets the address for sockaddr_in.
         *
         * @param address The IP address.
         * @param sockAddr The sockaddr_in structure.
         */
		static void setAddress(const std::string& address, sockaddr_in& sockAddr);

		/**
         * Gets the IP address from sockaddr_in.
         *
         * @param sockAddr The sockaddr_in structure.
         * @return The IP address as a string.
         */
		[[nodiscard]] static std::string getAddress(const sockaddr_in& sockAddr);

		/**
         * Gets the address type of sockaddr_in.
         *
         * @return The address type.
         */
		[[nodiscard]] static AddressType getAddrType();
	private:
		inline static AddressType _addrType = AddressType::IPv4;
	};

	/**
     * Template class for sockaddr structure with IPv6 address.
     */
	template<>
	class SockAddr<sockaddr_in6>
	{
	public:
		/**
         * Sets the address type for sockaddr_in6.
         *
         * @param addrType The address type.
         * @param sockAddr The sockaddr_in6 structure.
         */
		static void setType(const AddressType& addrType, sockaddr_in6& sockAddr);

		/**
         * Sets the port for sockaddr_in6.
         *
         * @param port The port number.
         * @param sockAddr The sockaddr_in6 structure.
         */
		static void setPort(u_short port, sockaddr_in6& sockAddr);

		/**
		* Sets the address for sockaddr_in6.
		*
		* @param address The IP address.
		* @param sockAddr The sockaddr_in6 structure.
		*/
		static void setAddress(const std::string& address, sockaddr_in6& sockAddr);

		/**
         * Gets the IP address from sockaddr_in6.
         *
         * @param sockAddr The sockaddr_in6 structure.
         * @return The IP address as a string.
         */
		[[nodiscard]] static std::string getAddress(const sockaddr_in6& sockAddr);

		/**
         * Gets the address type of sockaddr_in6.
         *
         * @return The address type.
         */
		[[nodiscard]] static AddressType getAddrType();
	private:
		inline static AddressType _addrType = AddressType::IPv6;
	};

	/**
	* Alias for SockAddr with sockaddr_in.
	*/
	using SockAddr4 = SockAddr<sockaddr_in>;

	/**
	* Alias for SockAddr with sockaddr_in6.
	*/
	using SockAddr6 = SockAddr<sockaddr_in6>;

	/**
     * Template concept for checking if a type is sockaddr_in or sockaddr_in6.
     *
     * @tparam T The type to check.
     */
	template<class T>
	concept IsSockAddr = std::is_same_v<T, sockaddr_in>;//std::is_same_v<T, SockAddr4> || std::is_same_v<T, SockAddr6>
		 // TODO: fix it
}