#include "NiceHawk.h"
#include "RoleClass.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../Helpers/CachedPlayer.h"
#include "../Main.h"

using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void NiceHawk::TimerEnd()
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

	void NiceHawk::FixedUpdate::Postfix()
	{
		if (RoleClass::NiceHawk::Timer >= 0.1 && !RoleClass::IsMeeting)
		{
			Camera->main->orthographicSize = RoleClass::NiceHawk::CameraDefault * 3.0f;
			FastDestroyableSingleton<HudManager*>::getInstance().UICamera->orthographicSize = RoleClass::NiceHawk::Default * 3.0f;
		}
		else
		{
			Camera->main->orthographicSize = RoleClass::NiceHawk::CameraDefault;
			FastDestroyableSingleton<HudManager*>::getInstance().UICamera->orthographicSize = RoleClass::NiceHawk::Default;
		}
		if (RoleClass::NiceHawk::timer1 >= 0.1 && !RoleClass::IsMeeting)
		{
			auto TimeSpanDate = TimeSpan(0, 0, 0, static_cast<int>(10));
			RoleClass::NiceHawk::timer1 = static_cast<float>(((Roles->RoleClass.NiceHawk::Timer2 + TimeSpanDate) - DateTime::Now).TotalSeconds);
			CachedPlayer::LocalPlayer->transform->localPosition = RoleClass::NiceHawk::Postion;
			SuperNewRolesPlugin::Logger->LogInfo(RoleClass::NiceHawk::timer1);
		}
	}
}
