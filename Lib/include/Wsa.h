#pragma once

#include "Ws.h"
#include "Singleton.h"

/**
 * @class Wsa
 * @brief Handles the initialization and cleanup of WinSock using the Singleton pattern.
 *
 * The Wsa class ensures that WinSock is properly initialized and cleaned up using the Singleton pattern.
 * It provides a single instance that can be accessed globally and guarantees that WinSock is initialized
 * only once during the application's lifetime.
 */
class Wsa : public Utils::Singleton<Wsa>
{
public:

	/**
     * Initializes WinSock.
     *
     * This function initializes WinSock with version 2.2. If the initialization fails, a runtime_error
     * is thrown.
     *
     * @throws std::runtime_error If WinSock initialization fails.
     */
	void initialize()
	{
		if (WSAStartup(MAKEWORD(2, 2), &ws) < 0)
		{
			throw std::runtime_error("Failed to initialize WinSock");
		}
		_wasInitialized = true;
	}

	/**
	* Checks if WinSock has been successfully initialized.
	*
	* @return True if WinSock has been initialized, false otherwise.
	*/
	bool wasInitialized()
	{
		return _wasInitialized;
	}

	/**
     * Cleans up WinSock resources.
     */
	void cleanup()
	{
		WSACleanup();
		_wasInitialized = false;
	}

private:
	bool _wasInitialized{ false };
	WSAData ws;
};
