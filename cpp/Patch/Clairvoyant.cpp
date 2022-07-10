#include "Clairvoyant.h"
#include "../Main.h"
#include "../MapOptions/MapOption.h"
#include "../Roles/RoleClass.h"
#include "../Helpers/FastDestroyableSingleton.h"

using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

	void Clairvoyant::TimerEnd()
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

float Clairvoyant::count = 0;

	void Clairvoyant::FixedUpdate::Postfix()
	{
		SuperNewRolesPlugin::Logger->LogInfo(count);
		SuperNewRolesPlugin::Logger->LogInfo(MapOptions::MapOption::Timer);
		if (MapOptions::MapOption::Timer >= 0.1 && !Roles->RoleClass::IsMeeting)
		{
			Camera->main->orthographicSize = MapOptions::MapOption::CameraDefault * 3.0f;
			FastDestroyableSingleton<HudManager*>::getInstance().UICamera->orthographicSize = MapOptions::MapOption::Default * 3.0f;
			if (count == 0)
			{
				count = 1;
				MapOptions::MapOption::Timer = 0;
				return;
			}
		}
		else
		{
			Camera->main->orthographicSize = MapOptions::MapOption::CameraDefault;
			FastDestroyableSingleton<HudManager*>::getInstance().UICamera->orthographicSize = MapOptions::MapOption::Default;
		}
	}
}
