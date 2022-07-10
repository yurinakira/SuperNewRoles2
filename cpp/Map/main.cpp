#include "main.h"

using namespace HarmonyLib;

namespace SuperNewRoles::Map
{

CustomMapNames Data::ThisMap = CustomMapNames::Skeld;
std::vector<std::wstring> Data::MapStringNames = {L"The Skeld", L"MIRA HQ", L"Polus", L"dlekS ehT", L"Airship", L"Agartha"};
std::unordered_map<std::wstring, CustomMapNames> Data::CustomMapNameData =
{
	{MapStringNames[0], CustomMapNames::Skeld},
	{MapStringNames[1], CustomMapNames::Mira},
	{MapStringNames[2], CustomMapNames::Polus},
	{MapStringNames[3], CustomMapNames::Dleks},
	{MapStringNames[4], CustomMapNames::Agartha},
	{MapStringNames[5], CustomMapNames::Agartha}
};

	void Data::MainMenu()
	{
	}

	void Data::ClearAndReloads()
	{
		//ThisMap = CustomMapNames.Skeld;
		ThisMap = CustomMapNameData[MapStringNames[PlayerControl::GameOptions::MapId]];
		ThisMap = CustomMapNames::Skeld;
	}

	bool Data::IsMap(CustomMapNames map)
	{
		return ThisMap == map;
	}
}
