#include "JackalSeer.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../ModHelpers.h"
#include "../Helpers/MapUtilities.h"
#include "RoleHelper.h"

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void JackalSeer::resetCoolDown()
	{
		HudManagerStartPatch::JackalKillButton->MaxTimer = RoleClass::JackalSeer::KillCoolDown;
		HudManagerStartPatch::JackalKillButton->Timer = RoleClass::JackalSeer::KillCoolDown;
		HudManagerStartPatch::JackalSeerSidekickButton->MaxTimer = RoleClass::JackalSeer::KillCoolDown;
		HudManagerStartPatch::JackalSeerSidekickButton->Timer = RoleClass::JackalSeer::KillCoolDown;
	}

	void JackalSeer::EndMeeting()
	{
		resetCoolDown();
	}

	void JackalSeer::setPlayerOutline(PlayerControl *target, Color *color)
	{
		if (target == nullptr || target->MyRend == nullptr)
		{
			return;
		}

		SuperNewRoles::ModHelpers::MyRend(target)->material.SetFloat(L"_Outline", 1.0f);
		SuperNewRoles::ModHelpers::MyRend(target)->material.SetColor(L"_OutlineColor", color);
	}

	PlayerControl *JackalSeer::JackalSeerFixedPatch::JackalSeersetTarget(bool onlyCrewmates, bool targetPlayersInVents, std::vector<PlayerControl*> &untargetablePlayers, PlayerControl *targetingPlayer)
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
			if (!playerInfo->Disconnected && playerInfo->PlayerId != targetingPlayer->PlayerId && playerInfo->Object.isAlive() && !playerInfo->Object.isDead() && !SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::Jackal::JackalPlayer, playerInfo->Object) && !SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::Jackal::SidekickPlayer, playerInfo->Object) && !SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::TeleportingJackal::TeleportingJackalPlayer, playerInfo->Object) && !SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::JackalSeer::JackalSeerPlayer, playerInfo->Object) && !SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::JackalSeer::SidekickSeerPlayer, playerInfo->Object))
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

	void JackalSeer::JackalSeerFixedPatch::JackalSeerPlayerOutLineTarget()
	{
		setPlayerOutline(JackalSeersetTarget(), RoleClass::JackalSeer::color);
	}

	void JackalSeer::JackalSeerFixedPatch::Postfix(PlayerControl *__instance, RoleId role)
	{
		if (AmongUsClient::Instance->AmHost)
		{
			if (RoleClass::JackalSeer::SidekickSeerPlayer.size() > 0)
			{
				auto upflag = true;
				for (auto p : RoleClass::JackalSeer::JackalSeerPlayer)
				{
					if (SuperNewRoles::RoleHelpers::isAlive(p))
					{
						upflag = false;
					}
				}
				if (upflag)
				{
					MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SidekickSeerPromotes), Hazel::SendOption::Reliable, -1);
					AmongUsClient::Instance->FinishRpcImmediately(writer);
					RPCProcedure::SidekickSeerPromotes();
				}
			}
		}
		if (role == RoleId::JackalSeer)
		{
			JackalSeerPlayerOutLineTarget();
		}
	}
}
