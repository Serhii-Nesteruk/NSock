#pragma once

#include <string>

namespace Utils
{
	[[nodiscard]] std::string GetWinSockErrorString(int errorCode);
}