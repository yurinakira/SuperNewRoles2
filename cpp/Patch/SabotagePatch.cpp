#include "SabotagePatch.h"
#include "../MapOptions/MapOption.h"
#include "../Helpers/MapUtilities.h"

using namespace HarmonyLib;

namespace SuperNewRoles::Patch
{

	void MeltdownBooster::Prefix(ReactorSystemType *__instance, float deltaTime)
	{
		if (MapOptions::MapOption::ReactorDurationOption->getBool())
		{
			if (!__instance->IsActive)
			{
				return;
			}
			if (MapUtilities::CachedShipStatus->Type == ShipStatus::MapType::Pb)
			{
				if (__instance->Countdown >= MapOptions::MapOption::PolusReactorTimeLimit->getFloat())
				{
					__instance->Countdown = MapOptions::MapOption::PolusReactorTimeLimit->getFloat();
				}
				return;
			}
			if (MapUtilities::CachedShipStatus->Type == ShipStatus::MapType::Hq)
			{
				if (__instance->Countdown >= MapOptions::MapOption::MiraReactorTimeLimit->getFloat())
				{
					__instance->Countdown = MapOptions::MapOption::MiraReactorTimeLimit->getFloat();
				}
				return;
			}
			return;
		}
	}

	void HeliMeltdownBooster::Prefix(HeliSabotageSystem *__instance, float deltaTime)
	{
		if (MapOptions::MapOption::ReactorDurationOption->getBool())
		{
			if (!__instance->IsActive)
			{
				return;
			}

			if (MapUtilities::CachedShipStatus != nullptr)
			{
				if (__instance->Countdown >= MapOptions::MapOption::AirshipReactorTimeLimit->getFloat())
				{
					__instance->Countdown = MapOptions::MapOption::AirshipReactorTimeLimit->getFloat();
				}
			}
		}
	}
}
