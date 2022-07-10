#pragma once

//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "CustomOptionModel.h"
#include "../Patch/LadderDead.h"
#include <string>
#include <unordered_map>
#include <vector>

using namespace BepInEx::Configuration;
using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::MapCustoms;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::CustomOption
{
	class CustomOptions
	{
	public:
		static std::vector<std::wstring> rates;

		static std::vector<std::wstring> rates4;

		static std::vector<std::wstring> presets;
		static CustomOption *presetSelection;

		static CustomOption *specialOptions;
		static CustomOption *hideSettings;

		static CustomOption *crewmateRolesCountMax;
		static CustomOption *crewmateGhostRolesCountMax;
		static CustomOption *impostorRolesCountMax;
		static CustomOption *impostorGhostRolesCountMax;
		static CustomOption *neutralRolesCountMax;
		static CustomOption *neutralGhostRolesCountMax;

		static CustomOption *enableMirroMap;

		static CustomOption *IsDebugMode;

		static CustomOption *DisconnectNotPCOption;

		static CustomOption *ZoomOption;
		static CustomOption *ClairvoyantZoom;
		static CustomOption *MouseZoom;
		static CustomOption *ZoomCoolTime;
		static CustomOption *ZoomDurationTime;

		static CustomOption *DetectiveRate;
		static CustomOption *DetectivePlayerCount;

		static CustomRoleOption *SoothSayerOption;
		static CustomOption *SoothSayerPlayerCount;
		static CustomOption *SoothSayerDisplayMode;
		static CustomOption *SoothSayerMaxCount;

		static CustomRoleOption *JesterOption;
		static CustomOption *JesterPlayerCount;
		static CustomOption *JesterIsVent;
		static CustomOption *JesterIsSabotage;
		static CustomOption *JesterIsWinCleartask;
		static CustomOption *JesterCommonTask;
		static CustomOption *JesterShortTask;
		static CustomOption *JesterLongTask;

		static CustomRoleOption *LighterOption;
		static CustomOption *LighterPlayerCount;
		static CustomOption *LighterCoolTime;
		static CustomOption *LighterDurationTime;
		static CustomOption *LighterUpVision;

		static CustomRoleOption *EvilLighterOption;
		static CustomOption *EvilLighterPlayerCount;
		static CustomOption *EvilLighterCoolTime;
		static CustomOption *EvilLighterDurationTime;

		static CustomRoleOption *EvilScientistOption;
		static CustomOption *EvilScientistPlayerCount;
		static CustomOption *EvilScientistCoolTime;
		static CustomOption *EvilScientistDurationTime;

		static CustomRoleOption *SheriffOption;
		static CustomOption *SheriffPlayerCount;
		static CustomOption *SheriffCoolTime;
		static CustomOption *SheriffMadRoleKill;
		static CustomOption *SheriffNeutralKill;
		static CustomOption *SheriffLoversKill;
		static CustomOption *SheriffKillMaxCount;

		static CustomRoleOption *RemoteSheriffOption;
		static CustomOption *RemoteSheriffPlayerCount;
		static CustomOption *RemoteSheriffCoolTime;
		static CustomOption *RemoteSheriffMadRoleKill;
		static CustomOption *RemoteSheriffNeutralKill;
		static CustomOption *RemoteSheriffLoversKill;
		static CustomOption *RemoteSheriffKillMaxCount;
		static CustomOption *RemoteSheriffIsKillTeleportSetting;

		static CustomRoleOption *MeetingSheriffOption;
		static CustomOption *MeetingSheriffPlayerCount;
		static CustomOption *MeetingSheriffMadRoleKill;
		static CustomOption *MeetingSheriffNeutralKill;
		static CustomOption *MeetingSheriffKillMaxCount;
		static CustomOption *MeetingSheriffOneMeetingMultiKill;

		static CustomRoleOption *JackalOption;
		static CustomOption *JackalPlayerCount;
		static CustomOption *JackalKillCoolDown;
		static CustomOption *JackalUseVent;
		static CustomOption *JackalUseSabo;
		static CustomOption *JackalIsImpostorLight;
		static CustomOption *JackalCreateSidekick;
		static CustomOption *JackalNewJackalCreateSidekick;

		static CustomRoleOption *TeleporterOption;
		static CustomOption *TeleporterPlayerCount;
		static CustomOption *TeleporterCoolTime;
		static CustomOption *TeleporterDurationTime;

		static CustomRoleOption *SpiritMediumOption;
		static CustomOption *SpiritMediumPlayerCount;
		static CustomOption *SpiritMediumDisplayMode;
		static CustomOption *SpiritMediumMaxCount;

		static CustomRoleOption *SpeedBoosterOption;
		static CustomOption *SpeedBoosterPlayerCount;
		static CustomOption *SpeedBoosterCoolTime;
		static CustomOption *SpeedBoosterDurationTime;
		static CustomOption *SpeedBoosterSpeed;


//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
