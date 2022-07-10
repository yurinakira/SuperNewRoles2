#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include "stringhelper.h"
#include "tangible_filesystem.h"

using namespace HarmonyLib;
using namespace Newtonsoft::Json::Linq;
using namespace Twitch;
using namespace UnityEngine;

namespace SuperNewRoles
{
	class AutoUpdate
	{
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AnnouncementPopUp), nameof(AnnouncementPopUp.UpdateAnnounceText))] public static class Announcement
		class Announcement final
		{
		public:
			static bool Prefix(AnnouncementPopUp *__instance);
		};
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AnnouncementPopUp), nameof(AnnouncementPopUp.Init))] public static class AnnouncementInitpatch
		class AnnouncementInitpatch final
		{
		public:
			static bool Prefix(AnnouncementPopUp *__instance);
		};
	public:
		static std::wstring announcement;
		static GenericPopup *InfoPopup;
	private:
		static bool IsLoad;
	public:
		static std::wstring updateURL;
		static void Load();
//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task<bool> Update()
		static Task<bool> *Update();
//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task<bool> checkForUpdate(TMPro.TextMeshPro setdate)
		static Task<bool> *checkForUpdate(TMPro::TextMeshPro *setdate);
	};
}
