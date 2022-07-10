//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "SyncSetting.h"
#include "../ModeHandler.h"
#include "../../Roles/RoleHelper.h"
#include "../../CustomRPC/CustomRPC.h"
#include "../../Roles/RoleClass.h"
#include "../../Helpers/MapUtilities.h"
#include "../../CustomOption/CustomOptionDate.h"
#include "../../PlayerControlHepler.h"
#include "../../ModHelpers.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../BotManager.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::SuperHostRoles
{

GameOptionsData *SyncSetting::OptionData;

	void SyncSetting::CustomSyncSettings(PlayerControl *player)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (!ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			return;
		}
		auto role = SuperNewRoles::RoleHelpers::getRole(player);
		auto optdata = SuperNewRoles::Mode::SuperHostRoles::SyncSetting::DeepCopy(OptionData);
		switch (role)
		{
			case RoleId::Jester:
				if (RoleClass::Jester::IsUseVent)
				{
					optdata->RoleOptions->EngineerCooldown = 0.0f;
					optdata->RoleOptions->EngineerInVentMaxTime = 0.0f;
				}
				break;
			case RoleId::Sheriff:
			{
				optdata->ImpostorLightMod = optdata->CrewLightMod;
				auto switchSystem = MapUtilities::getSystems()[SystemTypes::Electrical].CastFast<SwitchSystem*>();
				if (switchSystem != nullptr && switchSystem->IsActive)
				{
					optdata->ImpostorLightMod /= 5;
				}
				optdata->KillCooldown = KillCoolSet(CustomOptions::SheriffCoolTime->getFloat());
				break;
			}
			case RoleId::Minimalist:
				optdata->KillCooldown = KillCoolSet(RoleClass::Minimalist::KillCoolTime);
				break;
			case RoleId::Samurai:
				optdata->KillCooldown = KillCoolSet(RoleClass::Samurai::KillCoolTime);
				optdata->RoleOptions->ShapeshifterCooldown = RoleClass::Samurai::SwordCoolTime;
				optdata->RoleOptions->ShapeshifterDuration = 1.0f;
				break;
			case RoleId::God:
				optdata->AnonymousVotes = !RoleClass::God::IsVoteView;
				break;
			case RoleId::Observer:
				optdata->AnonymousVotes = !RoleClass::Observer::IsVoteView;
				break;
			case RoleId::MadMate:
				if (RoleClass::MadMate::IsUseVent)
				{
					optdata->RoleOptions->EngineerCooldown = 0.0f;
					optdata->RoleOptions->EngineerInVentMaxTime = 0.0f;
				}
				if (RoleClass::MadMate::IsImpostorLight)
				{
					optdata->CrewLightMod = optdata->ImpostorLightMod;
					auto switchSystem2 = MapUtilities::getSystems()[SystemTypes::Electrical].CastFast<SwitchSystem*>();
					if (switchSystem2 != nullptr && switchSystem2->IsActive)
					{
						optdata->CrewLightMod = optdata->ImpostorLightMod * 15;
					}
				}
				break;
			case RoleId::MadMayor:
				if (RoleClass::MadMayor::IsUseVent)
				{
					optdata->RoleOptions->EngineerCooldown = 0.0f;
					optdata->RoleOptions->EngineerInVentMaxTime = 0.0f;
				}
				if (RoleClass::MadMayor::IsImpostorLight)
				{
					optdata->CrewLightMod = optdata->ImpostorLightMod;
					auto switchSystem2 = MapUtilities::getSystems()[SystemTypes::Electrical].CastFast<SwitchSystem*>();
					if (switchSystem2 != nullptr && switchSystem2->IsActive)
					{
						optdata->CrewLightMod = optdata->ImpostorLightMod * 15;
					}
				}
				break;
			case RoleId::MadStuntMan:
				if (RoleClass::MadStuntMan::IsUseVent)
				{
					optdata->RoleOptions->EngineerCooldown = 0.0f;
					optdata->RoleOptions->EngineerInVentMaxTime = 0.0f;
				}
				if (RoleClass::MadStuntMan::IsImpostorLight)
				{
					optdata->CrewLightMod = optdata->ImpostorLightMod;
					auto switchSystem2 = MapUtilities::getSystems()[SystemTypes::Electrical].CastFast<SwitchSystem*>();
					if (switchSystem2 != nullptr && switchSystem2->IsActive)
					{
						optdata->CrewLightMod = optdata->ImpostorLightMod * 15;
					}
				}
				break;
			case RoleId::MadJester:
				if (RoleClass::MadJester::IsUseVent)
				{
					optdata->RoleOptions->EngineerCooldown = 0.0f;
					optdata->RoleOptions->EngineerInVentMaxTime = 0.0f;
				}
				if (RoleClass::MadJester::IsImpostorLight)
				{
					optdata->CrewLightMod = optdata->ImpostorLightMod;
					auto switchSystem2 = MapUtilities::getSystems()[SystemTypes::Electrical].CastFast<SwitchSystem*>();
					if (switchSystem2 != nullptr && switchSystem2->IsActive)
					{
						optdata->CrewLightMod = optdata->ImpostorLightMod * 15;
					}
				}
				break;
			case RoleId::MadMaker:
				if (!SuperNewRoles::PlayerControlHepler::IsMod(player))
				{
					if (!RoleClass::MadMaker::IsImpostorLight)
					{
						optdata->ImpostorLightMod = optdata->CrewLightMod;
						auto switchSystemMadMaker = MapUtilities::getSystems()[SystemTypes::Electrical].CastFast<SwitchSystem*>();
						if (switchSystemMadMaker != nullptr && switchSystemMadMaker->IsActive)
						{
							optdata->ImpostorLightMod /= 5;
						}
					}
				}
				if (SuperNewRoles::PlayerControlHepler::IsMod(player))
				{
					if (RoleClass::MadMaker::IsImpostorLight)
					{
						optdata->CrewLightMod = optdata->ImpostorLightMod;
						auto switchSystem2 = MapUtilities::CachedShipStatus->Systems[SystemTypes::Electrical].CastFast<SwitchSystem*>();
						if (switchSystem2 != nullptr && switchSystem2->IsActive)
						{
							optdata->CrewLightMod = optdata->ImpostorLightMod * 15;
						}
					}
				}
				if (std::find(RoleClass::MadMaker::CreatePlayers.begin(), RoleClass::MadMaker::CreatePlayers.end(), player->PlayerId) != RoleClass::MadMaker::CreatePlayers.end())
				{
					optdata->KillCooldown = -1.0f;
				}
				else
				{
					optdata->KillCooldown = 0.001f;
				}
				break;
			case RoleId::JackalFriends:

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
