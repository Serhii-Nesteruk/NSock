#include "Socket.h"
#include "Address.h"
#include "Wsa.h"
#include "TCPSocket.h"

int main()
{
	try
	{
		Wsa::instance().initialize();

		Address serverAddr(Ws::AddressType::IPv4, 8088, "127.0.0.1");

		TCPSocket serverSocket(Ws::AddressType::IPv4, serverAddr, true, false);
		serverSocket.listen();

		Socket clientSocket = serverSocket.accept();

		std::string message{ "Hello World!!!" };
		serverSocket.send(clientSocket, message);

		Wsa::instance().cleanup();

		system("pause");
	}
	catch(const std::runtime_error& error)
	{
		std::cerr << "================" << std::endl;
		std::cerr << error.what() << std::endl;
		std::cerr << "================" << std::endl;
	}

	return 0;
}
