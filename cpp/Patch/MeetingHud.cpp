//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "MeetingHud.h"
#include "../Mode/SuperHostRoles/main.h"
#include "../Roles/RoleClass.h"
#include "../Mode/ModeHandler.h"
#include "../Mode/Detective/main.h"
#include "../Helpers/CachedPlayer.h"
#include "../Mode/Werewolf/main.h"
#include "../ModHelpers.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Roles/RoleHelper.h"
#include "../Main.h"
#include "../BotManager.h"
#include "../TranslateDate.h"
#include "../LateTask.h"
#include "../Mode/SuperHostRoles/FixedUpdate.h"
#include "../Roles/Bakery.h"
#include "../PlayerControlHepler.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../Helpers/RPCHelper.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;
using namespace static MeetingHud;

namespace SuperNewRoles::Patch
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix(MeetingHud __instance, [HarmonyArgument(0)] VoterState[] states, [HarmonyArgument(1)] ref GameData.PlayerInfo exiled, [HarmonyArgument(2)] bool tie)
	void VotingComplete::Prefix(MeetingHud *__instance, std::vector<VoterState*> &states, GameData::PlayerInfo *&exiled, bool tie)
	{
		if (exiled != nullptr && exiled->Object.IsBot() && RoleClass::Assassin::TriggerPlayer == nullptr && main::RealExiled == nullptr)
		{
			exiled = nullptr;
		}
	}

	bool CheckForEndVotingPatch::Prefix(MeetingHud *__instance)
	{
		try
		{
			if (!AmongUsClient::Instance->AmHost)
			{
				return true;
			}
			if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Detective}) && Mode::Detective::main::IsNotDetectiveVote)
			{
				for (auto ps : *__instance->playerStates)
				{
					if (ps->TargetPlayerId == Mode::Detective::main::DetectivePlayer->PlayerId && !ps->DidVote)
					{
						return false;
					}
					else if (ps->TargetPlayerId == Mode::Detective::main::DetectivePlayer->PlayerId && ps->DidVote)
					{
						std::vector<MeetingHud::VoterState*> statesdetective;
						GameData::PlayerInfo *exiledPlayerdetective = CachedPlayer::LocalPlayer->Data;
						bool tiedetective = false;

						std::vector<MeetingHud::VoterState*> statesListdetective;
						if (ps->VotedFor != ps->TargetPlayerId)
						{
							MeetingHud::VoterState *tempVar = new MeetingHud::VoterState();
							tempVar->VoterId = ps->TargetPlayerId;
							tempVar->VotedForId = ps->VotedFor;
							statesListdetective.push_back(tempVar);
							statesdetective = statesListdetective.ToArray();

							auto VotingDatadetective = SuperNewRoles::Patch::ExtendedMeetingHud::CustomCalculateVotes(__instance);

							exiledPlayerdetective = GameData::Instance->AllPlayers.GetFastEnumerator()->ToArray()->FirstOrDefault([&] (std::any info)
							{
								return !tiedetective && info->PlayerId == ps->VotedFor;
							});

							__instance->RpcVotingComplete(statesdetective, exiledPlayerdetective, tiedetective); //RPC

//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
						}
						else
						{
							MeetingHud::VoterState *tempVar2 = new MeetingHud::VoterState();
							tempVar2->VoterId = ps->TargetPlayerId;
							tempVar2->VotedForId = 253;
							statesListdetective.push_back(tempVar2);
							statesdetective = statesListdetective.ToArray();

							auto VotingDatadetective = SuperNewRoles::Patch::ExtendedMeetingHud::CustomCalculateVotes(__instance);
							exiledPlayerdetective = GameData::Instance->AllPlayers.GetFastEnumerator()->ToArray()->FirstOrDefault([&] (std::any info)
							{
								return !tiedetective && info->PlayerId == 253;
							});

							__instance->RpcVotingComplete(statesdetective, exiledPlayerdetective, tiedetective); //RPC

//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar2' statement was not added since tempVar2 was passed to a method or constructor. Handle memory management manually.
						}
						return false;
					}
				}
			}
			else if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Werewolf}))
			{
				if (Mode::Werewolf::main::isAbility())
				{
					for (auto ps : *__instance->playerStates)
					{
						PlayerControl *player = ModHelpers::playerById(ps->TargetPlayerId);
						if (!ps->AmDead && !ps->DidVote && (SuperNewRoles::RoleHelpers::isImpostor(player) || (!SuperNewRoles::RoleHelpers::isRole(player, CustomRPC::RoleId::DefaultRole) && !SuperNewRoles::RoleHelpers::isRole(player, CustomRPC::RoleId::MadMate) && !SuperNewRoles::RoleHelpers::isRole(player, CustomRPC::RoleId::SpiritMedium) && !(player->PlayerId == Mode::Werewolf::main::HunterExilePlayer->PlayerId && SuperNewRoles::ModHelpers::IsCheckListPlayerControl(Mode::Werewolf::main::HunterPlayers, player)))))
						{
							return false;
						}
					}
					for (auto i = 0; i < __instance->playerStates->Length; i++)
					{
						PlayerVoteArea *ps = __instance->playerStates[i];
						PlayerControl *player = ModHelpers::playerById(ps->TargetPlayerId);
						PlayerControl *VoteTarget = GameData::Instance->AllPlayers.GetFastEnumerator()->ToArray()->FirstOrDefault([&] (std::any info)
						{
							return info->PlayerId == ps->VotedFor;
						}) == nullptr ? nullptr : GameData::Instance->AllPlayers.GetFastEnumerator()->ToArray()->FirstOrDefault([&] (std::any info)
						{
							return info->PlayerId == ps->VotedFor;
						})->Object;
						if (ps->VotedFor != 253 && ps->VotedFor != 254 && VoteTarget != nullptr)
						{
							if (SuperNewRoles::RoleHelpers::isImpostor(player))
							{
								Mode::Werewolf::main::WolfKillPlayers.push_back(VoteTarget->PlayerId);
							}
							else if (SuperNewRoles::RoleHelpers::isRole(player, RoleId::SoothSayer))
							{
								Mode::Werewolf::main::SoothRoles.emplace(player->PlayerId, VoteTarget->PlayerId);
							}
							else if (player->PlayerId == Mode::Werewolf::main::HunterExilePlayer->PlayerId && SuperNewRoles::ModHelpers::IsCheckListPlayerControl(Mode::Werewolf::main::HunterPlayers, player))
							{
								Mode::Werewolf::main::SoothRoles.emplace(player->PlayerId, VoteTarget->PlayerId);
							}
						}
					}
					__instance->RpcVotingComplete((std::vector<MeetingHud::VoterState*>())->ToArray(), nullptr, false);
					return false;
				}
				else
				{
					for (auto ps : *__instance->playerStates)
					{
						if (!(ps->AmDead || ps->DidVote)) //死んでいないプレイヤーが投票していない
						{
							return false;
						}
					}
					std::vector<MeetingHud::VoterState*> states1;
					GameData::PlayerInfo *exiledPlayer1 = CachedPlayer::LocalPlayer->Data;
					bool tie1 = false;

					std::vector<MeetingHud::VoterState*> statesList1;
					for (auto i = 0; i < __instance->playerStates->Length; i++)
					{
						PlayerVoteArea *ps = __instance->playerStates[i];
						if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::BattleRoyal}))
						{
							if (ps != nullptr && SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(ps->TargetPlayerId), CustomRPC::RoleId::Sheriff))
							{
							}
						}
						else
						{
							if (ps == nullptr)
							{
								continue;
							}
							auto voter = ModHelpers::playerById(ps->TargetPlayerId);
							if (voter == nullptr || voter->Data == nullptr || voter->Data->Disconnected)
							{
								continue;
							}
							MeetingHud::VoterState *tempVar3 = new MeetingHud::VoterState();
							tempVar3->VoterId = ps->TargetPlayerId;
							tempVar3->VotedForId = ps->VotedFor;
							statesList1.push_back(tempVar3);

//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar3' statement was not added since tempVar3 was passed to a method or constructor. Handle memory management manually.
						}
					}
					states1 = statesList1.ToArray();
					auto VotingData1 = SuperNewRoles::Patch::ExtendedMeetingHud::CustomCalculateVotes(__instance);
					unsigned char exileId1 = std::numeric_limits<unsigned char>::max();
					int max1 = 0;

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
