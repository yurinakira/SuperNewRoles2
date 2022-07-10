//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "RoleHelper.h"
#include "../Mode/Werewolf/main.h"
#include "../BotManager.h"
#include "../ChacheManager/main.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "../PlayerControlHepler.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../Main.h"
#include "../Mode/ModeHandler.h"
#include "../ModHelpers.h"
#include "../Intro/IntroDate.h"

using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles
{

	bool RoleHelpers::isCrew(PlayerControl *player)
	{
		return player != nullptr && !SuperNewRoles::RoleHelpers::isImpostor(player) && !SuperNewRoles::RoleHelpers::isNeutral(player);
	}

	bool RoleHelpers::isImpostor(PlayerControl *player)
	{
		if (SuperNewRoles::RoleHelpers::isRole(player, std::vector<SuperNewRoles::CustomRPC::RoleId>
		{
			{RoleId::Sheriff, RoleId::Sheriff}
		}))
		{
			return false;
		}
		return player != nullptr && player->Data->Role.IsImpostor;
	}

	bool RoleHelpers::isHauntedWolf(PlayerControl *player)
	{
		if (SuperNewRoles::RoleHelpers::isRole(player, std::vector<SuperNewRoles::CustomRPC::RoleId>
		{
			{RoleId::HauntedWolf}
		}))
		{
			return true;
		}
		return player != nullptr && !SuperNewRoles::RoleHelpers::isImpostor(player) && !SuperNewRoles::RoleHelpers::isNeutral(player) && !SuperNewRoles::RoleHelpers::isCrew(player);
	}

	bool RoleHelpers::isMadRole(PlayerControl *player)
	{
		RoleId role = SuperNewRoles::RoleHelpers::getRole(player);
		bool tempVar14;
		switch (role)
		{
			case RoleId::MadMate:
				tempVar14 = true;
				break;
			case RoleId::MadMayor:
				tempVar14 = true;
				break;
			case RoleId::MadStuntMan:
				tempVar14 = true;
				break;
			case RoleId::MadHawk:
				tempVar14 = true;
				break;
			case RoleId::MadJester:
				tempVar14 = true;
				break;
			case RoleId::MadSeer:
				tempVar14 = true;
				break;
			case RoleId::BlackCat:
				tempVar14 = true;
				break;
			case RoleId::MadMaker:
				tempVar14 = true;
				break;
			//isMad
			default:
				tempVar14 = false;
				break;
		}
		return tempVar14;
	}

	bool RoleHelpers::isFriendRole(PlayerControl *player)
	{
		RoleId role = SuperNewRoles::RoleHelpers::getRole(player);
		bool tempVar15;
		switch (role)
		{
			case RoleId::JackalFriends:
				tempVar15 = true;
				break;
			case RoleId::SeerFriends:
				tempVar15 = true;
				break;
			case RoleId::MayorFriends:
				tempVar15 = true;
				break;
			//isFriends
			default:
				tempVar15 = false;
				break;
		}
		return tempVar15;
	}

	bool RoleHelpers::IsQuarreled(PlayerControl *player, bool IsChache)
	{
		if (SuperNewRoles::BotManager::IsBot(player))
		{
			return false;
		}
		if (IsChache)
		{
			try
			{
				if (ChacheManager::QuarreledChache[player->PlayerId] == nullptr)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			catch (...)
			{
				return false;
			}
		}
		for (auto players : RoleClass::Quarreled::QuarreledPlayer)
		{
			for (auto p : players)
			{
				if (p == player)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool RoleHelpers::IsLovers(PlayerControl *player, bool IsChache)
	{
		if (SuperNewRoles::BotManager::IsBot(player))
		{
			return false;
		}
		if (IsChache)
		{
			try
			{
				if (ChacheManager::LoversChache[player->PlayerId] == nullptr)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			catch (...)
			{
				return false;
			}
		}

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
