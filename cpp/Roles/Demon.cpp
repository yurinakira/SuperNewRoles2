#include "Demon.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Helpers/RPCHelper.h"
#include "../Main.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "../BotManager.h"
#include "RoleHelper.h"
#include "../ModHelpers.h"
#include "../Mode/ModeHandler.h"

using namespace Hazel;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{

	void Demon::DemonCurse(PlayerControl *target, PlayerControl *source)
	{
		try
		{
			if (source == nullptr)
			{
				source = PlayerControl::LocalPlayer;
			}
			MessageWriter *Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::DemonCurse);
			Writer->Write(source->PlayerId);
			Writer->Write(target->PlayerId);
			SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
			RPCProcedure::DemonCurse(source->PlayerId, target->PlayerId);
		}
		catch (const std::runtime_error &e)
		{
			SuperNewRolesPlugin::Logger->LogError(e);
		}
	}

	std::vector<PlayerControl*> Demon::GetCurseData(PlayerControl *player)
	{
		return RoleClass::Demon::CurseDatas.find(player->PlayerId) != RoleClass::Demon::CurseDatas.end() ? RoleClass::Demon::CurseDatas[player->PlayerId] : std::vector<PlayerControl*>();
	}

	std::vector<PlayerControl*> Demon::GetUntarget()
	{
		if (RoleClass::Demon::CurseDatas.find(CachedPlayer::LocalPlayer->PlayerId) != RoleClass::Demon::CurseDatas.end())
		{
			return RoleClass::Demon::CurseDatas[CachedPlayer::LocalPlayer->PlayerId];
		}
		return std::vector<PlayerControl*>();
	}

	bool Demon::IsCursed(PlayerControl *source, PlayerControl *target)
	{
		if (source == nullptr || source->Data->Disconnected || target == nullptr || SuperNewRoles::RoleHelpers::isDead(target) || SuperNewRoles::BotManager::IsBot(target))
		{
			return true;
		}
		if (source->PlayerId == target->PlayerId)
		{
			return true;
		}
		if (RoleClass::Demon::CurseDatas.find(source->PlayerId) != RoleClass::Demon::CurseDatas.end())
		{
			if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::Demon::CurseDatas[source->PlayerId], target))
			{
				return true;
			}
		}
		return false;
	}

	std::vector<PlayerControl*> Demon::GetIconPlayers(PlayerControl *player)
	{
		if (player == nullptr)
		{
			player = PlayerControl::LocalPlayer;
		}
		if (RoleClass::Demon::CurseDatas.find(player->PlayerId) != RoleClass::Demon::CurseDatas.end())
		{
			return RoleClass::Demon::CurseDatas[player->PlayerId];
		}
		return std::vector<PlayerControl*>();
	}

	bool Demon::IsViewIcon(PlayerControl *player)
	{
		if (player == nullptr)
		{
			return false;
		}
		for (auto data : RoleClass::Demon::CurseDatas)
		{
			for (PlayerControl *Player : data.Value)
			{
				if (player->PlayerId == Player->PlayerId)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool Demon::IsButton()
	{
		return RoleHelpers::isAlive(PlayerControl::LocalPlayer) && PlayerControl::LocalPlayer::isRole(RoleId::Demon) && ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default});
	}

	bool Demon::IsWin(PlayerControl *Demon)
	{
		for (auto player : CachedPlayer::AllPlayers)
		{
			if (player->PlayerId != Demon->PlayerId && !IsCursed(Demon, player))
			{
				return false;
			}
		}
		if (RoleClass::Demon::IsAliveWin && SuperNewRoles::RoleHelpers::isDead(Demon))
		{
			return false;
		}
		return true;
	}

	bool Demon::IsDemonWinFlag()
	{
		for (auto player : RoleClass::Demon::DemonPlayer)
		{
			if (IsWin(player))
			{
				return true;
			}
		}
		return false;
	}
}
