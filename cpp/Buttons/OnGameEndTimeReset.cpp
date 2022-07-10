#include "OnGameEndTimeReset.h"
#include "../Roles/SpeedBooster.h"
#include "../Roles/EvilSpeedBooster.h"
#include "../Roles/Lighter.h"
#include "../Roles/RoleClass.h"
#include "../Helpers/FastDestroyableSingleton.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Buttons
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix(AmongUsClient __instance, [HarmonyArgument(0)] ref EndGameResult endGameResult)
	void OnGameTimeEnd::Prefix(AmongUsClient *__instance, EndGameResult *&endGameResult)
	{
		Patch();
	}

	void OnGameTimeEnd::Patch()
	{
		Roles->SpeedBooster::ResetSpeed();
		Roles->EvilSpeedBooster::ResetSpeed();
		Roles->Lighter::LightOutEnd();
		Camera->main->orthographicSize = RoleClass::Hawk::Default;
		FastDestroyableSingleton<HudManager*>::getInstance().UICamera->orthographicSize = RoleClass::Hawk::Default;
		Camera->main->orthographicSize = RoleClass::NiceHawk::Default;
		FastDestroyableSingleton<HudManager*>::getInstance().UICamera->orthographicSize = RoleClass::NiceHawk::Default;
	}
}
