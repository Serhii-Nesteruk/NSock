#include <WS2tcpip.h>

#include "Socket.h"
#include "Wsa.h"

int main()
{
	Wsa::instance().initialize();

	sockaddr_in serverAddr;
	Ws::SockAddr4::setType(Ws::AddressType::IPv4, serverAddr);
	Ws::SockAddr4::setPort(8088, serverAddr);
	Ws::SockAddr4::setAddress("127.0.0.1", serverAddr);

	Socket<sockaddr_in> serverSocket(Ws::AddressType::IPv4, Ws::Socket::SocketType::STREAM,
		serverAddr, true, false);
	serverSocket.listen();

	Socket<sockaddr_in> clientSocket = serverSocket.accept();

	std::string message{ "Hello World!!!" };
	int messageSize = message.size();
	Ws::Socket::send(clientSocket.getDescriptor(), reinterpret_cast<const char*>(&messageSize));
	Ws::Socket::send(clientSocket.getDescriptor(), message.data());

	Wsa::instance().cleanup();

	system("pause");

	return 0;
}
