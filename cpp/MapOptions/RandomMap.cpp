#include "RandomMap.h"
#include "MapOption.h"
#include "../SubmergedCompatibility.h"
#include "../Helpers/CachedPlayer.h"

using namespace HarmonyLib;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles::MapOptions
{

	void RandomMap::Prefix()
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (MapOption::IsRandomMap)
		{
			auto rand = new System::Random();
			std::vector<unsigned char> RandomMaps;
			if (MapOption::ValidationSkeld)
			{
				RandomMaps.push_back(0);
			}
			if (MapOption::ValidationMira)
			{
				RandomMaps.push_back(1);
			}
			if (MapOption::ValidationPolus)
			{
				RandomMaps.push_back(2);
			}
			if (MapOption::ValidationAirship)
			{
				RandomMaps.push_back(4);
			}
			if (MapOption::ValidationSubmerged && SubmergedCompatibility::getLoaded())
			{
				RandomMaps.push_back(5);
			}
			if (RandomMaps.size() <= 0)
			{
				delete rand;
				return;
			}
			auto MapsId = RandomMaps[rand->Next(RandomMaps.size())];
			PlayerControl::GameOptions->MapId = MapsId;
			CachedPlayer::LocalPlayer->PlayerControl->RpcSyncSettings(PlayerControl::GameOptions);

			delete rand;
		}
		return;
	}
}
