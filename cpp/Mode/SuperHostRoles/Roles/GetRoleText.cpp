#include "GetRoleText.h"
#include "../../../Roles/RoleHelper.h"
#include "../../../CustomRPC/CustomRPC.h"
#include "../../../Roles/RoleClass.h"
#include "../../../ModHelpers.h"
#include "../../../Main.h"

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::SuperHostRoles::Roles
{

	std::wstring GetRoleTextClass::GetRoleTextPostfix(PlayerControl *p)
	{
		std::wstring returndata = L"";
		if (SuperNewRoles::RoleHelpers::isAlive(p))
		{
			if (SuperNewRoles::RoleHelpers::isRole(p, RoleId::SerialKiller))
			{
				if (!(RoleClass::SerialKiller::IsSuicideViews.find(p->PlayerId) == RoleClass::SerialKiller::IsSuicideViews.end() || !RoleClass::SerialKiller::IsSuicideViews[p->PlayerId]))
				{
					float Time;
					std::unordered_map<unsigned char, float>::const_iterator RoleClass.SerialKiller.SuicideTimers_iterator = RoleClass.SerialKiller.SuicideTimers.find(p.PlayerId);
					if (RoleClass::SerialKiller::SuicideTimers_iterator != RoleClass::SerialKiller::SuicideTimers.end())
					{
						Time = RoleClass::SerialKiller::SuicideTimers_iterator->second;
						returndata = ModHelpers::cs(RoleClass::SerialKiller::color, L"(" + std::to_wstring(static_cast<int>(Time) + 1) + L")");
					}
					else
					{
						Time = RoleClass::SerialKiller::SuicideTimers_iterator->second;
					}
				}
			}
		}
		SuperNewRolesPlugin::Logger->LogInfo(L"[SHR:GetRoleText] Return Data:" + returndata);
		return returndata;
	}

	std::wstring GetRoleTextClass::GetNameTextPostfix(PlayerControl *p)
	{
		std::wstring returndata = L"";
		return returndata;
	}
}
