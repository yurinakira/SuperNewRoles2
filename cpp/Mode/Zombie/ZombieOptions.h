#pragma once

#include "../../CustomOption/CustomOptionModel.h"

using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Zombie
{
	class ZombieOptions
	{
	public:
		static CustomOption::CustomOption *ZombieMode;
		static CustomOption::CustomOption *StartSecondOption;
		static CustomOption::CustomOption *ZombieLightOption;
		static CustomOption::CustomOption *ZombieSpeedOption;
		static CustomOption::CustomOption *PoliceLightOption;
		static CustomOption::CustomOption *PoliceSpeedOption;
		static CustomOption::CustomOption *ZombieCommingLightOption;
		static CustomOption::CustomOption *ZombieCommingSpeedOption;
		static void Load();
	private:
		static float GetSpeed(float speed);
	public:
		static void FirstChangeSettings();
		static void ChengeSetting(PlayerControl *player);
		static float ZombieLight;
		static float ZombieSpeed;
		static float PoliceLight;
		static float PoliceSpeed;
	};
}
