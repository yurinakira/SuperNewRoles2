#include "MadSeer.h"
#include "RoleClass.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleHelper.h"
#include "../Main.h"
#include "../Patch/TaskCount.h"

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles
{

std::vector<unsigned char> MadSeer::CheckedImpostor;

	bool MadSeer::CheckImpostor(PlayerControl *p)
	{
		if (!RoleClass::MadSeer::IsImpostorCheck)
		{
			return false;
		}
		if (!SuperNewRoles::RoleHelpers::isRole(p, RoleId::MadSeer))
		{
			return false;
		}
		if (std::find(CheckedImpostor.begin(), CheckedImpostor.end(), p->PlayerId) != CheckedImpostor.end())
		{
			return true;
		}
		/*
		SuperNewRolesPlugin.Logger.LogInfo("[MadSeer]Impostor Check Task Count:"+RoleClass.MadSeer.ImpostorCheckTask);
		SuperNewRolesPlugin.Logger.LogInfo("[MadSeer]Finish Task Count:"+TaskCount.TaskDate(p.Data).Item1);*/
		SuperNewRolesPlugin::Logger->LogInfo(L"[MadSeer]Is Validity?:" + StringHelper::toString(RoleClass::MadSeer::ImpostorCheckTask <= std::get<0>(TaskCount::TaskDate(p->Data))));
		if (RoleClass::MadSeer::ImpostorCheckTask <= std::get<0>(TaskCount::TaskDate(p->Data)))
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"[MadSeer]Returned valid.");
			return true;
		}
		// SuperNewRolesPlugin.Logger.LogInfo("[MadSeer]Passed to the Bottom.");
		return false;
	}
}
