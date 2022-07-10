//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "main.h"
#include "../../BotManager.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../Roles/RoleHelper.h"
#include "../../ModHelpers.h"
#include "../ModeHandler.h"
#include "../../Helpers/RPCHelper.h"
#include "../../Main.h"
#include "../../TranslateDate.h"

using namespace SuperNewRoles::Helpers;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::CopsRobbers
{

	void main::ClearAndReloads()
	{
		IsStart = false;
		ArrestPositions = std::unordered_map<int, std::optional<SystemTypes*>>();
		Arrest = std::vector<int>();
		IsMove = false;
		SpawnPosition = std::unordered_map<int, std::optional<SystemTypes*>>();
		LastCount = 0;
	}

bool main::IsStart = false;

	PlayerControl *main::GetBot()
	{
		if (BotManager::AllBots.size() != 0)
		{
			if (BotManager::AllBots[0] != nullptr)
			{
				return BotManager::AllBots[0];
			}
		}
		return nullptr;
	}

std::vector<int> main::Arrest;
std::unordered_map<int, std::optional<SystemTypes*>> main::ArrestPositions;
bool main::IsMove = false;
std::unordered_map<int, std::optional<SystemTypes*>> main::SpawnPosition;

	bool main::IsArrest(PlayerControl *player)
	{
		if (std::find(Arrest.begin(), Arrest.end(), player->PlayerId) != Arrest.end())
		{
			return true;
		}
		return false;
	}

std::unordered_map<MapNames*, std::vector<SystemTypes*>> main::Rooms =
{
	{
		MapNames::Skeld, {SystemTypes::Comms, SystemTypes::Nav, SystemTypes::Security}
	},
	{
		MapNames::Mira, {SystemTypes::Comms, SystemTypes::Greenhouse, SystemTypes::Launchpad, SystemTypes::Storage}
	},
	{
		MapNames::Polus, {SystemTypes::Electrical, SystemTypes::Specimens, SystemTypes::Weapons}
	},
	{
		MapNames::Airship, {SystemTypes::Records, SystemTypes::Security, SystemTypes::VaultRoom}
	}
};

	MapNames *main::GetMap()
	{
		int mapid = PlayerControl::GameOptions::MapId;
		return static_cast<MapNames*>(mapid);
	}

	bool main::EndGameCheck(ShipStatus *__instance)
	{
		bool impostorwin = true;
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (!p->Data->Disconnected)
			{
				if (!SuperNewRoles::RoleHelpers::isImpostor(p) && !SuperNewRoles::Mode::CopsRobbers::main::IsArrest(p))
				{
					impostorwin = false;
				}
			}
		}
		if (impostorwin)
		{
			__instance->enabled = false;
			ShipStatus::RpcEndGame(GameOverReason::ImpostorByKill, false);
			return true;
		}
		else if (GameData::Instance->TotalTasks > 0 && GameData::Instance->TotalTasks <= GameData::Instance->CompletedTasks)
		{
			__instance->enabled = false;
			ShipStatus::RpcEndGame(GameOverReason::HumansByTask, false);
			return true;
		}
		else
		{
			return false;
		}
	}

	void main::ChangeCosmetics()
	{
		for (auto p : CachedPlayer::AllPlayers)
		{
			p->RpcSetPet(L"");
			p->RpcSetVisor(L"");
			if (SuperNewRoles::RoleHelpers::isImpostor(p))
			{
				p->RpcSetColor(1);
				p->RpcSetHat(L"");
				p->RpcSetSkin(L"skin_Police");
			}
			else
			{
				p->RpcSetColor(6);
				p->RpcSetHat(L"hat_pk04_Vagabond");
				p->RpcSetSkin(L"");
			}
		}
	}

	SystemTypes *main::GetRandomSpawnPosition(PlayerControl *player)
	{
		if (SpawnPosition.find(player->PlayerId) == SpawnPosition.end())
		{
			auto type = ModHelpers::GetRandom(Rooms[GetMap()]);
			SpawnPosition[player->PlayerId] = type;
		}
		return static_cast<SystemTypes*>(SpawnPosition[player->PlayerId]);
	}

	SystemTypes *main::SetRandomArrestPosition(PlayerControl *player)
	{
		auto type = ModHelpers::GetRandom(Rooms[GetMap()]);
		ArrestPositions[player->PlayerId] = type;
		Arrest.push_back(player->PlayerId);
		//player.MyPhysics.RpcClimbLadder(null);

		player->RpcSetColor(5);
		player->RpcSetHat(L"");
		player->RpcSetSkin(L"skin_Hazmat");
		player->RpcSetVisor(L"visor_pk01_DumStickerVisor");

		return type;
	}

	void main::RemoveArrest(PlayerControl *player)
	{
		Arrest.Remove(player->PlayerId);

		player->RpcSetColor(6);
		player->RpcSetHat(L"hat_pk04_Vagabond");
		player->RpcSetSkin(L"");
		player->RpcSetVisor(L"");

	}

	Vector2 *main::getPosition(SystemTypes *type)
	{
		//return new Vector2(-13.4818f, -5.3336f);
		auto MAP = GetMap();
		switch (type)
		{
			case SystemTypes::Comms:
				switch (MAP)
				{
					case MapNames::Skeld:
						return new Vector2(4.5f, -15.5f);
					case MapNames::Mira:
						return new Vector2();
				}
				break;
			case SystemTypes::Nav:
				return new Vector2(16.6f, -4.6f);
			case SystemTypes::Security:
				switch (MAP)
				{
					case MapNames::Skeld:

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
