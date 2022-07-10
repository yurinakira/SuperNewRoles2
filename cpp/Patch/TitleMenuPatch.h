#pragma once

#include <string>
#include <limits>
#include <functional>
#include "../stringhelper.h"
#include "../tangible_filesystem.h"

using namespace HarmonyLib;
using namespace Newtonsoft::Json::Linq;
using namespace SuperNewRoles::CustomCosmetics;
using namespace SuperNewRoles::Patch;
using namespace Twitch;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace static UnityEngine::UI::Button;
//C# TO C++ CONVERTER TODO TASK: C# to C++ Converter could not confirm whether this is a namespace alias or a type alias:
//using Object = UnityEngine::Object;

namespace SuperNewRoles::Patch
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MainMenuManager), nameof(MainMenuManager.Start))] public class MainMenuPatch
	class MainMenuPatch
	{
	public:
		static const std::wstring snrdiscordserver;
	private:
		static void Prefix(MainMenuManager *__instance);
	};
}
