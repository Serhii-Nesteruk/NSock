#include <WS2tcpip.h>

#include "Socket.h"
#include "Address.h"
#include "Wsa.h"

int main()
{
	try
	{
		Wsa::instance().initialize();

		Address<sockaddr_in, Ws::SockAddr4> serverAddr(Ws::AddressType::IPv4, 8088, "127.0.0.1");

		Socket serverSocket(Ws::AddressType::IPv4, Ws::Socket::SocketType::STREAM,
			serverAddr.getSockAddress(), true, false);
		serverSocket.listen();

		Socket<sockaddr_in> clientSocket = serverSocket.accept();

		std::string message{ "Hello World!!!" };
		int messageSize = message.size();
		Ws::Socket::send(clientSocket.getDescriptor(), reinterpret_cast<const char*>(&messageSize));
		Ws::Socket::send(clientSocket.getDescriptor(), message.data());

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
