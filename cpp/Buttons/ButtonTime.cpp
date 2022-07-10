//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "ButtonTime.h"
#include "../Helpers/CachedPlayer.h"
#include "../Roles/RoleClass.h"
#include "Buttons.h"
#include "../Roles/Scientist.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Roles/NiceHawk.h"
#include "../Roles/MadHawk.h"
#include "../Roles/Hawk.h"
#include "../MapOptions/MapOption.h"
#include "../Patch/Clairvoyant.h"
#include "../Roles/Lighter.h"
#include "../Roles/SpeedBooster.h"
#include "../Roles/EvilSpeedBooster.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace SuperNewRoles::Buttons
{

	void ButtonTime::Update()
	{
		try
		{
			ClergymanDuration();
		}
		catch (...)
		{
		}
		HawkDuration();
		ClairvoyantDuration();
	}

	void ButtonTime::ScientistButton()
	{
		float durationtime;
		float cooltime;
		if (CachedPlayer::LocalPlayer->Data->Role.IsImpostor)
		{
			durationtime = RoleClass::EvilScientist::DurationTime;
			cooltime = RoleClass::EvilScientist::CoolTime;
		}
		else
		{
			durationtime = RoleClass::NiceScientist::DurationTime;
			cooltime = RoleClass::NiceScientist::CoolTime;
		}
		if (Roles->RoleClass.NiceScientist::IsScientist)
		{
			auto TimeSpanDate = TimeSpan(0, 0, 0, static_cast<int>(durationtime));
			Buttons::HudManagerStartPatch::ScientistButton->MaxTimer = durationtime;
			Buttons::HudManagerStartPatch::ScientistButton->Timer = static_cast<float>(((Roles->RoleClass.NiceScientist::ButtonTimer + TimeSpanDate) - DateTime::Now).TotalSeconds);
			if (Buttons::HudManagerStartPatch::ScientistButton->Timer <= 0.0f)
			{
				Roles->Scientist::ScientistEnd();
				Roles->Scientist::ResetCoolDown();
				Buttons::HudManagerStartPatch::ScientistButton->MaxTimer = cooltime;
				Roles->RoleClass.NiceScientist::IsScientist = false;
				Buttons::HudManagerStartPatch::ScientistButton->actionButton->cooldownTimerText->color = Color::white;
				Roles->RoleClass.NiceScientist::ButtonTimer = DateTime::Now;
			}
		}
		else
		{
			auto TimeSpanDate = TimeSpan(0, 0, 0, static_cast<int>(cooltime));
			Buttons::HudManagerStartPatch::ScientistButton->Timer = static_cast<float>(((Roles->RoleClass.NiceScientist::ButtonTimer + TimeSpanDate) - DateTime::Now).TotalSeconds);
			if (Buttons::HudManagerStartPatch::ScientistButton->Timer <= 0.0f)
			{
				Buttons::HudManagerStartPatch::ScientistButton->Timer = 0.0f;
			}
			return;
		}
	}

	void ButtonTime::HawkDuration()
	{
		if (RoleClass::Hawk::Timer == 0 && PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::Hawk))
		{
			return;
		}
		if (RoleClass::NiceHawk::Timer == 0 && PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::NiceHawk))
		{
			return;
		}
		if (RoleClass::MadHawk::Timer == 0 && PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::MadHawk))
		{
			return;
		}
		RoleClass::Hawk::IsHawkOn = true;
		auto TimeSpanDate = TimeSpan(0, 0, 0, static_cast<int>(Roles->RoleClass.Hawk::DurationTime));
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::NiceHawk))
		{
			TimeSpanDate = TimeSpan(0, 0, 0, static_cast<int>(Roles->RoleClass.NiceHawk::DurationTime));
			RoleClass::NiceHawk::Timer = static_cast<float>(((Roles->RoleClass.NiceHawk::ButtonTimer + TimeSpanDate) - DateTime::Now).TotalSeconds);
			if (RoleClass::NiceHawk::Timer <= 0.0f)
			{
				RoleClass::NiceHawk::Timer = 0.0f;
			}
			NiceHawk::TimerEnd();
			RoleClass::Hawk::IsHawkOn = false;
			return;
		}
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::MadHawk))
		{
			TimeSpanDate = TimeSpan(0, 0, 0, static_cast<int>(Roles->RoleClass.MadHawk::DurationTime));
			RoleClass::MadHawk::Timer = static_cast<float>(((Roles->RoleClass.MadHawk::ButtonTimer + TimeSpanDate) - DateTime::Now).TotalSeconds);
			if (RoleClass::MadHawk::Timer <= 0.0f)
			{
				RoleClass::MadHawk::Timer = 0.0f;
			}
			MadHawk::TimerEnd();
			RoleClass::Hawk::IsHawkOn = false;
			return;
		}
		RoleClass::Hawk::Timer = static_cast<float>(((Roles->RoleClass.Hawk::ButtonTimer + TimeSpanDate) - DateTime::Now).TotalSeconds);
		if (RoleClass::Hawk::Timer <= 0.0f && PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::Hawk))
		{
			RoleClass::Hawk::Timer = 0.0f;
		}
		Hawk::TimerEnd();
		RoleClass::Hawk::IsHawkOn = false;
		return;
	}

	void ButtonTime::ClairvoyantDuration()
	{
		if (MapOptions::MapOption::Timer == 0 && PlayerControl::LocalPlayer::Data->IsDead && MapOptions::MapOption::ClairvoyantZoom)
		{
			return;
		}
		MapOptions::MapOption::IsZoomOn = true;
		auto TimeSpanDate = TimeSpan(0, 0, 0, static_cast<int>(MapOptions::MapOption::DurationTime));
		TimeSpanDate = TimeSpan(0, 0, 0, static_cast<int>(MapOptions::MapOption::DurationTime));
		MapOptions::MapOption::Timer = static_cast<float>(((MapOptions::MapOption::ButtonTimer + TimeSpanDate) - DateTime::Now).TotalSeconds);
		if (MapOptions::MapOption::Timer <= 0.0f)
		{
			MapOptions::MapOption::Timer = 0.0f;
		}
		Patch::Clairvoyant::TimerEnd();
		MapOptions::MapOption::IsZoomOn = false;
		return;
	}

	void ButtonTime::TeleporterButton()
	{
		if (Roles->RoleClass.Teleporter::ButtonTimer == nullptr)
		{
			Roles->RoleClass.Teleporter::ButtonTimer = DateTime::Now;
		}
		auto TimeSpanDate = TimeSpan(0, 0, 0, static_cast<int>(Roles->RoleClass.Teleporter::CoolTime));
		Buttons::HudManagerStartPatch::TeleporterButton->Timer = static_cast<float>(((Roles->RoleClass.Teleporter::ButtonTimer + TimeSpanDate) - DateTime::Now).TotalSeconds);
		if (Buttons::HudManagerStartPatch::TeleporterButton->Timer <= 0.0f)
		{
			Buttons::HudManagerStartPatch::TeleporterButton->Timer = 0.0f;
		}
		return;
	}

	void ButtonTime::DoorrButton()
	{
		if (Buttons::HudManagerStartPatch::DoorrDoorButton->Timer == 0)
		{
			return;
		}
		if (Roles->RoleClass.Doorr::ButtonTimer == nullptr)
		{
			Roles->RoleClass.Doorr::ButtonTimer = DateTime::Now;
		}
		TimeSpan TimeSpanDate = TimeSpan(0, 0, 0, static_cast<int>(Roles->RoleClass.Doorr::CoolTime));
		if (CachedPlayer::LocalPlayer->Data->Role.IsImpostor)
		{
			TimeSpanDate = TimeSpan(0, 0, 0, static_cast<int>(Roles->RoleClass.EvilDoorr::CoolTime));
		}
		Buttons::HudManagerStartPatch::DoorrDoorButton->Timer = static_cast<float>(((Roles->RoleClass.Doorr::ButtonTimer + TimeSpanDate) - DateTime::Now).TotalSeconds);
		if (Buttons::HudManagerStartPatch::DoorrDoorButton->Timer <= 0.0f)
		{
			Buttons::HudManagerStartPatch::DoorrDoorButton->Timer = 0.0f;
		}
		return;
	}


//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
