//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "FixedUpdate.h"
#include "../MapOptions/RandomMap.h"
#include "../Config.h"
#include "../Helpers/CachedPlayer.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Helpers/RPCHelper.h"
#include "../Helpers/MapUtilities.h"
#include "../ModHelpers.h"
#include "../Buttons/VentAndSabo.h"
#include "../CustomOption/CustomOptionDate.h"
#include "LadderDead.h"
#include "../Mode/ModeHandler.h"
#include "../Sabotage/SabotageManager.h"
#include "SetNames.h"
#include "../Roles/Jackal.h"
#include "../Roles/JackalSeer.h"
#include "../Roles/SetTarget.h"
#include "../Roles/Researcher.h"
#include "../Roles/Pursuer.h"
#include "../Roles/RoleClass.h"
#include "../Roles/Hawk.h"
#include "../Roles/NiceHawk.h"
#include "../Roles/MadHawk.h"
#include "../Roles/Vampire.h"
#include "../Roles/DarkKiller.h"
#include "../Roles/Vulture.h"
#include "../Roles/Mafia.h"
#include "../Roles/SerialKiller.h"
#include "../Roles/Kunoichi.h"
#include "../Roles/Minimalist.h"
#include "../MapOptions/MapOption.h"
#include "Clairvoyant.h"
#include "../Roles/Bait.h"
#include "../Mode/SuperHostRoles/BlockTool.h"
#include "../Mode/NotImpostorCheck/NameSet.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;
using namespace SuperNewRoles::Sabotage;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

	void StartGame::Postfix(PlayerControl *__instance)
	{
		MapOptions::RandomMap::Prefix();
		FixedUpdate::IsProDown = ConfigRoles::getCustomProcessDown()->Value;
	}

	void AbilityUpdate::Postfix(AbilityButton *__instance)
	{
		if (CachedPlayer::LocalPlayer->Data->Role.IsSimpleRole && __instance->commsDown.active)
		{
			__instance->commsDown.SetActive(false);
		}
	}

	void DebugManager::Postfix(ControllerManager *__instance)
	{
		if (AmongUsClient::Instance->GameState == AmongUsClient::GameStates::Started)
		{
			if (AmongUsClient::Instance->AmHost && Input->GetKeyDown(KeyCode::H) && Input->GetKey(KeyCode::LeftShift) && Input->GetKey(KeyCode::RightShift))
			{
				SuperNewRoles::Helpers::RPCHelper::EndRPC(RPCHelper::StartRPC(CustomRPC::CustomRPC::SetHaison));
				RPCProcedure::SetHaison();
				ShipStatus::RpcEndGame(GameOverReason::HumansByTask, false);
				MapUtilities::CachedShipStatus->enabled = false;
			}
		}
	}

	void FixedUpdate::setBasePlayerOutlines()
	{
		for (auto target : CachedPlayer::AllPlayers)
		{
			auto rend = SuperNewRoles::ModHelpers::MyRend(target);
			if (target == nullptr || rend == nullptr)
			{
				continue;
			}
			if (rend->material.GetFloat(L"_Outline") == 0.0f)
			{
				continue;
			}
			rend->material.SetFloat(L"_Outline", 0.0f);
		}
	}

bool FixedUpdate::ProDown = false;
bool FixedUpdate::IsProDown = false;

	void FixedUpdate::Postfix(PlayerControl *__instance)
	{
		if (__instance != PlayerControl::LocalPlayer)
		{
			return;
		}
		if (IsProDown)
		{
			ProDown = !ProDown;
			if (ProDown)
			{
				return;
			}
		}
		if (AmongUsClient::Instance->GameState == AmongUsClient::GameStates::Started)
		{
			auto MyRole = PlayerControl::LocalPlayer::getRole();
			setBasePlayerOutlines();
			VentAndSabo::VentButtonVisibilityPatch::Postfix(__instance);
			if (CustomOptions::LadderDead->getBool())
			{
				LadderDead::FixedUpdate();
			}
			auto ThisMode = ModeHandler::GetMode();
			if (ThisMode == ModeId::Default)
			{
				SabotageManager::Update();
				SetNameUpdate::Postfix(__instance);
				Jackal::JackalFixedPatch::Postfix(__instance, MyRole);
				JackalSeer::JackalSeerFixedPatch::Postfix(__instance, MyRole);
				if (PlayerControl::LocalPlayer::isAlive())
				{
					if (PlayerControl::LocalPlayer::isImpostor())
					{
						SetTarget::ImpostorSetTarget();
					}
					switch (MyRole)
					{
						case RoleId::Researcher:
							Researcher::ReseUseButtonSetTargetPatch::Postfix(PlayerControl::LocalPlayer);
							break;
						case RoleId::Pursuer:
							Pursuer::PursureUpdate::Postfix();
							break;
						case RoleId::Levelinger:
							if (RoleClass::Levelinger::IsPower(RoleClass::Levelinger::LevelPowerTypes::Pursuer))
							{
								if (!RoleClass::Pursuer::arrow->arrow->active)
								{
									RoleClass::Pursuer::arrow->arrow->SetActive(true);
								}
								Pursuer::PursureUpdate::Postfix();
							}
							else
							{
								if (RoleClass::Pursuer::arrow->arrow->active)
								{
									RoleClass::Pursuer::arrow->arrow->SetActive(false);
								}
							}
							break;
						case RoleId::Hawk:
							Hawk::FixedUpdate::Postfix();
							break;
						case RoleId::NiceHawk:
							NiceHawk::FixedUpdate::Postfix();
							break;
						case RoleId::MadHawk:
							MadHawk::FixedUpdate::Postfix();
							break;
						case RoleId::Vampire:
							Vampire::FixedUpdate::Postfix();
							break;
						case RoleId::DarkKiller:
							DarkKiller::FixedUpdate::Postfix();
							break;
						case RoleId::Vulture:
							Vulture::FixedUpdate::Postfix();
							break;
						case RoleId::Mafia:
							Mafia::FixedUpdate();
							break;
						case RoleId::SerialKiller:
							SerialKiller::FixedUpdate();
							break;
						case RoleId::Kunoichi:
							Kunoichi::Update();
							break;

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
