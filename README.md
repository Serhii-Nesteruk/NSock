# NSock - C++ Socket Library

NSock is a C++ library that provides a simple and flexible interface for working with sockets. It is designed to simplify the process of creating and managing network connections in C++ applications.

## Features
- Easy-to-use API for socket programming in C++.
- Support for TCP and UDP sockets.
- the basic platform is Windows

Under development

```cpp
#include "TCPSocket.h"
#include "Wsa.h"

#include <iostream>

int main()
{
	try
	{
		Wsa::instance().initialize();

		Address serverAddr(Ws::AddressType::IPv4, 8088, "127.0.0.1");

		TCPSocket clientSocket(Ws::AddressType::IPv4, serverAddr, false, true);

		std::string message = clientSocket.received();

		std::cout << message << std::endl;

		Wsa::instance().cleanup();

		system("pause");
	}
	catch (const std::runtime_error& error)
	{
		std::cerr << "================" << std::endl;
		std::cerr << error.what() << std::endl;
		std::cerr << "================" << std::endl;
	}

	return 0;
}
```
