#include "Hawk.h"
#include "../Main.h"
#include "RoleClass.h"
#include "../Helpers/FastDestroyableSingleton.h"

using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void Hawk::TimerEnd()
	{
		/**
		if (PlayerControl.LocalPlayer.isRole(CustomRPC.RoleId.Hawk))
		{
		    MapBehaviour.Instance.Close();
		    FastDestroyableSingleton<HudManager>.Instance.KillButton.gameObject.SetActive(true);
		    FastDestroyableSingleton<HudManager>.Instance.ReportButton.gameObject.SetActive(true);
		    FastDestroyableSingleton<HudManager>.Instance.SabotageButton.gameObject.SetActive(true);
		}
		**/
	}

float Hawk::count = 0;

	void Hawk::FixedUpdate::Postfix()
	{
		SuperNewRolesPlugin::Logger->LogInfo(count);
		SuperNewRolesPlugin::Logger->LogInfo(RoleClass::Hawk::Timer);
		if (RoleClass::Hawk::Timer >= 0.1 && !RoleClass::IsMeeting)
		{
			Camera->main->orthographicSize = RoleClass::Hawk::CameraDefault * 3.0f;
			FastDestroyableSingleton<HudManager*>::getInstance().UICamera->orthographicSize = RoleClass::Hawk::Default * 3.0f;
			if (count == 0)
			{
				count = 1;
				RoleClass::Hawk::Timer = 0;
				return;
			}
		}
		else
		{
			Camera->main->orthographicSize = RoleClass::Hawk::CameraDefault;
			FastDestroyableSingleton<HudManager*>::getInstance().UICamera->orthographicSize = RoleClass::Hawk::Default;
		}
	}
}
