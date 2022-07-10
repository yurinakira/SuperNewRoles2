#include "MadMayor.h"
#include "RoleClass.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleHelper.h"
#include "../Main.h"
#include "../Patch/TaskCount.h"

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles
{

std::vector<unsigned char> MadMayor::CheckedImpostor;

	bool MadMayor::CheckImpostor(PlayerControl *p)
	{
		if (!RoleClass::MadMayor::IsImpostorCheck)
		{
			return false;
		}
		if (!SuperNewRoles::RoleHelpers::isRole(p, RoleId::MadMayor))
		{
			return false;
		}
		if (std::find(CheckedImpostor.begin(), CheckedImpostor.end(), p->PlayerId) != CheckedImpostor.end())
		{
			return true;
		}
		/*
		SuperNewRolesPlugin.Logger.LogInfo("インポスターチェックタスク量:"+RoleClass.MadMayor.ImpostorCheckTask);
		SuperNewRolesPlugin.Logger.LogInfo("終了タスク量:"+TaskCount.TaskDate(p.Data).Item1);*/
		SuperNewRolesPlugin::Logger->LogInfo(L"有効か:" + StringHelper::toString(RoleClass::MadMayor::ImpostorCheckTask <= std::get<0>(TaskCount::TaskDate(p->Data))));
		if (RoleClass::MadMayor::ImpostorCheckTask <= std::get<0>(TaskCount::TaskDate(p->Data)))
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"有効を返しました");
			return true;
		}
		// SuperNewRolesPlugin.Logger.LogInfo("一番下まで通過");
		return false;
	}
}
