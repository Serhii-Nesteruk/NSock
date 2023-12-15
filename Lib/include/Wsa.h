#pragma once

#include "Ws.h"
#include "Singleton.h"

class Wsa : public Utils::Singleton<Wsa>
{
public:
	void initialize()
	{
		if (WSAStartup(MAKEWORD(2, 2), &ws) < 0)
		{
			throw std::runtime_error("Failed to initialize WinSock");
		}
		_wasInitialized = true;
	}

	bool wasInitialized()
	{
		return _wasInitialized;
	}
	void cleanup()
	{
		WSACleanup();
		_wasInitialized = false;
	}

private:
	bool _wasInitialized{ false };
	WSAData ws;
};
