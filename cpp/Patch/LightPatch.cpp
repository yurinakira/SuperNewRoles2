#include "LightPatch.h"
#include "../SubmergedCompatibility.h"
#include "../Roles/Clergyman.h"
#include "../Roles/RoleClass.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Roles/TeamRoleType.h"
#include "../Roles/RoleHelper.h"
#include "../ModHelpers.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

	float LightPatch::GetNeutralLightRadius(ShipStatus *shipStatus, bool isImpostor)
	{
		if (SubmergedCompatibility::isSubmerged())
		{
			return SubmergedCompatibility::GetSubmergedNeutralLightRadius(isImpostor);
		}

		if (Clergyman::IsLightOutVision() && isImpostor)
		{
			return shipStatus->MaxLightRadius * RoleClass::Clergyman::DownImpoVision;
		}
		if (isImpostor)
		{
			return shipStatus->MaxLightRadius * PlayerControl::GameOptions::ImpostorLightMod;
		}

		SwitchSystem *switchSystem = shipStatus->Systems[SystemTypes::Electrical].TryCast<SwitchSystem*>();
		float lerpValue = switchSystem->Value / 255.0f;

		auto LocalPlayer = PlayerControl::LocalPlayer;
		if (LocalPlayer->isRole(RoleId::Nocturnality))
		{
			if (1 - lerpValue >= 0)
			{
				lerpValue = 1.0f - lerpValue;
			}
			else
			{
				lerpValue = 1.0f + (1.0f - lerpValue);
			}
		}
		return Mathf::Lerp(shipStatus->MinLightRadius, shipStatus->MaxLightRadius, lerpValue) * PlayerControl::GameOptions::CrewLightMod;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(ref float __result, ShipStatus __instance, [HarmonyArgument(0)] GameData.PlayerInfo player)
	bool LightPatch::Prefix(float &__result, ShipStatus *__instance, GameData::PlayerInfo *player)
	{
		//if (!__instance.Systems.ContainsKey(SystemTypes.Electrical)) return true;

		ISystemType *systemType = __instance->Systems->ContainsKey(SystemTypes::Electrical) ? __instance->Systems[SystemTypes::Electrical] : nullptr;
		if (systemType == nullptr)
		{
			return true;
		}
		SwitchSystem *switchSystem = systemType->TryCast<SwitchSystem*>();
		if (switchSystem == nullptr)
		{
			return true;
		}

		float num = static_cast<float>(switchSystem->Value) / 255.0f;

		if (player == nullptr || player->IsDead)
		{
			__result = __instance->MaxLightRadius;
		}
		else if (player->Object.isRole(CustomRPC::RoleId::CountChanger) && CountChanger::GetRoleType(player->Object) == TeamRoleType::Crewmate)
		{
			__result = GetNeutralLightRadius(__instance, false);
		}
		else if (player->Object.isImpostor() || RoleHelpers::IsImpostorLight(player->Object))
		{
			__result = GetNeutralLightRadius(__instance, true);
		}
		else if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::Lighter::LighterPlayer, player->Object) && RoleClass::Lighter::IsLightOn)
		{
			__result = Mathf::Lerp(__instance->MaxLightRadius * RoleClass::Lighter::UpVision, __instance->MaxLightRadius * RoleClass::Lighter::UpVision, num);
		}
		else
		{
			__result = GetNeutralLightRadius(__instance, false);
		}
		return false;
	}
}
