#include "VentAndSabo.h"
#include "../ModHelpers.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../MapOptions/MapOption.h"
#include "../Roles/RoleHelper.h"
#include "../SubmergedCompatibility.h"
#include "../Helpers/CachedPlayer.h"
#include "../Roles/RoleClass.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::MapOptions;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Buttons
{

	bool VentAndSabo::MapBehaviourPatch::Prefix(MapBehaviour *__instance)
	{
		if (!MeetingHud::Instance)
		{
			if (PlayerControl::LocalPlayer::IsUseSabo() && !ModHelpers::getShowButtons() && !__instance->IsOpen)
			{
				__instance->Close();
				FastDestroyableSingleton<HudManager*>::getInstance().ShowMap(static_cast<Il2CppSystem::Action<MapBehaviour*>*>([&] (m)
				{
					m::ShowSabotageMap();
				}));
				return false;
			}
		}
		return true;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(Vent __instance, [HarmonyArgument(0)] PlayerControl pc)
	bool VentAndSabo::EnterVentAnimPatch::Prefix(Vent *__instance, PlayerControl *pc)
	{
		if (MapOption::VentAnimation->getBool())
		{
			return pc->AmOwner;
		}
		return true;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(Vent __instance, [HarmonyArgument(0)] PlayerControl pc)
	bool VentAndSabo::ExitVentAnimPatch::Prefix(Vent *__instance, PlayerControl *pc)
	{
		if (MapOption::VentAnimation->getBool())
		{
			return pc->AmOwner;
		}
		return true;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(Vent __instance, ref float __result, [HarmonyArgument(0)] GameData.PlayerInfo pc, [HarmonyArgument(1)] out bool canUse, [HarmonyArgument(2)] out bool couldUse)
	bool VentAndSabo::VentCanUsePatch::Prefix(Vent *__instance, float &__result, GameData::PlayerInfo *pc, bool &canUse, bool &couldUse)
	{
		float num = std::numeric_limits<float>::max();
		PlayerControl *object = pc->Object;

		bool roleCouldUse = SuperNewRoles::RoleHelpers::IsUseVent(object);

		auto usableDistance = __instance->UsableDistance;

		if (SubmergedCompatibility::isSubmerged())
		{
			// as submerged does, only change stuff for vents 9 and 14 of submerged. Code partially provided by AlexejheroYTB
			if (SubmergedCompatibility::getInTransition())
			{
				__result = std::numeric_limits<float>::max();
				return canUse = couldUse = false;
			}
			switch (__instance->Id)
			{
				case 9: // Cannot enter vent 9 (Engine Room Exit Only Vent)!
					if (PlayerControl::LocalPlayer::inVent)
					{
						break;
					}
					__result = std::numeric_limits<float>::max();
					return canUse = couldUse = false;
				case 14: // Lower Central
					__result = std::numeric_limits<float>::max();
					couldUse = roleCouldUse && !pc->IsDead && (object->CanMove || object->inVent);
					canUse = couldUse;
					if (canUse)
					{
						Vector3 *center = object->Collider.bounds.center;
						Vector3 *position = __instance->transform.position;
						__result = Vector2::Distance(center, position);
						canUse &= __result <= __instance->UsableDistance;
					}
					return false;
			}
		}

		couldUse = (object->inVent || roleCouldUse) && !pc->IsDead && (object->CanMove || object->inVent);
		canUse = couldUse;
		if (pc->Role->Role == RoleTypes::Engineer)
		{
			return true;
		}
		if (canUse)
		{
			Vector2 *truePosition = object->GetTruePosition();
			Vector3 *position = __instance->transform.position;
			num = Vector2::Distance(truePosition, position);

			canUse &= num <= usableDistance && !PhysicsHelpers::AnythingBetween(truePosition, position, Constants->ShipOnlyMask, false);
		}
		__result = num;
		return false;
	}

	void VentAndSabo::VentButtonVisibilityPatch::Postfix(PlayerControl *__instance)
	{
		auto ImpostorVentButton = FastDestroyableSingleton<HudManager*>::getInstance().ImpostorVentButton;
		auto ImpostorSabotageButton = FastDestroyableSingleton<HudManager*>::getInstance().SabotageButton;

		if (PlayerControl::LocalPlayer::IsUseVent())
		{
			if (!ImpostorVentButton->gameObject.active)
			{
				ImpostorVentButton->Show();
			}
			if (Input->GetKeyDown(KeyCode::V) || KeyboardJoystick::player::GetButtonDown(50))
			{
				ImpostorVentButton->DoClick();
			}
		}
		else
		{
			if (ImpostorVentButton->gameObject.active)
			{
				ImpostorVentButton->Hide();
			}
		}

		if (PlayerControl::LocalPlayer::IsUseSabo())
		{
			if (!ImpostorSabotageButton->gameObject.active)
			{
				ImpostorSabotageButton->Show();
			}
		}
		else
		{
			if (ImpostorSabotageButton->gameObject.active)
			{
				ImpostorSabotageButton->Hide();
			}
		}
	}

	bool VentAndSabo::VentUsePatch::Prefix(Vent *__instance)
	{
		bool canUse;
		bool couldUse;
		__instance->CanUse(CachedPlayer::LocalPlayer->Data, canUse, couldUse);
		bool canMoveInVents = !SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::MadMate::MadMatePlayer, PlayerControl::LocalPlayer);
		if (!canUse)
		{
			return false; // No need to execute the native method as using is disallowed anyways
		}

		bool isEnter = !PlayerControl::LocalPlayer::inVent;

		if (isEnter)
		{
			PlayerControl::LocalPlayer::MyPhysics::RpcEnterVent(__instance->Id);
		}
		else
		{
			PlayerControl::LocalPlayer::MyPhysics::RpcExitVent(__instance->Id);
		}
		__instance->SetButtons(isEnter && canMoveInVents);
		return false;
	}

	bool VentAndSabo::SabotageButtonDoClickPatch::Prefix(SabotageButton *__instance)
	{
		// The sabotage button behaves just fine if it's a regular impostor
		if (CachedPlayer::LocalPlayer->Data->Role->TeamType == RoleTeamTypes::Impostor)
		{
			return true;
		}

		FastDestroyableSingleton<HudManager*>::getInstance().ShowMap(static_cast<Il2CppSystem::Action<MapBehaviour*>*>([&] (m)
		{
			m::ShowSabotageMap();
		}));
		return false;
	}
}
