#pragma once

#include "CustomPlate.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "../stringhelper.h"
#include "../tangible_filesystem.h"

using namespace HarmonyLib;
using namespace Newtonsoft::Json::Linq;
using namespace UnityEngine;

namespace SuperNewRoles::CustomCosmetics
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch] public class CustomPlates
	class CustomPlates
	{

	public:
		class CustomPlate
		{
		private:
			std::wstring author;
			std::wstring name;
			std::wstring resource;
			std::wstring reshasha;

		public:
			std::wstring getAuthor() const;
			void setAuthor(const std::wstring &value);
			std::wstring getName() const;
			void setName(const std::wstring &value);
			std::wstring getResource() const;
			void setResource(const std::wstring &value);
			std::wstring getReshasha() const;
			void setReshasha(const std::wstring &value);
		};
	};
	class DownLoadClass final
	{
	public:
		static bool IsEndDownload;
		static bool running;
		static std::vector<std::wstring> fetchs;
		static std::vector<CustomPlates::CustomPlate*> platedetails;
		static void Load();
	private:
		static std::wstring sanitizeResourcePath(const std::wstring &res);
		static bool doesResourceRequireDownload(const std::wstring &respath, const std::wstring &reshash, MD5 *md5);
	public:
//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task<HttpStatusCode> FetchHats(string repo)
		static Task<HttpStatusCode> *FetchHats(const std::wstring &repo);
	};
}
