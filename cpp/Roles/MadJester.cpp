#include "MadJester.h"
#include "RoleClass.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleHelper.h"
#include "../Main.h"
#include "../Patch/TaskCount.h"

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles
{

std::vector<unsigned char> MadJester::CheckedImpostor;

	bool MadJester::CheckImpostor(PlayerControl *p)
	{
		if (!RoleClass::MadJester::IsImpostorCheck)
		{
			return false;
		}
		if (!SuperNewRoles::RoleHelpers::isRole(p, RoleId::MadJester))
		{
			return false;
		}
		if (std::find(CheckedImpostor.begin(), CheckedImpostor.end(), p->PlayerId) != CheckedImpostor.end())
		{
			return true;
		}
		/*
		SuperNewRolesPlugin.Logger.LogInfo("�C���|�X�^�[�`�F�b�N�^�X�N��:"+RoleClass.MadJester.ImpostorCheckTask);
		SuperNewRolesPlugin.Logger.LogInfo("�I���^�X�N��:"+TaskCount.TaskDate(p.Data).Item1);*/
		SuperNewRolesPlugin::Logger->LogInfo(L"�L����:" + StringHelper::toString(RoleClass::MadJester::ImpostorCheckTask <= std::get<0>(TaskCount::TaskDate(p->Data))));
		if (RoleClass::MadJester::ImpostorCheckTask <= std::get<0>(TaskCount::TaskDate(p->Data)))
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"�L����Ԃ��܂���");
			return true;
		}
		// SuperNewRolesPlugin.Logger.LogInfo("��ԉ��܂Œʉ�");
		return false;
	}
}
