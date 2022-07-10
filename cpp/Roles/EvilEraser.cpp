//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "EvilEraser.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleHelper.h"
#include "RoleClass.h"
#include "../Helpers/RPCHelper.h"

using namespace Hazel;
using namespace SuperNewRoles::Helpers;

namespace SuperNewRoles::Roles
{

	bool EvilEraser::IsBlock(BlockTypes blocktype, PlayerControl *player)
	{
		if (player == nullptr)
		{
			player = PlayerControl::LocalPlayer;
		}
		if (!SuperNewRoles::RoleHelpers::isRole(player, CustomRPC::RoleId::EvilEraser))
		{
			return false;
		}
		if (RoleClass::EvilEraser::Counts.find(player->PlayerId) != RoleClass::EvilEraser::Counts.end() && RoleClass::EvilEraser::Counts[player->PlayerId] <= 0)
		{
			return false;
		}
		bool tempVar13;
		switch (blocktype)
		{
			case BlockTypes::StuntmanGuard:
				tempVar13 = true;
				break;
			case BlockTypes::ClergymanLightOut:
				tempVar13 = true;
				break;
			case BlockTypes::BaitReport:
				tempVar13 = true;
				break;
			case BlockTypes::RedRidingHoodRevive:
				tempVar13 = true;
				break;
			case BlockTypes::JackalSidekick:
				tempVar13 = true;
				break;
			case BlockTypes::NekomataExiled:
				tempVar13 = true;
				break;
			case BlockTypes::FoxGuard:
				tempVar13 = true;
				break;
			default:
				tempVar13 = false;
				break;
		}
		return tempVar13;
	}

	bool EvilEraser::IsBlockAndTryUse(BlockTypes blocktype, PlayerControl *player)
	{
		bool BlockData = IsBlock(blocktype, player);
		if (BlockData)
		{
			UseCount(player);
		}
		return BlockData;
	}

	void EvilEraser::UseCount(PlayerControl *player)
	{
		MessageWriter *writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::UseEraserCount);
		writer->Write(player->PlayerId);
		SuperNewRoles::Helpers::RPCHelper::EndRPC(writer);
		CustomRPC::RPCProcedure::UseEraserCount(player->PlayerId);
	}

	bool EvilEraser::IsOKAndTryUse(BlockTypes blocktype, PlayerControl *player)
	{
		return !IsBlockAndTryUse(blocktype, player);
	}

bool EvilEraser::IsWinGodGuard = false;

	bool EvilEraser::IsGodWinGuard()
	{
		bool IsAlive = false;
		for (auto p : RoleClass::God::GodPlayer)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p))
			{
				IsAlive = true;
			}
		}
		if (!IsAlive)
		{
			return false;
		}
		if (IsWinGodGuard)
		{
			return true;
		}
		PlayerControl *player = GetOnCount();
		if (player == nullptr)
		{
			return false;
		}
		else
		{
			IsWinGodGuard = true;
			UseCount(player);
		}
		return false;
	}

bool EvilEraser::IsWinFoxGuard = false;

	bool EvilEraser::IsFoxWinGuard()
	{
		bool IsAlive = false;
		for (auto p : RoleClass::Fox::FoxPlayer)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p))
			{
				IsAlive = true;
			}
		}
		if (!IsAlive)
		{
			return false;
		}
		if (IsWinFoxGuard)
		{
			return true;
		}
		PlayerControl *player = GetOnCount();
		if (player == nullptr)
		{
			return false;
		}
		else
		{
			IsWinFoxGuard = true;
			UseCount(player);
		}
		return false;
	}

bool EvilEraser::IsWinNeetGuard = false;

	bool EvilEraser::IsNeetWinGuard()
	{
		bool IsAlive = false;
		for (auto p : RoleClass::Neet::NeetPlayer)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p))
			{
				IsAlive = true;
			}
		}
		if (!IsAlive)
		{
			return false;
		}
		if (IsWinNeetGuard)
		{
			return true;
		}
		PlayerControl *player = GetOnCount();
		if (player == nullptr)
		{
			return false;
		}
		else
		{
			IsWinNeetGuard = true;
			UseCount(player);
		}
		return false;
	}


//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
