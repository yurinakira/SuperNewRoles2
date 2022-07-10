#include "Bait.h"
#include "../../../CustomRPC/CustomRPC.h"
#include "../../../Roles/RoleClass.h"
#include "../../../Roles/RoleHelper.h"
#include "../../../LateTask.h"

using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles::Roles
{

	void Bait::MurderPostfix(PlayerControl *__instance, PlayerControl *target)
	{
		if (SuperNewRoles::RoleHelpers::isRole(target, CustomRPC::RoleId::Bait) && (!SuperNewRoles::RoleHelpers::isRole(__instance, CustomRPC::RoleId::Minimalist) || RoleClass::Minimalist::UseReport))
		{
			new LateTask([&] ()
			{
				if (!(SuperNewRoles::RoleHelpers::isRole(__instance, CustomRPC::RoleId::Minimalist) && !RoleClass::Minimalist::UseReport))
				{
					RoleClass::Bait::ReportedPlayer.push_back(target->PlayerId);
					__instance->CmdReportDeadBody(target->Data);
				}
			}, RoleClass::Bait::ReportTime, L"ReportBaitBody");
		}
	}
}
