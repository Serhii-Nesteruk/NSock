#include <iostream>
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

	Socket<sockaddr_in> clientSocket(Ws::AddressType::IPv4, Ws::Socket::SocketType::STREAM,
		serverAddr, false, true);

	int messageSize = 0;
	Ws::Socket::recv(clientSocket.getDescriptor(), reinterpret_cast<char*>(&messageSize), sizeof(messageSize));

	std::string message{ };
	message.resize(messageSize);
	Ws::Socket::recv(clientSocket.getDescriptor(), message.data(), messageSize);

	std::cout << message << std::endl;

	Wsa::instance().cleanup();

	system("pause");

	return 0;
}