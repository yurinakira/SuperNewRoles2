#include "BestFalseCharge.h"
#include "../../../Roles/RoleClass.h"
#include "../../../Helpers/RPCHelper.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles::Roles
{

	void BestFalseCharge::WrapUp()
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (AmongUsClient::Instance->AmHost && !RoleClass::Bestfalsecharge::IsOnMeeting && RoleClass::IsMeeting)
		{
			for (auto p : RoleClass::Bestfalsecharge::BestfalsechargePlayer)
			{
				SuperNewRoles::Helpers::RPCHelper::RpcInnerExiled(p);
			}
			RoleClass::Bestfalsecharge::IsOnMeeting = true;
		}
	}
}
