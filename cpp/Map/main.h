#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using namespace HarmonyLib;

namespace SuperNewRoles::Map
{
	enum class CustomMapNames
	{
		Skeld,
		Mira,
		Polus,
		Dleks,
		Airship,
		Agartha
	};
	class Data final
	{
	public:
		static CustomMapNames ThisMap; //CustomMapNames.Agartha;
		static std::vector<std::wstring> MapStringNames;
		static std::unordered_map<std::wstring, CustomMapNames> CustomMapNameData;
		static void MainMenu();
		static void ClearAndReloads();
		static bool IsMap(CustomMapNames map);
	};
}
