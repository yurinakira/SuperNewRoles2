#include "TeleportingJackal.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../ModHelpers.h"
#include "../Helpers/MapUtilities.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleHelper.h"

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void TeleportingJackal::resetCoolDown()
	{
		HudManagerStartPatch::JackalKillButton->MaxTimer = RoleClass::TeleportingJackal::KillCoolDown;
		HudManagerStartPatch::JackalKillButton->Timer = RoleClass::TeleportingJackal::KillCoolDown;
	}

	void TeleportingJackal::EndMeeting()
	{
		resetCoolDown();
		HudManagerStartPatch::SheriffKillButton->MaxTimer = RoleClass::TeleportingJackal::CoolTime;
		RoleClass::TeleportingJackal::ButtonTimer = DateTime::Now;
	}

	void TeleportingJackal::setPlayerOutline(PlayerControl *target, Color *color)
	{
		if (target == nullptr || target->MyRend == nullptr)
		{
			return;
		}

		SuperNewRoles::ModHelpers::MyRend(target)->material.SetFloat(L"_Outline", 1.0f);
		SuperNewRoles::ModHelpers::MyRend(target)->material.SetColor(L"_OutlineColor", color);
	}

	PlayerControl *TeleportingJackal::JackalFixedPatch::TeleportingJackalsetTarget(bool onlyCrewmates, bool targetPlayersInVents, std::vector<PlayerControl*> &untargetablePlayers, PlayerControl *targetingPlayer)
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

	void TeleportingJackal::JackalFixedPatch::TeleportingJackalPlayerOutLineTarget()
	{
		setPlayerOutline(TeleportingJackalsetTarget(), RoleClass::TeleportingJackal::color);
	}

	void TeleportingJackal::JackalFixedPatch::Postfix(PlayerControl *__instance)
	{
		if (PlayerControl::LocalPlayer::isRole(RoleId::TeleportingJackal))
		{
			TeleportingJackalPlayerOutLineTarget();
		}
	}

	void TeleportingJackal::ResetCoolDown()
	{
		HudManagerStartPatch::TeleporterButton->MaxTimer = RoleClass::TeleportingJackal::CoolTime;
		RoleClass::TeleportingJackal::ButtonTimer = DateTime::Now;
	}

	void TeleportingJackal::TeleportStart()
	{
		std::vector<PlayerControl*> aliveplayers;
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p) && p->CanMove)
			{
				aliveplayers.push_back(p);
			}
		}
		auto player = ModHelpers::GetRandom<PlayerControl*>(aliveplayers);
		CustomRPC::RPCProcedure::TeleporterTP(player->PlayerId);
		MessageWriter *Writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::TeleporterTP), Hazel::SendOption::Reliable, -1);
		Writer->Write(player->PlayerId);
		AmongUsClient::Instance->FinishRpcImmediately(Writer);
	}

	bool TeleportingJackal::IsTeleportingJackal(PlayerControl *Player)
	{
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::TeleportingJackal::TeleportingJackalPlayer, Player))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
