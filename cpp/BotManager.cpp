#include "BotManager.h"
#include "Helpers/CachedPlayer.h"
#include "Main.h"
#include "Helpers/RPCHelper.h"
#include "LateTask.h"

using namespace Hazel;
using namespace SuperNewRoles::Helpers;
using namespace UnityEngine;

namespace SuperNewRoles
{

std::vector<PlayerControl*> BotManager::AllBots;

	bool BotManager::IsBot(PlayerControl *player)
	{
		try
		{
			if (player == nullptr)
			{
				return false;
			}
			if (player->Data->Disconnected)
			{
				return false;
			}
			for (auto p : BotManager::AllBots)
			{
				if (p->PlayerId == player->PlayerId)
				{
					return true;
				}
			}
			return false;
		}
		catch (...)
		{
			return false;
		}
	}

	bool BotManager::IsPlayer(PlayerControl *player)
	{
		return !IsBot(player);
	}

	PlayerControl *BotManager::Spawn(const std::wstring &name, unsigned char BotPlayerId)
	{
		unsigned char id = 0;
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (p->PlayerId > id)
			{
				id = p->PlayerId;
			}
		}
		auto Bot = UnityEngine::Object::Instantiate(AmongUsClient::Instance->PlayerPrefab);

		id++;
		/*
		if (id < 14) {
		    id = 15;
		}
		*/
		Bot->PlayerId = id;
		// Bot.PlayerId = BotPlayerId;
		GameData::Instance->AddPlayer(Bot);
		AmongUsClient::Instance->Spawn(Bot, -2, InnerNet::SpawnFlags::IsClientCharacter);
		Bot->transform->position = new Vector3(9999.0f, 9999.0f, 0);
		Bot->NetTransform->enabled = true;

		Bot->RpcSetName(name);
		Bot->RpcSetColor(1);
		Bot->RpcSetHat(L"hat_NoHat");
		Bot->RpcSetPet(L"peet_EmptyPet");
		Bot->RpcSetVisor(L"visor_EmptyVisor");
		Bot->RpcSetNamePlate(L"nameplate_NoPlate");
		Bot->RpcSetSkin(L"skin_None");
		GameData::Instance->RpcSetTasks(Bot->PlayerId, std::vector<unsigned char>(0));
		SuperNewRolesPlugin::Logger->LogInfo(L"botスポーン!\nID:" + Bot->PlayerId + L"\nBotName:" + Bot->name);
		AllBots.push_back(Bot);
		MessageWriter *writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::SetBot);
		writer->Write(Bot->PlayerId);
		new LateTask([&] ()
		{
			SuperNewRoles::Helpers::RPCHelper::EndRPC(writer);
		}, 0.5f);
		return Bot;
	}

	void BotManager::Despawn(PlayerControl *Bot)
	{
		SuperNewRolesPlugin::Logger->LogInfo(L"botデスポーン!\nID:" + Bot->PlayerId + L"\nBotName:" + Bot->name);
		GameData::Instance->RemovePlayer(Bot->PlayerId);
		AmongUsClient::Instance->Despawn(Bot);
		SuperNewRolesPlugin::Logger->LogInfo(L"完了！");
		AllBots.Remove(Bot);
	}

	void BotManager::AllBotDespawn()
	{
		for (auto Bots : AllBots)
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"botデスポーン!\nID:" + Bots->PlayerId + L"\nBotName:" + Bots->name);
			GameData::Instance->RemovePlayer(Bots->PlayerId);
			Bots->Despawn();
			SuperNewRolesPlugin::Logger->LogInfo(L"完了！");
		}
		AllBots = std::vector<PlayerControl*>();
	}
}
