//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "MapOption.h"
#include "../Mode/SuperHostRoles/BlockTool.h"
#include "../Helpers/FastDestroyableSingleton.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::MapOptions
{

bool MapOption::UseAdmin = false;
bool MapOption::UseVitalOrDoorLog = false;
bool MapOption::UseCamera = false;
bool MapOption::UseDeadBodyReport = false;
bool MapOption::UseMeetingButton = false;
bool MapOption::IsRandomMap = false;
bool MapOption::ValidationSkeld = false;
bool MapOption::ValidationMira = false;
bool MapOption::ValidationPolus = false;
bool MapOption::ValidationAirship = false;
bool MapOption::ValidationSubmerged = false;
bool MapOption::IsRestrict = false;
bool MapOption::MouseZoom = false;
bool MapOption::ClairvoyantZoom = false;
float MapOption::CoolTime = 0;
float MapOption::DurationTime = 0;
bool MapOption::IsZoomOn = false;
float MapOption::Timer = 0;
DateTime MapOption::ButtonTimer;
float MapOption::Default = 0;
float MapOption::CameraDefault = 0;

	void MapOption::ClearAndReload()
	{
		if (MapOptionSetting->getBool())
		{
			if (DeviceOptions->getBool())
			{
				UseAdmin = DeviceUseAdmin->getBool();
				UseVitalOrDoorLog = DeviceUseVitalOrDoorLog->getBool();
				UseCamera = DeviceUseCamera->getBool();
			}
			else
			{
				UseAdmin = true;
				UseVitalOrDoorLog = true;
				UseCamera = true;
			}
			if (RandomMapOption->getBool())
			{
				IsRandomMap = true;
				ValidationSkeld = RandomMapSkeld->getBool();
				ValidationMira = RandomMapMira->getBool();
				ValidationPolus = RandomMapPolus->getBool();
				ValidationAirship = RandomMapAirship->getBool();
				ValidationSubmerged = RandomMapSubmerged->getBool();
			}
			else
			{
				IsRandomMap = false;
				ValidationSkeld = false;
				ValidationMira = false;
				ValidationPolus = false;
				ValidationAirship = false;
				ValidationSubmerged = false;
			}
			UseDeadBodyReport = !NotUseReportDeadBody->getBool();
			UseMeetingButton = !NotUseMeetingButton->getBool();
			//SuperNewRoles.Patch.AdminPatch.ClearAndReload();
			//SuperNewRoles.Patch.CameraPatch.ClearAndReload();
			//SuperNewRoles.Patch.VitalsPatch.ClearAndReload();
		}
		else
		{
			UseAdmin = true;
			UseVitalOrDoorLog = true;
			UseCamera = true;
			UseDeadBodyReport = true;
			UseMeetingButton = true;
			IsRandomMap = false;
			ValidationSkeld = false;
			ValidationMira = false;
			ValidationPolus = false;
			ValidationAirship = false;
			ValidationSubmerged = false;
		}
		BlockTool::OldDesyncCommsPlayers = std::vector<unsigned char>();
		BlockTool::CameraPlayers = std::vector<unsigned char>();
		//BlockTool.VitalPlayers = new();
		//BlockTool.AdminPlayers = new();
		/*
		if (DeviceUseCameraTime.getFloat() == 0 || !UseCamera)
		{
		    BlockTool.CameraTime = -10;
		} else
		{
		    BlockTool.CameraTime = DeviceUseCameraTime.getFloat();
		}
		if (DeviceUseVitalOrDoorLogTime.getFloat() == 0 || !UseVitalOrDoorLog)
		{
		    BlockTool.VitalTime = -10;
		}
		else
		{
		    BlockTool.VitalTime = DeviceUseVitalOrDoorLogTime.getFloat();
		}
		if (DeviceUseAdminTime.getFloat() == 0 || !UseAdmin)
		{
		    BlockTool.AdminTime = -10;
		}
		else
		{
		    BlockTool.AdminTime = DeviceUseAdminTime.getFloat();
		}*/
		PolusReactorTimeLimit->getFloat();
		MiraReactorTimeLimit->getFloat();
		AirshipReactorTimeLimit->getFloat();

		//千里眼・ズーム関連
		ClairvoyantZoom = CustomOptions::ClairvoyantZoom->getBool();
		MouseZoom = CustomOptions::MouseZoom->getBool();
		CoolTime = CustomOptions::ZoomCoolTime->getFloat();
		DurationTime = CustomOptions::ZoomDurationTime->getFloat();
		IsZoomOn = false;
		Timer = 0;
		ButtonTimer = DateTime::Now;
		CameraDefault = Camera->main.orthographicSize;
		Default = FastDestroyableSingleton<HudManager*>::getInstance().UICamera::orthographicSize;
	}

CustomOption::CustomOption *MapOption::MapOptionSetting;
CustomOption::CustomOption *MapOption::DeviceOptions;
CustomOption::CustomOption *MapOption::DeviceUseAdmin;
CustomOption::CustomOption *MapOption::DeviceUseVitalOrDoorLog;
CustomOption::CustomOption *MapOption::DeviceUseCamera;
CustomOption::CustomOption *MapOption::NotUseReportDeadBody;
CustomOption::CustomOption *MapOption::NotUseMeetingButton;
CustomOption::CustomOption *MapOption::RandomMapOption;
CustomOption::CustomOption *MapOption::RandomMapSkeld;
CustomOption::CustomOption *MapOption::RandomMapMira;
CustomOption::CustomOption *MapOption::RandomMapPolus;
CustomOption::CustomOption *MapOption::RandomMapAirship;
CustomOption::CustomOption *MapOption::RandomMapSubmerged;
CustomOption::CustomOption *MapOption::RestrictDevicesOption;
CustomOption::CustomOption *MapOption::RestrictAdmin;
CustomOption::CustomOption *MapOption::IsYkundesuBeplnEx;
CustomOption::CustomOption *MapOption::CanUseAdminTime;
CustomOption::CustomOption *MapOption::RestrictCamera;
CustomOption::CustomOption *MapOption::CanUseCameraTime;
CustomOption::CustomOption *MapOption::RestrictVital;
CustomOption::CustomOption *MapOption::CanUseVitalTime;

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
