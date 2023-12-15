#include "../include/Utils.h"

#include <WinSock2.h>

std::string Utils::GetWinSockErrorString(int errorCode)
{
	LPVOID errorMsgBuffer = nullptr;

	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		nullptr,
		errorCode,
		0, // Default language
		reinterpret_cast<LPSTR>(&errorMsgBuffer),
		0,
		nullptr
	);

	if (errorMsgBuffer != nullptr)
	{
		std::string errorMsg(static_cast<LPCSTR>(errorMsgBuffer));
		LocalFree(errorMsgBuffer); // Free the buffer
		return errorMsg;
	}
	else
	{
		return "Failed to retrieve error message.";
	}
}
