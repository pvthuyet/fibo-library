module;

#include "config.hpp"
#ifdef SAIGON_OS_WINNT
#include <windows.h>
#include <system_error>
#include <string>
//#include "fmt/format.h"

module Saigon.WindowsStringApi;

namespace saigon::stringapi
{
	std::string wc2mb(std::wstring_view str, unsigned int codePage) // 65001: CP_UTF8
	{
		int len = static_cast<int>(str.length());

		// There is no data to convert
		if (0 == len) {
			return std::string{};
		}

		auto numOfChars = ::WideCharToMultiByte(codePage, 0, str.data(), len, NULL, 0, NULL, NULL);
		if (0 == numOfChars) {
			//throw std::system_error(
			//	::GetLastError(),
			//	std::system_category(),
			//	fmt::format("Failed to convert wide char to multibyte. {}:{}",
			//		__FILE__,
			//		__LINE__));
		}

		std::string mstr(numOfChars, 0);
		auto retVal = ::WideCharToMultiByte(codePage, 0, str.data(), len, &mstr[0], numOfChars, NULL, NULL);
		if (0 == retVal) {
		//	throw std::system_error(
		//		::GetLastError(),
		//		std::system_category(),
		//		fmt::format("Failed to convert wide char to multibyte. {}:{}",
		//			__FILE__,
		//			__LINE__));
		}
		return mstr;
	}

	std::wstring mb2wc(std::string_view str, unsigned int codePage)
	{
		int len = static_cast<int>(str.length());

		// There is no data to convert
		if (0 == len) {
			return std::wstring{};
		}

		int numOfWideChars = ::MultiByteToWideChar(codePage, 0, str.data(), len, NULL, 0);
		if (0 == numOfWideChars) {
			//throw std::system_error(
			//	::GetLastError(),
			//	std::system_category(),
			//	fmt::format("Failed to convert multibyte to wide char. {}:{}",
			//		__FILE__,
			//		__LINE__));
		}

		std::wstring wstr(numOfWideChars, 0);
		auto retVal = ::MultiByteToWideChar(codePage, 0, str.data(), len, &wstr[0], numOfWideChars);
		if (0 == retVal) {
			//throw std::system_error(
			//	::GetLastError(),
			//	std::system_category(),
			//	fmt::format("Failed to convert multibyte to wide char. {}:{}",
			//		__FILE__,
			//		__LINE__));
		}
		return wstr;
	}
}
#endif // SAIGON_OS_WINNT