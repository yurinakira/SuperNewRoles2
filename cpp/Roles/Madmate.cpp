#include "Madmate.h"
#include "RoleHelper.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleClass.h"
#include "../Patch/TaskCount.h"

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles
{

std::vector<unsigned char> Madmate::CheckedImpostor;

	bool Madmate::CheckImpostor(PlayerControl *p)
	{
		if (std::find(CheckedImpostor.begin(), CheckedImpostor.end(), p->PlayerId) != CheckedImpostor.end())
		{
			return true;
		}
		int CheckTask = 0;
		switch (SuperNewRoles::RoleHelpers::getRole(p))
		{
			case RoleId::MadMate:
				if (!RoleClass::MadMate::IsImpostorCheck)
				{
					return false;
				}
				CheckTask = RoleClass::MadMate::ImpostorCheckTask;
				break;
			case RoleId::MadMayor:
				if (!RoleClass::MadMayor::IsImpostorCheck)
				{
					return false;
				}
				CheckTask = RoleClass::MadMayor::ImpostorCheckTask;
				break;
			case RoleId::MadJester:
				if (!RoleClass::MadJester::IsImpostorCheck)
				{
					return false;
				}
				CheckTask = RoleClass::MadJester::ImpostorCheckTask;
				break;
			case RoleId::MadSeer:
				if (!RoleClass::MadSeer::IsImpostorCheck)
				{
					return false;
				}
				CheckTask = RoleClass::MadSeer::ImpostorCheckTask;
				break;
			case RoleId::BlackCat:
				if (!RoleClass::BlackCat::IsImpostorCheck)
				{
					return false;
				}
				CheckTask = RoleClass::BlackCat::ImpostorCheckTask;
				break;
			default:
				return false;
		}
		auto taskdata = std::get<0>(TaskCount::TaskDate(p->Data));
		if (CheckTask <= taskdata)
		{
			CheckedImpostor.push_back(p->PlayerId);
			return true;
		}
		return false;
	}
}
