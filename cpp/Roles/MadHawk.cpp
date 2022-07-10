#include "MadHawk.h"
#include "RoleClass.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../Helpers/CachedPlayer.h"
#include "../Main.h"

using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void MadHawk::TimerEnd()
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

	void MadHawk::FixedUpdate::Postfix()
	{
		if (RoleClass::MadHawk::Timer >= 0.1 && !RoleClass::IsMeeting)
		{
			Camera->main->orthographicSize = RoleClass::MadHawk::CameraDefault * 3.0f;
			FastDestroyableSingleton<HudManager*>::getInstance().UICamera->orthographicSize = RoleClass::MadHawk::Default * 3.0f;

		}
		else
		{
			Camera->main->orthographicSize = RoleClass::MadHawk::CameraDefault;
			FastDestroyableSingleton<HudManager*>::getInstance().UICamera->orthographicSize = RoleClass::MadHawk::Default;
		}
		if (RoleClass::MadHawk::timer1 >= 0.1 && !RoleClass::IsMeeting)
		{
			auto TimeSpanDate = TimeSpan(0, 0, 0, static_cast<int>(10));
			RoleClass::MadHawk::timer1 = static_cast<float>(((Roles->RoleClass.MadHawk::Timer2 + TimeSpanDate) - DateTime::Now).TotalSeconds);
			CachedPlayer::LocalPlayer->transform->localPosition = RoleClass::MadHawk::Postion;
			SuperNewRolesPlugin::Logger->LogInfo(RoleClass::MadHawk::timer1);
		}
	}
}
