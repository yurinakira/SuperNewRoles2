#include "MapUtilities.h"

using namespace HarmonyLib;
using namespace Il2CppSystem;

namespace SuperNewRoles
{

ShipStatus *MapUtilities::CachedShipStatus = ShipStatus::Instance;

	void MapUtilities::MapDestroyed()
	{
		CachedShipStatus = ShipStatus::Instance;
		_systems.clear();
	}

std::unordered_map<SystemTypes*, std::any> MapUtilities::_systems;

	std::unordered_map<SystemTypes*, std::any> MapUtilities::getSystems()
	{
		if (_systems.empty())
		{
			GetSystems();
		}
		return _systems;
	}

	void MapUtilities::GetSystems()
	{
		if (!CachedShipStatus)
		{
			return;
		}

		auto systems = CachedShipStatus->Systems;
		if (systems->Count <= 0)
		{
			return;
		}

		for (auto systemTypes : SystemTypeHelpers::AllTypes)
		{
			if (!systems->ContainsKey(systemTypes))
			{
				continue;
			}
			_systems[systemTypes] = systems[systemTypes].TryCast<std::any>();
		}
	}

	void ShipStatus_Awake_Patch::Postfix(ShipStatus *__instance)
	{
		MapUtilities::CachedShipStatus = __instance;
	}

	void ShipStatus_OnDestroy_Patch::Postfix()
	{
		MapUtilities::CachedShipStatus = nullptr;
		MapUtilities::MapDestroyed();
	}
}
