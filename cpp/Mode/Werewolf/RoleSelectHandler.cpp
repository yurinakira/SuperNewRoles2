#include "RoleSelectHandler.h"
#include "../../AllRoleSetClass.h"
#include "../../ChacheManager/main.h"
#include "../../CustomRPC/CustomRPC.h"
#include "../../CustomOption/CustomOptionDate.h"
#include "WerewolfOptions.h"
#include "../../Main.h"

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Werewolf
{

	void RoleSelectHandler::RoleSelect()
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		OneOrNotListSet();
		AllRoleSetClass::AllRoleSet();
		ChacheManager::ResetChache();
	}

	void RoleSelectHandler::OneOrNotListSet()
	{
		std::vector<RoleId> Impoonepar;
		std::vector<RoleId> Imponotonepar;
		std::vector<RoleId> Neutonepar;
		std::vector<RoleId> Neutnotonepar;
		std::vector<RoleId> Crewonepar;
		std::vector<RoleId> Crewnotonepar;
		if (!(StringHelper::replace(CustomOption::CustomOptions::MadMateOption->getString(), L"0%", L"") == L""))
		{
			int OptionDate = std::stoi(StringHelper::replace(CustomOption::CustomOptions::MadMateOption->getString(), L"0%", L""));
			RoleId ThisRoleId = RoleId::MadMate;
			if (OptionDate == 10)
			{
				Crewonepar.push_back(ThisRoleId);
			}
			else
			{
				for (int i = 1; i <= OptionDate; i++)
				{
					Crewnotonepar.push_back(ThisRoleId);
				}
			}
		}
		if (!(StringHelper::replace(CustomOption::CustomOptions::SoothSayerOption->getString(), L"0%", L"") == L""))
		{
			int OptionDate = std::stoi(StringHelper::replace(CustomOption::CustomOptions::SoothSayerOption->getString(), L"0%", L""));
			RoleId ThisRoleId = RoleId::SoothSayer;
			if (OptionDate == 10)
			{
				Crewonepar.push_back(ThisRoleId);
			}
			else
			{
				for (int i = 1; i <= OptionDate; i++)
				{
					Crewnotonepar.push_back(ThisRoleId);
				}
			}
		}
		if (!(StringHelper::replace(CustomOption::CustomOptions::SpiritMediumOption->getString(), L"0%", L"") == L""))
		{
			int OptionDate = std::stoi(StringHelper::replace(CustomOption::CustomOptions::SpiritMediumOption->getString(), L"0%", L""));
			RoleId ThisRoleId = RoleId::SpiritMedium;
			if (OptionDate == 10)
			{
				Crewonepar.push_back(ThisRoleId);
			}
			else
			{
				for (int i = 1; i <= OptionDate; i++)
				{
					Crewnotonepar.push_back(ThisRoleId);
				}
			}
		}
		if (!(StringHelper::replace(Mode::Werewolf::WerewolfOptions::WerewolfHunterOption->getString(), L"0%", L"") == L""))
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"[WereWolf] ADDWOLF@ame");
			int OptionDate = std::stoi(StringHelper::replace(Mode::Werewolf::WerewolfOptions::WerewolfHunterOption->getString(), L"0%", L""));
			RoleId ThisRoleId = RoleId::Hunter;
			if (OptionDate == 10)
			{
				Crewonepar.push_back(ThisRoleId);
			}
			else
			{
				for (int i = 1; i <= OptionDate; i++)
				{
					Crewnotonepar.push_back(ThisRoleId);
				}
			}
		}
		AllRoleSetClass::Impoonepar = Impoonepar;
		AllRoleSetClass::Imponotonepar = Imponotonepar;
		AllRoleSetClass::Neutonepar = Neutonepar;
		AllRoleSetClass::Neutnotonepar = Neutnotonepar;
		AllRoleSetClass::Crewonepar = Crewonepar;
		AllRoleSetClass::Crewnotonepar = Crewnotonepar;
	}
}
