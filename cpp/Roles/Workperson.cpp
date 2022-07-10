#include "Workperson.h"
#include "../CustomRPC/CustomRPC.h"
#include "../CustomOption/CustomOptionDate.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;

namespace SuperNewRoles::Roles
{

	void Workperson::BeginCrewmatePatch::Postfix(ShipStatus *__instance)
	{
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::Workperson))
		{
			PlayerControl::LocalPlayer::generateAndAssignTasks(static_cast<int>(CustomOptions::WorkpersonCommonTask->getFloat()), static_cast<int>(CustomOptions::WorkpersonShortTask->getFloat()), static_cast<int>(CustomOptions::WorkpersonLongTask->getFloat()));
		}
	}
}
