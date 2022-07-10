//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "CountChanger.h"
#include "RoleClass.h"
#include "../ModHelpers.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleHelper.h"

namespace SuperNewRoles::Roles
{

	void CountChanger::CountChangerPatch::WrapUpPatch()
	{
		RoleClass::CountChanger::IsSet = false;
		RoleClass::CountChanger::ChangeData = RoleClass::CountChanger::Setdata;
		RoleClass::CountChanger::Setdata = std::unordered_map<int, int>();
	}

	bool CountChanger::isChange(PlayerControl *p)
	{
		if (RoleClass::CountChanger::ChangeData.find(p->PlayerId) != RoleClass::CountChanger::ChangeData.end())
		{
			return true;
		}
		else if (RoleClass::CountChanger::ChangeData.ContainsValue(p->PlayerId))
		{
			return true;
		}
		return false;
	}

	TeamRoleType CountChanger::GetRoleType(PlayerControl *p)
	{
		if (RoleClass::CountChanger::ChangeData.find(p->PlayerId) != RoleClass::CountChanger::ChangeData.end())
		{
			auto player = ModHelpers::playerById(static_cast<unsigned char>(RoleClass::CountChanger::ChangeData[p->PlayerId]));
			return Get(player);
		}
		else if (RoleClass::CountChanger::ChangeData.ContainsValue(p->PlayerId))
		{
			return Get(ModHelpers::playerById(static_cast<unsigned char>(SuperNewRoles::ModHelpers::GetKey(RoleClass::CountChanger::ChangeData, p->PlayerId))));
		}
		else
		{
			return Get(p);
		}
	}

