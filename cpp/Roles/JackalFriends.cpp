#include "JackalFriends.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleHelper.h"
#include "RoleClass.h"
#include "../Patch/TaskCount.h"

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles
{

std::vector<unsigned char> JackalFriends::CheckedJackal;

	bool JackalFriends::CheckJackal(PlayerControl *p)
	{
		if (std::find(CheckedJackal.begin(), CheckedJackal.end(), p->PlayerId) != CheckedJackal.end())
		{
			return true;
		}
		RoleId role = SuperNewRoles::RoleHelpers::getRole(p);
		int CheckTask = 0;
		switch (role)
		{
			case RoleId::JackalFriends:
				if (!RoleClass::JackalFriends::IsJackalCheck)
				{
					return false;
				}
				CheckTask = RoleClass::JackalFriends::JackalCheckTask;
				break;
			case RoleId::SeerFriends:
				if (!RoleClass::SeerFriends::IsJackalCheck)
				{
					return false;
				}
				CheckTask = RoleClass::SeerFriends::JackalCheckTask;
				break;
			case RoleId::MayorFriends:
				if (!RoleClass::MayorFriends::IsJackalCheck)
				{
					return false;
				}
				CheckTask = RoleClass::MayorFriends::JackalCheckTask;
				break;
			default:
				return false;
		}
		auto taskdata = std::get<0>(TaskCount::TaskDate(p->Data));
		if (CheckTask <= taskdata)
		{
			CheckedJackal.push_back(p->PlayerId);
			return true;
		}
		return false;
	}
}
