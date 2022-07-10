#pragma once

#include <string>
#include <iostream>

using namespace SuperNewRoles::CustomCosmetics::ShareCosmetics;

namespace SuperNewRoles::CustomCosmetics::ShareCosmetics
{
	class HttpConnect
	{
	public:
//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task<string> Download(string url)
		static Task<std::wstring> *Download(const std::wstring &url);
//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task<bool> ShareCosmeticDateDownload(byte id, string url)
		static Task<bool> *ShareCosmeticDateDownload(unsigned char id, const std::wstring &url);
	};
}
