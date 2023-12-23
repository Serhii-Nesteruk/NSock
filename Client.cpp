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