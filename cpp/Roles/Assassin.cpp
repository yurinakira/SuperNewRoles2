#include "Assassin.h"
#include "RoleClass.h"
#include "../Mode/ModeHandler.h"
#include "../Helpers/CachedPlayer.h"
#include "../Mode/SuperHostRoles/main.h"
#include "../BotManager.h"
#include "RoleHelper.h"
#include "../TranslateDate.h"
#include "../CustomRPC/CustomRPC.h"
#include "../LateTask.h"
#include "../Helpers/RPCHelper.h"
#include "../Helpers/MapUtilities.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace UnhollowerBaseLib;

namespace SuperNewRoles::Roles
{

	bool Assassin::AirshipStatusPrespawnStepPatch::Prefix()
	{
		return RoleClass::Assassin::TriggerPlayer == nullptr;
	}

	void Assassin::AddChat(PlayerControl *sourcePlayer, const std::wstring &chatText)
	{
		if (!ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			return;
		}
		if (RoleClass::Assassin::TriggerPlayer != nullptr && sourcePlayer->PlayerId == RoleClass::Assassin::TriggerPlayer->PlayerId)
		{
			auto player = CachedPlayer::AllPlayers.ToArray()->ToList()->FirstOrDefault([&] (_)
			{
				return chatText == _::PlayerControl::name;
			});
			if (player == nullptr || player->PlayerControl.IsBot())
			{
				return;
			}

			Il2CppStructArray<MeetingHud::VoterState*> *array = new Il2CppStructArray<MeetingHud::VoterState*>(MeetingHud::Instance->playerStates->Length);

			for (int i = 0; i < MeetingHud::Instance->playerStates->Length; i++)
			{
				PlayerVoteArea *playerVoteArea = MeetingHud::Instance->playerStates[i];
				if (playerVoteArea->TargetPlayerId == RoleClass::Assassin::TriggerPlayer->PlayerId)
				{
					playerVoteArea->VotedFor = player->Data->PlayerId;
				}
				else
				{
					playerVoteArea->VotedFor = 254;
				}
				MeetingHud::Instance->SetDirtyBit(1U);

				MeetingHud::VoterState *tempVar = new MeetingHud::VoterState();
				tempVar->VoterId = playerVoteArea->TargetPlayerId;
				tempVar->VotedForId = playerVoteArea->VotedFor;
				array[i] = tempVar;

				delete tempVar;
			}
			GameData::PlayerInfo *target = player->Data;
			GameData::PlayerInfo *exileplayer = nullptr;
			if (target != nullptr)
			{
				auto outfit = target->DefaultOutfit;
				exileplayer = target;
				PlayerControl *exile = nullptr;
				Mode::SuperHostRoles::main::RealExiled = target->Object;
				if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
				{
					for (auto p : BotManager::AllBots)
					{
						if (SuperNewRoles::RoleHelpers::isDead(p))
						{
							exileplayer = p->Data;
							exile = p;
							p->RpcSetColor(static_cast<unsigned char>(outfit->ColorId));
							p->RpcSetName(target->Object.getDefaultName() + (target->Object.isRole(RoleId::Marine) ? ModTranslation::getString(L"AssassinSucsess") : ModTranslation::getString(L"AssassinFail")) + L"<size=0%>");
							p->RpcSetHat(outfit->HatId);
							p->RpcSetVisor(outfit->VisorId);
							p->RpcSetSkin(outfit->SkinId);
							break;
						}
					}
				}
				RoleClass::Assassin::MeetingEndPlayers.push_back(RoleClass::Assassin::TriggerPlayer->PlayerId);
				if (target->Object.isRole(RoleId::Marine))
				{
					RoleClass::Assassin::IsImpostorWin = true;
				}
				else
				{
					RoleClass::Assassin::DeadPlayer = RoleClass::Assassin::TriggerPlayer;
				}
				new LateTask([&] ()
				{
					if (exile != nullptr)
					{
						exile->RpcSetName(SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(exile));
						exile->RpcSetColor(1);
						exile->RpcSetHat(L"hat_NoHat");
						exile->RpcSetPet(L"peet_EmptyPet");
						exile->RpcSetVisor(L"visor_EmptyVisor");
						exile->RpcSetNamePlate(L"nameplate_NoPlate");
						exile->RpcSetSkin(L"skin_None");
					}
				}, 5.0f);
			}
			new LateTask([&] ()
			{
				MeetingHud::Instance->RpcVotingComplete(array, exileplayer, true);
			}, 0.2f);

//C# TO C++ CONVERTER TODO TASK: A 'delete array' statement was not added since array was passed to a method or constructor. Handle memory management manually.
		}
	}

	void Assassin::WrapUp(GameData::PlayerInfo *exiled)
	{
		if (RoleClass::Assassin::DeadPlayer != nullptr)
		{
			if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
			{
				if (AmongUsClient::Instance->AmHost)
				{
					SuperNewRoles::Helpers::RPCHelper::RpcInnerExiled(RoleClass::Assassin::DeadPlayer);
				}
			}
			else
			{
				RoleClass::Assassin::DeadPlayer->Exiled();
			}
			RoleClass::Assassin::DeadPlayer = nullptr;
		}
		if (RoleClass::Assassin::IsImpostorWin)
		{
			MapUtilities::CachedShipStatus->enabled = false;
			ShipStatus::RpcEndGame(GameOverReason::ImpostorByVote, false);
		}
		auto exile = Mode::SuperHostRoles::main::RealExiled;
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}) && exile != nullptr && SuperNewRoles::RoleHelpers::isRole(exile, CustomRPC::RoleId::Assassin))
		{
			if (AmongUsClient::Instance->AmHost)
			{
				new LateTask([&] ()
				{
					MeetingRoomManager::Instance->AssignSelf(exile, nullptr);
					FastDestroyableSingleton<HudManager*>::getInstance().OpenMeetingRoom(exile);
					exile->RpcStartMeeting(nullptr);
				}, 10.5f);
				new LateTask([&] ()
				{
					exile->RpcSetName(StringHelper::formatSimple(L"<size=200%>{0}<color=white>は誰だ？</size>", CustomOptions::cs(RoleClass::Marine::color, IntroDate::MarineIntro->NameKey + L"Name")));
				}, 12.0f);
				new LateTask([&] ()
				{
					exile->RpcSendChat(StringHelper::formatSimple(L"\n{0}", ModTranslation::getString(L"MarineWhois")));
				}, 12.5f);
				new LateTask([&] ()
				{
					exile->RpcSetName(SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(exile));
				}, 13.0f);
			}
			RoleClass::Assassin::TriggerPlayer = exile;
		}
	}
}
