//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "ModeHandler.h"
#include "PlusModeHandler.h"
#include "HideAndSeek/main.h"
#include "BattleRoyal/main.h"
#include "SuperHostRoles/main.h"
#include "Zombie/main.h"
#include "RandomColor/FixedUpdate.h"
#include "RandomColor/RandomColorOptions.h"
#include "NotImpostorCheck/main.h"
#include "Detective/main.h"
#include "Werewolf/main.h"
#include "CopsRobbers/main.h"
#include "SuperHostRoles/BlockTool.h"
#include "HideAndSeek/Intro.h"
#include "BattleRoyal/Intro.h"
#include "SuperHostRoles/Intro.h"
#include "Zombie/Intro.h"
#include "Detective/Intro.h"
#include "Werewolf/Intro.h"
#include "HideAndSeek/HASOptions.h"
#include "BattleRoyal/BROption.h"
#include "Zombie/ZombieOptions.h"
#include "Detective/DetectiveOptions.h"
#include "Werewolf/WerewolfOptions.h"
#include "PlusMode/Options.h"
#include "SuperHostRoles/FixedUpdate.h"
#include "HideAndSeek/Patch.h"
#include "Zombie/FixedUpdate.h"
#include "../Patch/ShareGameVersion.h"
#include "../PlayerControlHepler.h"
#include "SuperHostRoles/EndGameCheck.h"
#include "RandomColor/main.h"
#include "NotImpostorCheck/WinCheck.h"
#include "Detective/WinCheckPatch.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;

namespace SuperNewRoles::Mode
{

	bool CloseDoorsPatch::Prefix(ShipStatus *__instance)
	{
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Zombie}) || ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Werewolf}) || ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::BattleRoyal}) || ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::HideAndSeek}) || ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::CopsRobbers}))
		{
			return false;
		}
		return true;
	}

ModeId ModeHandler::thisMode = static_cast<ModeId>(0);

	void ModeHandler::ClearAndReload()
	{
		PlusModeHandler::ClearAndReload();
		if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::HideAndSeek, false}))
		{
			thisMode = ModeId::HideAndSeek;
			HideAndSeek::main::ClearAndReload();
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::BattleRoyal, false}))
		{
			thisMode = ModeId::BattleRoyal;
			BattleRoyal::main::ClearAndReload();
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles, false}))
		{
			thisMode = ModeId::SuperHostRoles;
			SuperHostRoles::main::ClearAndReloads();
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Zombie, false}))
		{
			thisMode = ModeId::Zombie;
			Zombie::main::ClearAndReload();
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::RandomColor, false}))
		{
			thisMode = ModeId::RandomColor;
			RandomColor::FixedUpdate::UpdateTime = 0.0f;
			RandomColor::FixedUpdate::IsRandomNameColor = RandomColor::RandomColorOptions::RandomNameColor->getBool();
			RandomColor::FixedUpdate::IsHideName = RandomColor::RandomColorOptions::HideName->getBool();
			RandomColor::FixedUpdate::IsRandomColorMeeting = RandomColor::RandomColorOptions::RandomColorMeeting->getBool();
			RandomColor::FixedUpdate::IsHideNameSet = false;
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::NotImpostorCheck, false}))
		{
			thisMode = ModeId::NotImpostorCheck;
			NotImpostorCheck::main::ClearAndReload();
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Detective, false}))
		{
			thisMode = ModeId::Detective;
			Detective::main::ClearAndReload();
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Werewolf, false}))
		{
			thisMode = ModeId::Werewolf;
			Werewolf::main::ClearAndReload();
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::CopsRobbers, false}))
		{
			thisMode = ModeId::CopsRobbers;
			CopsRobbers::main::ClearAndReloads();
		}
		/*            else if (isMode(ModeId.LevelUp, false))
		            {
		                thisMode = ModeId.LevelUp;
		                LevelUp.main.ClearAndReloads();
		            }*/
		else
		{
			thisMode = ModeId::Default;
		}
		if (!isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			SuperHostRoles::BlockTool::IsCom = false;
		}
	}

std::vector<std::wstring> ModeHandler::modes = {ModTranslation::getString(L"HideAndSeekModeName"), ModTranslation::getString(L"SuperHostRolesModeName"), ModTranslation::getString(L"BattleRoyalModeName"), ModTranslation::getString(L"ZombieModeName"), ModTranslation::getString(L"RandomColorModeName"), ModTranslation::getString(L"NotImpostorCheckModeName"), ModTranslation::getString(L"DetectiveModeName"), ModTranslation::getString(L"CopsRobbersModeName")};
const std::wstring ModeHandler::PlayingOnSuperNewRoles = L"Playing on <color=#ffa500>Super</color><color=#ff0000>New</color><color=#00ff00>Roles</color>";
CustomOptionBlank *ModeHandler::Mode;
CustomOption::CustomOption *ModeHandler::ModeSetting;
CustomOption::CustomOption *ModeHandler::ThisModeSetting;

	Il2CppSystem::Collections::Generic::List<PlayerControl*> *ModeHandler::TeamHandler(IntroCutscene *__instance)
	{
		if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::HideAndSeek}))
		{
			return HideAndSeek::Intro::ModeHandler(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::BattleRoyal}))
		{
			return BattleRoyal::Intro::ModeHandler(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			return SuperHostRoles::Intro::ModeHandler(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Zombie}))
		{
			return Zombie::Intro::ModeHandler(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::RandomColor}))
		{
			return SuperHostRoles::Intro::ModeHandler(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::NotImpostorCheck}))
		{
			return SuperHostRoles::Intro::ModeHandler(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Detective}))
		{
			return SuperHostRoles::Intro::ModeHandler(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Werewolf}))
		{
			auto Data = new Il2CppSystem::Collections::Generic->List<PlayerControl*>();
			Data->Add(PlayerControl::LocalPlayer);

//C# TO C++ CONVERTER TODO TASK: A 'delete Data' statement was not added since Data was used in a 'return' or 'throw' statement.
			return Data;
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::CopsRobbers}))
		{
			auto Data = new Il2CppSystem::Collections::Generic->List<PlayerControl*>();
			Data->Add(PlayerControl::LocalPlayer);

//C# TO C++ CONVERTER TODO TASK: A 'delete Data' statement was not added since Data was used in a 'return' or 'throw' statement.
			return Data;
		}
		return new Il2CppSystem::Collections::Generic->List<PlayerControl*>();
	}

	void ModeHandler::IntroHandler(IntroCutscene *__instance)
	{
		if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::HideAndSeek}))
		{
			HideAndSeek::Intro::IntroHandler(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::BattleRoyal}))
		{
			BattleRoyal::Intro::IntroHandler(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			SuperHostRoles::Intro::IntroHandler(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Zombie}))
		{
			Zombie::Intro::IntroHandler(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Detective}))
		{
			SuperHostRoles::Intro::IntroHandler(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Werewolf}))
		{
			SuperHostRoles::Intro::IntroHandler(__instance);
		}
	}

	void ModeHandler::YouAreIntroHandler(IntroCutscene *__instance)
	{
		if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Zombie}))
		{
			Zombie::Intro::YouAreHandle(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Detective}))
		{
			Detective::Intro::YouAreHandle(__instance);
		}
		else if (isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Werewolf}))
		{
			Werewolf::Intro::YouAreHandle(__instance);
		}
	}

	void ModeHandler::OptionLoad()
	{
		Mode = new CustomOptionBlank(nullptr);
		ModeSetting = CustomOption::CustomOption::Create(484, true, CustomOptionType::Generic, L"ModeSetting", false, Mode, true, false, L"");

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
