#include "DeviceClass.h"
#include "MapOption.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace UnityEngine;

namespace SuperNewRoles::MapOptions
{

	bool DeviceClass::MapConsoleUsePatch::Prefix(MapConsole *__instance)
	{
		bool IsUse = MapOption::UseAdmin; /*
	                if (MapOption.UseAdmin)
	                {
	                    if (BlockTool.AdminTime != -10 && BlockTool.AdminTime <= 0)
	                    {
	                        IsUse = false;
	                    }
	                }*/
		return IsUse;
	}

	bool DeviceClass::MapCountOverlayUpdatePatch::Prefix(MapConsole *__instance)
	{
		bool IsUse = MapOption::UseAdmin;
		/*
		if (MapOption.UseAdmin)
		{
		    if (BlockTool.AdminTime > 0)
		    {
		        BlockTool.AdminTime -= Time.fixedDeltaTime;
		        MessageWriter writer = RPCHelper.StartRPC(CustomRPC.CustomRPC.SetDeviceTime);
		        writer.Write(BlockTool.AdminTime);
		        writer.Write((byte)SystemTypes.Admin);
		        writer.EndRPC();
		    }
		    else if (BlockTool.AdminTime != -10 && BlockTool.AdminTime < 0.1)
		    {
		        SuperNewRolesPlugin.Logger.LogInfo("アドミンを無効に設定！");
		        IsUse = false;
		    }
		}*/
		return IsUse;
	}

	void DeviceClass::VitalsDevice::Postfix(VitalsMinigame *__instance)
	{
		if (!MapOption::UseVitalOrDoorLog)
		{
			__instance->Close();
		}
		else
		{
			/*
			if (BlockTool.VitalTime > 0)
			{
			    BlockTool.VitalTime -= Time.fixedDeltaTime;
			    MessageWriter writer = RPCHelper.StartRPC(CustomRPC.CustomRPC.SetDeviceTime);
			    writer.Write(BlockTool.VitalTime);
			    writer.Write((byte)SystemTypes.Medical);
			    writer.EndRPC();
			}
			else if (BlockTool.CameraTime != -10)
			{
			    __instance.Close();
			}
			*/
		}
	}

	void DeviceClass::SurveillanceMinigameUpdatePatch::Postfix(SurveillanceMinigame *__instance)
	{
		if (MapOption::UseCamera == false)
		{
			__instance->Close();
		}
		else
		{
			/*
			if (BlockTool.CameraTime > 0)
			{
			    BlockTool.CameraTime -= Time.fixedDeltaTime;
			    MessageWriter writer = RPCHelper.StartRPC(CustomRPC.CustomRPC.SetDeviceTime);
			    writer.Write(BlockTool.CameraTime);
			    writer.Write((byte)SystemTypes.Security);
			    writer.EndRPC();
			}
			else if (BlockTool.CameraTime != -10)
			{
			    __instance.Close();
			}*/
		}
	}

	void DeviceClass::PlanetSurveillanceMinigameUpdatePatch::Postfix(PlanetSurveillanceMinigame *__instance)
	{
		if (MapOption::UseCamera == false)
		{
			__instance->Close();
		}
		else

		{
		/*
		    if (BlockTool.CameraTime > 0)
		    {
		        BlockTool.CameraTime -= Time.fixedDeltaTime;
		        MessageWriter writer = RPCHelper.StartRPC(CustomRPC.CustomRPC.SetDeviceTime);
		        writer.Write(BlockTool.CameraTime);
		        writer.Write((byte)SystemTypes.Security);
		        writer.EndRPC();
		    }
		    else if (BlockTool.CameraTime != -10)
		    {
		        __instance.Close();
		    }*/
		}
	}

	void DeviceClass::SecurityLogGameUpdatePatch::Postfix(SecurityLogGame *__instance)
	{
		if (MapOption::UseVitalOrDoorLog == false)
		{
			__instance->Close();
		}
		else

		{
		/*
		    if (BlockTool.VitalTime > 0)
		    {
		        BlockTool.VitalTime -= Time.fixedDeltaTime;
		        MessageWriter writer = RPCHelper.StartRPC(CustomRPC.CustomRPC.SetDeviceTime);
		        writer.Write(BlockTool.VitalTime);
		        writer.Write((byte)SystemTypes.Medical);
		        writer.EndRPC();
		    } else if(BlockTool.VitalTime != -10){
		        __instance.Close();
		    }*/
		}
	}
}
