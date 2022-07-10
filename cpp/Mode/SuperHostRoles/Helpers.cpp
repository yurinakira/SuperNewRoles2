#include "Helpers.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../ModHelpers.h"
#include "../../Main.h"

using namespace Hazel;

namespace SuperNewRoles::Mode::SuperHostRoles
{

	void Helpers::UnCheckedRpcSetRole(PlayerControl *player, RoleTypes *role)
	{
		for (auto p : CachedPlayer::AllPlayers)
		{
			SuperNewRoles::Mode::SuperHostRoles::Helpers::RpcSetRoleDesync(player, role, p);
		}
	}

	void Helpers::RpcSetRoleDesync(PlayerControl *player, RoleTypes *role, PlayerControl *seer)
	{
		//player: 名前の変更対象
		//seer: 上の変更を確認することができるプレイヤー

		if (player == nullptr)
		{
			return;
		}
		if (seer == nullptr)
		{
			seer = player;
		}
		auto clientId = SuperNewRoles::ModHelpers::getClientId(seer);
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(player->NetId, static_cast<unsigned char>(RpcCalls::SetRole), Hazel::SendOption::Reliable, clientId);
		writer->Write(static_cast<unsigned short>(role));
		AmongUsClient::Instance->FinishRpcImmediately(writer);
	}

	void Helpers::RpcSetRoleDesync(PlayerControl *player, CustomRpcSender *sender, RoleTypes *role, PlayerControl *seer)
	{
		//player: 名前の変更対象
		//seer: 上の変更を確認することができるプレイヤー

		if (player == nullptr)
		{
			return;
		}
		if (seer == nullptr)
		{
			seer = player;
		}
		auto clientId = SuperNewRoles::ModHelpers::getClientId(seer);
		SuperNewRolesPlugin::Logger->LogInfo(L"(Desync => " + seer->Data->PlayerName + L" ) " + player->Data->PlayerName + L" => " + role);
		sender->StartMessage(clientId)->StartRpc(player->NetId, RpcCalls::SetRole).Write(static_cast<unsigned short>(role)).EndRpc().EndMessage();
	}

	void Helpers::RpcSetRole(PlayerControl *player, CustomRpcSender *sender, RoleTypes *role)
	{
		SuperNewRolesPlugin::Logger->LogInfo(player->Data->PlayerName + L" => " + role);
		if (player == nullptr)
		{
			return;
		}
		sender->StartRpc(player->NetId, RpcCalls::SetRole);
		sender->Write(static_cast<unsigned short>(role));
		sender->EndRpc();
		player->SetRole(role);
	}
}
