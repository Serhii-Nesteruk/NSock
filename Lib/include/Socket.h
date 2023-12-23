#pragma once

#include "Ws.h"

/**
 * @brief Socket class template.
 *
 * This template represents a basic socket class with support for various socket operations.
 *
 * @tparam _SockAddr Type for socket address. Defaults to sockaddr_in.
 */
template<Ws::IsSockAddr _SockAddr = sockaddr_in>
class Socket
{
public:
	using SocketType = Ws::Socket::SocketType;
	/**
     * @brief Default constructor.
     */
	Socket() = default;

	/**
     * @brief Parameterized constructor.
     *
     * @param addressType   Type of socket address.
     * @param socketType    Type of socket.
     * @param sockAddr      Socket address.
     * @param descriptor    Socket descriptor.
     */
	Socket(const Ws::AddressType& addressType, const SocketType& socketType,
		_SockAddr& sockAddr, SOCKET descriptor);

	/**
	* @brief Constructor with address type and socket type.
	*
	* @param addressType   Type of socket address.
	* @param socketType    Type of socket.
	*/
	Socket(const Ws::AddressType& addressType, const SocketType& socketType);

	/**
     * @brief Constructor with address type, socket type, and optional parameters for binding and connecting.
     *
     * @param addressType   Type of socket address.
     * @param socketType    Type of socket.
     * @param address       Socket address.
     * @param shouldBind    Flag indicating whether to bind the socket.
     * @param shouldConnect Flag indicating whether to connect the socket.
     */
	Socket(const Ws::AddressType& addressType, const SocketType& socketType,
		_SockAddr& address, bool shouldBind = false, bool shouldConnect = false);

	Socket(const Socket&) = delete;
	Socket& operator=(const Socket&) = delete;

	/**
     * @brief Move assignment operator.
     *
     * @param other Another Socket object to move.
     * @return Reference to the current object.
     */
	Socket& operator=(Socket&& other);

	/**
	* @brief Move constructor.
	*
	* @param other Another Socket object to move.
	*/
	Socket(Socket&& other);

	/**
	* @brief Destructor.
	*/
	~Socket();

	/**
     * @brief Bind the socket to a specific address.
     *
     * @param address Socket address to bind.
     */
	void bind(_SockAddr& address);

	/**
	* Creates a socket with the specified address type and socket type.
	*
	* This function creates a socket with the specified address type and socket type.
	* If the socket has already been created, an exception is thrown.
	*
	* @throws std::runtime_error If the address type is set to None, socket type is UNDEFINED,
	*                           or if the socket has already been created.
	*/
	void create();

	/**
	* Creates a socket with the specified address type and socket type.
	*
	* This function creates a socket with the specified address type and socket type.
	* If the socket has already been created, an exception is thrown.
	*
	* @param addressType The address type of the socket.
	* @param socketType The type of the socket.
	* @throws std::runtime_error If the socket has already been created.
	*/
	void create(const Ws::AddressType& addressType, const SocketType& socketType);

	/**
     * @brief Close the socket.
     */
	void close();

	/**
	 * @brief Check if the socket was created.
	 *
	 * @return True if the socket was created, false otherwise.
	 */
	void listen(int backlog = SOMAXCONN);

	/**
	* @brief Connect the socket to a specific address.
	*
	* @param address Socket address to connect to.
	*/
	void connect(_SockAddr& address);

	/**
	* @brief Accept a new connection on the socket.
	*
	* @return A new Socket object representing the accepted connection.
	*/
	Socket accept();

	/**
	* Sets the address type of the socket.
	*
	* This function sets the address type of the socket. It should be called before creating
	* or binding the socket. If the socket has already been created or bound, this function
	* will throw an exception.
	*
	* @throws std::runtime_error If the socket has already been created or bound.
	*/
	void setAddressType();

	/**
	* Sets the socket type of the socket.
	*
	* This function sets the socket type of the socket. It should be called before creating
	* the socket. If the socket has already been created, this function will throw an exception.
	*
	* @param socketType The type of the socket.
	* @throws std::runtime_error If the socket has already been created.
	*/
	void setSocketType(const SocketType& socketType);

	/**
	 * Sets the address of the socket.
	 *
	 * This function sets the address of the socket. It should be called before creating
	 * or connecting the socket. If the socket has already been created or connected, this function
	 * will throw an exception.
	 *
	 * @param sockAddr The sockaddr structure representing the address.
	 * @throws std::runtime_error If the socket has already been created or connected.
	 */
	void setAddress(const _SockAddr sockAddr);

	/**
	* Checks if the socket has been created.
	*
	* @return True if the socket has been created, false otherwise.
	*/
	[[nodiscard]] bool wasCreated() const;

	/**
	* Checks if the socket has been bound.
	*
	* @return True if the socket has been bound, false otherwise.
	*/
	[[nodiscard]] bool wasBound() const;


	/**
	 * Checks if the socket is already listening.
	 *
	 * @return True if the socket is already listening, false otherwise.
	 */
	[[nodiscard]] bool alreadyListening() const;

	/**
     * @brief Check if the socket is already connected.
     *
     * @return True if the socket is already connected, false otherwise.
     */
	[[nodiscard]] bool alreadyConnected() const;

	/**
     * @brief Get the socket descriptor.
     *
     * @return The socket descriptor.
     */
	[[nodiscard]] SOCKET getDescriptor() const;


private:

	/**
     * @brief Helper function to zero out data in the socket.
     *
     * @param sock Reference to the Socket object.
     */
	void zeroingData(Socket& sock);

private:
	bool _wasCreated{ false };
	bool _wasBound{ false };
	bool _alreadyConnected{ false };
	bool _alreadyListening{ false };
	SOCKET _sockDescriptor{ INVALID_SOCKET };
	Ws::AddressType _addressType{ Ws::AddressType::None };
	SocketType _socketType{ SocketType::UNDEFINED };
	_SockAddr _address;
};

#include "Socket.inl"