	bool CountChanger::IsChangeMadmate(PlayerControl *p)
	{
		auto getroledata = GetRoleType(p);
		if (getroledata == TeamRoleType::Crewmate)
		{
			if (RoleClass::CountChanger::ChangeData.find(p->PlayerId) != RoleClass::CountChanger::ChangeData.end())
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(RoleClass::CountChanger::ChangeData[p->PlayerId])), CustomRPC::RoleId::MadMate))
				{
					return true;
				}
			}
			else if (RoleClass::CountChanger::ChangeData.ContainsValue(p->PlayerId))
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(SuperNewRoles::ModHelpers::GetKey(RoleClass::CountChanger::ChangeData, p->PlayerId))), CustomRPC::RoleId::MadMate))
				{
					return true;
				}
			}
			else
			{
				return SuperNewRoles::RoleHelpers::isRole(p, CustomRPC::RoleId::MadMate);
			}
		}
		return false;
	}

	bool CountChanger::IsChangeMadMayor(PlayerControl *p)
	{
		auto getroledata = GetRoleType(p);
		if (getroledata == TeamRoleType::Crewmate)
		{
			if (RoleClass::CountChanger::ChangeData.find(p->PlayerId) != RoleClass::CountChanger::ChangeData.end())
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(RoleClass::CountChanger::ChangeData[p->PlayerId])), CustomRPC::RoleId::MadMayor))
				{
					return true;
				}
			}
			else if (RoleClass::CountChanger::ChangeData.ContainsValue(p->PlayerId))
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(SuperNewRoles::ModHelpers::GetKey(RoleClass::CountChanger::ChangeData, p->PlayerId))), CustomRPC::RoleId::MadMayor))
				{
					return true;
				}
			}
			else
			{
				return SuperNewRoles::RoleHelpers::isRole(p, CustomRPC::RoleId::MadMayor);
			}
		}
		return false;
	}

	bool CountChanger::IsChangeMadStuntMan(PlayerControl *p)
	{
		auto getroledata = GetRoleType(p);
		if (getroledata == TeamRoleType::Crewmate)
		{
			if (RoleClass::CountChanger::ChangeData.find(p->PlayerId) != RoleClass::CountChanger::ChangeData.end())
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(RoleClass::CountChanger::ChangeData[p->PlayerId])), CustomRPC::RoleId::MadStuntMan))
				{
					return true;
				}
			}
			else if (RoleClass::CountChanger::ChangeData.ContainsValue(p->PlayerId))
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(SuperNewRoles::ModHelpers::GetKey(RoleClass::CountChanger::ChangeData, p->PlayerId))), CustomRPC::RoleId::MadStuntMan))
				{
					return true;
				}
			}
			else
			{
				return SuperNewRoles::RoleHelpers::isRole(p, CustomRPC::RoleId::MadStuntMan);
			}
		}
		return false;
	}

	bool CountChanger::IsChangeMadJester(PlayerControl *p)
	{
		auto getroledata = GetRoleType(p);
		if (getroledata == TeamRoleType::Crewmate)
		{
			if (RoleClass::CountChanger::ChangeData.find(p->PlayerId) != RoleClass::CountChanger::ChangeData.end())
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(RoleClass::CountChanger::ChangeData[p->PlayerId])), CustomRPC::RoleId::MadJester))
				{
					return true;
				}
			}
			else if (RoleClass::CountChanger::ChangeData.ContainsValue(p->PlayerId))
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(SuperNewRoles::ModHelpers::GetKey(RoleClass::CountChanger::ChangeData, p->PlayerId))), CustomRPC::RoleId::MadJester))
				{
					return true;
				}
			}
			else
			{
				return SuperNewRoles::RoleHelpers::isRole(p, CustomRPC::RoleId::MadJester);
			}
		}
		return false;
	}

	bool CountChanger::IsChangeMadHawk(PlayerControl *p)
	{
		auto getroledata = GetRoleType(p);
		if (getroledata == TeamRoleType::Crewmate)
		{
			if (RoleClass::CountChanger::ChangeData.find(p->PlayerId) != RoleClass::CountChanger::ChangeData.end())
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(RoleClass::CountChanger::ChangeData[p->PlayerId])), CustomRPC::RoleId::MadHawk))
				{
					return true;
				}
			}
			else if (RoleClass::CountChanger::ChangeData.ContainsValue(p->PlayerId))
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(SuperNewRoles::ModHelpers::GetKey(RoleClass::CountChanger::ChangeData, p->PlayerId))), CustomRPC::RoleId::MadHawk))
				{
					return true;
				}
			}
			else
			{
				return SuperNewRoles::RoleHelpers::isRole(p, CustomRPC::RoleId::MadHawk);
			}
		}
		return false;
	}

	bool CountChanger::IsChangeMadSeer(PlayerControl *p)
	{
		auto getroledata = GetRoleType(p);
		if (getroledata == TeamRoleType::Crewmate)
		{
			if (RoleClass::CountChanger::ChangeData.find(p->PlayerId) != RoleClass::CountChanger::ChangeData.end())
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(RoleClass::CountChanger::ChangeData[p->PlayerId])), CustomRPC::RoleId::MadSeer))
				{
					return true;
				}
			}
			else if (RoleClass::CountChanger::ChangeData.ContainsValue(p->PlayerId))
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(SuperNewRoles::ModHelpers::GetKey(RoleClass::CountChanger::ChangeData, p->PlayerId))), CustomRPC::RoleId::MadSeer))
				{
					return true;
				}
			}
			else
			{
				return SuperNewRoles::RoleHelpers::isRole(p, CustomRPC::RoleId::MadSeer);
			}
		}
		return false;
	}

	bool CountChanger::IsChangeMadMaker(PlayerControl *p)
	{
		auto getroledata = GetRoleType(p);
		if (getroledata == TeamRoleType::Crewmate)
		{
			if (RoleClass::CountChanger::ChangeData.find(p->PlayerId) != RoleClass::CountChanger::ChangeData.end())
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(RoleClass::CountChanger::ChangeData[p->PlayerId])), CustomRPC::RoleId::MadMaker))
				{
					return true;
				}
			}
			else if (RoleClass::CountChanger::ChangeData.ContainsValue(p->PlayerId))
			{
				if (SuperNewRoles::RoleHelpers::isRole(ModHelpers::playerById(static_cast<unsigned char>(SuperNewRoles::ModHelpers::GetKey(RoleClass::CountChanger::ChangeData, p->PlayerId))), CustomRPC::RoleId::MadMaker))
				{
					return true;
				}
			}

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
