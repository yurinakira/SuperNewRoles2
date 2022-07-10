#pragma once

#include "../CustomOption/CustomOptionDate.h"
#include "../CustomOption/CustomOptionModel.h"
#include <string>
#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static SuperNewRoles.CustomOption.CustomOptions;

namespace SuperNewRoles::MapOptions
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch] public class MapOption
	class MapOption
	{
	public:
		static bool UseAdmin;
		static bool UseVitalOrDoorLog;
		static bool UseCamera;
		static bool UseDeadBodyReport;
		static bool UseMeetingButton;
		static bool IsRandomMap;
		static bool ValidationSkeld;
		static bool ValidationMira;
		static bool ValidationPolus;
		static bool ValidationAirship;
		static bool ValidationSubmerged;
		static bool IsRestrict;

		//千里眼・ズーム関連
		static bool MouseZoom;
		static bool ClairvoyantZoom;
		static float CoolTime;
		static float DurationTime;
		static bool IsZoomOn;
		static float Timer;
		static DateTime ButtonTimer;
		//private static Sprite buttonSprite;
		static float Default;
		static float CameraDefault;
		static void ClearAndReload();
		static CustomOption::CustomOption *MapOptionSetting;
		static CustomOption::CustomOption *DeviceOptions;
		static CustomOption::CustomOption *DeviceUseAdmin;

		//public static CustomOption.CustomOption DeviceUseAdminTime;
		static CustomOption::CustomOption *DeviceUseVitalOrDoorLog;
		//public static CustomOption.CustomOption DeviceUseVitalOrDoorLogTime;
		static CustomOption::CustomOption *DeviceUseCamera;
		//public static CustomOption.CustomOption DeviceUseCameraTime;
		static CustomOption::CustomOption *NotUseReportDeadBody;
		static CustomOption::CustomOption *NotUseMeetingButton;
		static CustomOption::CustomOption *RandomMapOption;
		static CustomOption::CustomOption *RandomMapSkeld;
		static CustomOption::CustomOption *RandomMapMira;
		static CustomOption::CustomOption *RandomMapPolus;
		static CustomOption::CustomOption *RandomMapAirship;
		static CustomOption::CustomOption *RandomMapSubmerged;

		static CustomOption::CustomOption *RestrictDevicesOption;
		static CustomOption::CustomOption *RestrictAdmin;
		static CustomOption::CustomOption *IsYkundesuBeplnEx;
		static CustomOption::CustomOption *CanUseAdminTime;
		static CustomOption::CustomOption *RestrictCamera;
		static CustomOption::CustomOption *CanUseCameraTime;
		static CustomOption::CustomOption *RestrictVital;
		static CustomOption::CustomOption *CanUseVitalTime;



		static CustomOption::CustomOption *ReactorDurationOption;
		static CustomOption::CustomOption *PolusReactorTimeLimit;
		static CustomOption::CustomOption *MiraReactorTimeLimit;
		static CustomOption::CustomOption *AirshipReactorTimeLimit;


		static CustomOption::CustomOption *VentAnimation;

		static void LoadOption();
	};
}
