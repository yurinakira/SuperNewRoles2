#pragma once

#include <vector>
#include <cmath>
#include "../bankersrounding.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles
{
	class Doctor
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Harmony] public class VitalsPatch
		class VitalsPatch
		{
		private:
			static float vitalsTimer;
			static TMPro::TextMeshPro *TimeRemaining;
			static std::vector<TMPro::TextMeshPro*> hackerTexts;

		public:
			static void ResetData();

		private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(VitalsMinigame), nameof(VitalsMinigame.Update))] class VitalsMinigameUpdatePatch
			class VitalsMinigameUpdatePatch
			{
			private:
				static void Postfix(VitalsMinigame *__instance);
			};
		};
	};
}
