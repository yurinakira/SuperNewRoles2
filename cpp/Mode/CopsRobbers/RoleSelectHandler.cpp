#include "RoleSelectHandler.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../BotManager.h"
#include "../../ModHelpers.h"
#include "../SuperHostRoles/Helpers.h"
#include "main.h"
#include "../SuperHostRoles/main.h"

using namespace SuperNewRoles::Mode::SuperHostRoles;

namespace SuperNewRoles::Mode::CopsRobbers
{

	void RoleSelectHandler::Handler()
	{
		std::vector<PlayerControl*> SelectPlayers;
		std::vector<PlayerControl*> impostors;
		for (auto player : CachedPlayer::AllPlayers)
		{
			if (!player->Data->Disconnected && SuperNewRoles::BotManager::IsPlayer(player))
			{
				SelectPlayers.push_back(player);
			}
		}
		for (int i = 0; i < PlayerControl::GameOptions::NumImpostors; i++)
		{
			if (SelectPlayers.size() >= 1)
			{
				auto newimpostor = ModHelpers::GetRandom(SelectPlayers);
				impostors.push_back(newimpostor);
				SelectPlayers.RemoveAll([&] (std::any a)
				{
					return a->PlayerId == newimpostor->PlayerId;
				});
			}
		}
		for (auto player : impostors)
		{
			player->RpcSetRole(RoleTypes::Impostor);
			for (auto player2 : CachedPlayer::AllPlayers)
			{
				if (!player2->Data->Disconnected)
				{
					if (!SuperNewRoles::ModHelpers::IsCheckListPlayerControl(impostors, player2))
					{
						SuperNewRoles::Mode::SuperHostRoles::Helpers::RpcSetRoleDesync(player2, RoleTypes::GuardianAngel, player);
					}
				}
			}
		}
		for (auto player : CachedPlayer::AllPlayers)
		{
			if (!player->Data->Disconnected)
			{
				if (!SuperNewRoles::ModHelpers::IsCheckListPlayerControl(impostors, player))
				{
					player->RpcSetRole(RoleTypes::Crewmate);
				}
				// player.RpcSetName("");
			}
		}
		main::ChangeCosmetics();
	}
}
