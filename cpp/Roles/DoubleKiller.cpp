#include "DoubleKiller.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../ModHelpers.h"
#include "../Helpers/MapUtilities.h"
#include "../CustomRPC/CustomRPC.h"

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void DoubleKiller::resetMainCoolDown()
	{
		HudManagerStartPatch::DoubleKillerMainKillButton->MaxTimer = RoleClass::DoubleKiller::MainCoolTime;
		HudManagerStartPatch::DoubleKillerMainKillButton->Timer = RoleClass::DoubleKiller::MainCoolTime;
	}

	void DoubleKiller::resetSubCoolDown()
	{
		HudManagerStartPatch::DoubleKillerSubKillButton->MaxTimer = RoleClass::DoubleKiller::SubCoolTime;
		HudManagerStartPatch::DoubleKillerSubKillButton->Timer = RoleClass::DoubleKiller::SubCoolTime;
	}

	void DoubleKiller::EndMeeting()
	{
		resetSubCoolDown();
		resetMainCoolDown();
		HudManagerStartPatch::DoubleKillerSubKillButton->MaxTimer = RoleClass::DoubleKiller::SubCoolTime;
	}

	void DoubleKiller::setPlayerOutline(PlayerControl *target, Color *color)
	{
		if (target == nullptr || target->MyRend == nullptr)
		{
			return;
		}

		SuperNewRoles::ModHelpers::MyRend(target)->material.SetFloat(L"_Outline", 1.0f);
		SuperNewRoles::ModHelpers::MyRend(target)->material.SetColor(L"_OutlineColor", color);
	}

	PlayerControl *DoubleKiller::DoubleKillerFixedPatch::DoubleKillersetTarget(bool onlyCrewmates, bool targetPlayersInVents, std::vector<PlayerControl*> &untargetablePlayers, PlayerControl *targetingPlayer)
	{
		PlayerControl *result = nullptr;
		float num = GameOptionsData::KillDistances[Mathf::Clamp(PlayerControl::GameOptions::KillDistance, 0, 2)];
		if (!MapUtilities::CachedShipStatus)
		{
			return result;
		}
		if (targetingPlayer == nullptr)
		{
			targetingPlayer = PlayerControl::LocalPlayer;
		}
		if (targetingPlayer->Data->IsDead || targetingPlayer->inVent)
		{
			return result;
		}

		if (untargetablePlayers.empty())
		{
			untargetablePlayers = std::vector<PlayerControl*>();
		}

		Vector2 *truePosition = targetingPlayer->GetTruePosition();
		Il2CppSystem::Collections::Generic::List<GameData::PlayerInfo*> *allPlayers = GameData::Instance->AllPlayers;
		for (int i = 0; i < allPlayers->Count; i++)
		{
			GameData::PlayerInfo *playerInfo = allPlayers[i];
			if (!playerInfo->Disconnected && playerInfo->PlayerId != targetingPlayer->PlayerId && playerInfo->Object.isAlive() && !playerInfo->Object.isDead() && !SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::DoubleKiller::DoubleKillerPlayer, playerInfo->Object))
			{
				PlayerControl *object = playerInfo->Object;
				if (untargetablePlayers.Any([&] (std::any x)
				{
					return x == object;
				}))
				{
					// if that player is not targetable: skip check
					continue;
				}

				if (object && (!object->inVent || targetPlayersInVents))
				{
					Vector2 *vector = object->GetTruePosition() - truePosition;
					float magnitude = vector->magnitude;
					if (magnitude <= num && !PhysicsHelpers::AnyNonTriggersBetween(truePosition, vector->normalized, magnitude, Constants->ShipAndObjectsMask))
					{
						result = object;
						num = magnitude;
					}
				}
			}
		}
		return result;
	}

	void DoubleKiller::DoubleKillerFixedPatch::DoubleKillerPlayerOutLineTarget()
	{
		setPlayerOutline(DoubleKillersetTarget(), RoleClass::DoubleKiller::color);
	}

	void DoubleKiller::DoubleKillerFixedPatch::Postfix(PlayerControl *__instance)
	{
		if (PlayerControl::LocalPlayer::isRole(RoleId::DoubleKiller))
		{
			DoubleKillerPlayerOutLineTarget();
		}
	}
}
