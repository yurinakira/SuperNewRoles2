//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "CustomOptionDate.h"
#include "../TranslateDate.h"
#include "../Config.h"
#include "../MapOptions/MapOption.h"
#include "../Mode/ModeHandler.h"
#include "../MapCustoms/MapCustom.h"
#include "../Sabotage/Options.h"
#include "../Roles/RoleClass.h"
#include "../Patch/SelectTask.h"
#include "../Main.h"

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

std::vector<std::wstring> CustomOptions::rates = {L"0%", L"10%", L"20%", L"30%", L"40%", L"50%", L"60%", L"70%", L"80%", L"90%", L"100%"};
std::vector<std::wstring> CustomOptions::rates4 = {L"0%", L"25%", L"50%", L"75%", L"100%"};
std::vector<std::wstring> CustomOptions::presets = {L"preset1", L"preset2", L"preset3", L"preset4", L"preset5", L"preset6", L"preset7", L"preset8", L"preset9", L"preset10"};
CustomOption *CustomOptions::presetSelection;
CustomOption *CustomOptions::specialOptions;
CustomOption *CustomOptions::hideSettings;
CustomOption *CustomOptions::crewmateRolesCountMax;
CustomOption *CustomOptions::crewmateGhostRolesCountMax;
CustomOption *CustomOptions::impostorRolesCountMax;
CustomOption *CustomOptions::impostorGhostRolesCountMax;
CustomOption *CustomOptions::neutralRolesCountMax;
CustomOption *CustomOptions::neutralGhostRolesCountMax;
CustomOption *CustomOptions::enableMirroMap;
CustomOption *CustomOptions::IsDebugMode;
CustomOption *CustomOptions::DisconnectNotPCOption;
CustomOption *CustomOptions::ZoomOption;
CustomOption *CustomOptions::ClairvoyantZoom;
CustomOption *CustomOptions::MouseZoom;
CustomOption *CustomOptions::ZoomCoolTime;
CustomOption *CustomOptions::ZoomDurationTime;
CustomOption *CustomOptions::DetectiveRate;
CustomOption *CustomOptions::DetectivePlayerCount;
CustomRoleOption *CustomOptions::SoothSayerOption;
CustomOption *CustomOptions::SoothSayerPlayerCount;
CustomOption *CustomOptions::SoothSayerDisplayMode;
CustomOption *CustomOptions::SoothSayerMaxCount;
CustomRoleOption *CustomOptions::JesterOption;
CustomOption *CustomOptions::JesterPlayerCount;
CustomOption *CustomOptions::JesterIsVent;
CustomOption *CustomOptions::JesterIsSabotage;
CustomOption *CustomOptions::JesterIsWinCleartask;
CustomOption *CustomOptions::JesterCommonTask;
CustomOption *CustomOptions::JesterShortTask;
CustomOption *CustomOptions::JesterLongTask;
CustomRoleOption *CustomOptions::LighterOption;
CustomOption *CustomOptions::LighterPlayerCount;
CustomOption *CustomOptions::LighterCoolTime;
CustomOption *CustomOptions::LighterDurationTime;
CustomOption *CustomOptions::LighterUpVision;
CustomRoleOption *CustomOptions::EvilLighterOption;
CustomOption *CustomOptions::EvilLighterPlayerCount;
CustomOption *CustomOptions::EvilLighterCoolTime;
CustomOption *CustomOptions::EvilLighterDurationTime;
CustomRoleOption *CustomOptions::EvilScientistOption;
CustomOption *CustomOptions::EvilScientistPlayerCount;
CustomOption *CustomOptions::EvilScientistCoolTime;
CustomOption *CustomOptions::EvilScientistDurationTime;
CustomRoleOption *CustomOptions::SheriffOption;
CustomOption *CustomOptions::SheriffPlayerCount;
CustomOption *CustomOptions::SheriffCoolTime;
CustomOption *CustomOptions::SheriffMadRoleKill;
CustomOption *CustomOptions::SheriffNeutralKill;
CustomOption *CustomOptions::SheriffLoversKill;
CustomOption *CustomOptions::SheriffKillMaxCount;
CustomRoleOption *CustomOptions::RemoteSheriffOption;
CustomOption *CustomOptions::RemoteSheriffPlayerCount;
CustomOption *CustomOptions::RemoteSheriffCoolTime;
CustomOption *CustomOptions::RemoteSheriffMadRoleKill;
CustomOption *CustomOptions::RemoteSheriffNeutralKill;
CustomOption *CustomOptions::RemoteSheriffLoversKill;
CustomOption *CustomOptions::RemoteSheriffKillMaxCount;
CustomOption *CustomOptions::RemoteSheriffIsKillTeleportSetting;
CustomRoleOption *CustomOptions::MeetingSheriffOption;
CustomOption *CustomOptions::MeetingSheriffPlayerCount;
CustomOption *CustomOptions::MeetingSheriffMadRoleKill;
CustomOption *CustomOptions::MeetingSheriffNeutralKill;
CustomOption *CustomOptions::MeetingSheriffKillMaxCount;
CustomOption *CustomOptions::MeetingSheriffOneMeetingMultiKill;
CustomRoleOption *CustomOptions::JackalOption;
CustomOption *CustomOptions::JackalPlayerCount;
CustomOption *CustomOptions::JackalKillCoolDown;
CustomOption *CustomOptions::JackalUseVent;
CustomOption *CustomOptions::JackalUseSabo;
CustomOption *CustomOptions::JackalIsImpostorLight;
CustomOption *CustomOptions::JackalCreateSidekick;
CustomOption *CustomOptions::JackalNewJackalCreateSidekick;
CustomRoleOption *CustomOptions::TeleporterOption;
CustomOption *CustomOptions::TeleporterPlayerCount;
CustomOption *CustomOptions::TeleporterCoolTime;
CustomOption *CustomOptions::TeleporterDurationTime;
CustomRoleOption *CustomOptions::SpiritMediumOption;
CustomOption *CustomOptions::SpiritMediumPlayerCount;
CustomOption *CustomOptions::SpiritMediumDisplayMode;
CustomOption *CustomOptions::SpiritMediumMaxCount;
CustomRoleOption *CustomOptions::SpeedBoosterOption;
CustomOption *CustomOptions::SpeedBoosterPlayerCount;
CustomOption *CustomOptions::SpeedBoosterCoolTime;
CustomOption *CustomOptions::SpeedBoosterDurationTime;
CustomOption *CustomOptions::SpeedBoosterSpeed;
CustomRoleOption *CustomOptions::EvilSpeedBoosterOption;
CustomOption *CustomOptions::EvilSpeedBoosterPlayerCount;

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
