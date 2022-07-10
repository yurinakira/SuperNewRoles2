#include "Jackal.h"
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

	void Jackal::resetCoolDown()
	{
		HudManagerStartPatch::JackalKillButton->MaxTimer = RoleClass::Jackal::KillCoolDown;
		HudManagerStartPatch::JackalKillButton->Timer = RoleClass::Jackal::KillCoolDown;
		HudManagerStartPatch::JackalSidekickButton->MaxTimer = RoleClass::Jackal::KillCoolDown;
		HudManagerStartPatch::JackalSidekickButton->Timer = RoleClass::Jackal::KillCoolDown;
	}

	void Jackal::EndMeeting()
	{
		resetCoolDown();
	}

	void Jackal::setPlayerOutline(PlayerControl *target, Color *color)
	{
		if (target == nullptr || SuperNewRoles::ModHelpers::MyRend(target) == nullptr)
		{
			return;
		}

		SuperNewRoles::ModHelpers::MyRend(target)->material.SetFloat(L"_Outline", 1.0f);
		SuperNewRoles::ModHelpers::MyRend(target)->material.SetColor(L"_OutlineColor", color);
	}

	PlayerControl *Jackal::JackalFixedPatch::JackalsetTarget(bool onlyCrewmates, bool targetPlayersInVents, std::vector<PlayerControl*> &untargetablePlayers, PlayerControl *targetingPlayer)
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
			//上記Jackalがbuttonのターゲットにできない役職の設定
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

	void Jackal::JackalFixedPatch::JackalPlayerOutLineTarget()
	{
		setPlayerOutline(JackalsetTarget(), RoleClass::Jackal::color);
	}

	void Jackal::JackalFixedPatch::Postfix(PlayerControl *__instance, RoleId role)
	{
		if (AmongUsClient::Instance->AmHost)
		{
			if (RoleClass::Jackal::SidekickPlayer.size() > 0)
			{
				auto upflag = true;
				for (auto p : RoleClass::Jackal::JackalPlayer)
				{
					if (SuperNewRoles::RoleHelpers::isAlive(p))
					{
						upflag = false;
					}
				}
				if (upflag)
				{
					MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SidekickPromotes), Hazel::SendOption::Reliable, -1);
					AmongUsClient::Instance->FinishRpcImmediately(writer);
					RPCProcedure::SidekickPromotes();
				}
			}
		}
		if (role == RoleId::Jackal)
		{
			JackalPlayerOutLineTarget();
		}
	}
}
