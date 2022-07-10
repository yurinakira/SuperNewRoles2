#include "ZombieOptions.h"
#include "../ModeHandler.h"
#include "../SuperHostRoles/SyncSetting.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../ModHelpers.h"
#include "main.h"

using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Zombie
{

CustomOption::CustomOption *ZombieOptions::ZombieMode;
CustomOption::CustomOption *ZombieOptions::StartSecondOption;
CustomOption::CustomOption *ZombieOptions::ZombieLightOption;
CustomOption::CustomOption *ZombieOptions::ZombieSpeedOption;
CustomOption::CustomOption *ZombieOptions::PoliceLightOption;
CustomOption::CustomOption *ZombieOptions::PoliceSpeedOption;
CustomOption::CustomOption *ZombieOptions::ZombieCommingLightOption;
CustomOption::CustomOption *ZombieOptions::ZombieCommingSpeedOption;

	void ZombieOptions::Load()
	{
		ZombieMode = CustomOption::CustomOption::Create(489, true, CustomOptionType::Generic, L"SettingZombieMode", false, ModeHandler::ModeSetting);
		StartSecondOption = CustomOption::CustomOption::Create(490, true, CustomOptionType::Generic, L"ZombieStartSecondSetting", 5.0f, 2.5f, 30.0f, 2.5f, ZombieMode);
		ZombieLightOption = CustomOption::CustomOption::Create(491, true, CustomOptionType::Generic, L"ZombieZombieLightSetting", 0.5f, 0.0f, 5.0f, 0.25f, ZombieMode);
		ZombieSpeedOption = CustomOption::CustomOption::Create(492, true, CustomOptionType::Generic, L"ZombieZombieSpeedSetting", 0.75f, 0.0f, 5.0f, 0.25f, ZombieMode);
		PoliceLightOption = CustomOption::CustomOption::Create(493, true, CustomOptionType::Generic, L"ZombiePoliceLightSetting", 3.0f, 0.0f, 5.0f, 0.25f, ZombieMode);
		PoliceSpeedOption = CustomOption::CustomOption::Create(494, true, CustomOptionType::Generic, L"ZombiePoliceSpeedSetting", 1.0f, 0.0f, 5.0f, 0.25f, ZombieMode);
		ZombieCommingLightOption = CustomOption::CustomOption::Create(495, true, CustomOptionType::Generic, L"ZombieCommingLightSetting", 1.5f, 0.0f, 5.0f, 0.25f, ZombieMode);
		ZombieCommingSpeedOption = CustomOption::CustomOption::Create(496, true, CustomOptionType::Generic, L"ZombieCommingSpeedSetting", 1.5f, 0.0f, 5.0f, 0.25f, ZombieMode);
	}

	float ZombieOptions::GetSpeed(float speed)
	{
		if (speed <= 0)
		{
			return 0.001f;
		}
		return speed;
	}

	void ZombieOptions::FirstChangeSettings()
	{
		auto optdata = SuperNewRoles::Mode::SuperHostRoles::SyncSetting::DeepCopy(SyncSetting::OptionData);
		optdata->CrewLightMod = GetSpeed(ZombieCommingLightOption->getFloat());
		optdata->ImpostorLightMod = GetSpeed(ZombieCommingSpeedOption->getFloat());
		for (auto player : CachedPlayer::AllPlayers)
		{
			if (player->AmOwner)
			{
				PlayerControl->GameOptions = optdata;
			}
			MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(RpcCalls::SyncSettings), SendOption::None, SuperNewRoles::ModHelpers::getClientId(player));
			writer->WriteBytesAndSize(optdata->ToBytes(5));
			AmongUsClient::Instance->FinishRpcImmediately(writer);
		}
	}

	void ZombieOptions::ChengeSetting(PlayerControl *player)
	{
		auto optdata = SuperNewRoles::Mode::SuperHostRoles::SyncSetting::DeepCopy(SyncSetting::OptionData);

		if (SuperNewRoles::Mode::Zombie::main::IsZombie(player))
		{
			optdata->ImpostorLightMod = GetSpeed(ZombieLight);
			optdata->PlayerSpeedMod = GetSpeed(ZombieSpeed);
			optdata->CrewLightMod = GetSpeed(ZombieLight);
			optdata->PlayerSpeedMod = GetSpeed(ZombieSpeed);
		}
		else
		{
			optdata->CrewLightMod = GetSpeed(PoliceLight);
			optdata->PlayerSpeedMod = GetSpeed(PoliceSpeed);
		}
		if (player->AmOwner)
		{
			PlayerControl->GameOptions = optdata;
		}
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(RpcCalls::SyncSettings), SendOption::None, SuperNewRoles::ModHelpers::getClientId(player));
		writer->WriteBytesAndSize(optdata->ToBytes(5));
		AmongUsClient::Instance->FinishRpcImmediately(writer);
	}

float ZombieOptions::ZombieLight = 0;
float ZombieOptions::ZombieSpeed = 0;
float ZombieOptions::PoliceLight = 0;
float ZombieOptions::PoliceSpeed = 0;
}
