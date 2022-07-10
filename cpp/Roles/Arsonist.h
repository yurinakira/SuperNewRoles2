#pragma once

#include "../Buttons/CustomButton.h"
#include "Speeder.h"
#include <unordered_map>
#include <vector>
#include <stdexcept>

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Arsonist final
	{
	public:
		static void ArsonistDouse(PlayerControl *target, PlayerControl *source = nullptr);

		static std::vector<PlayerControl*> GetDouseData(PlayerControl *player);

		static std::vector<PlayerControl*> GetUntarget();

		static bool IsDoused(PlayerControl *source, PlayerControl *target);

		static std::vector<PlayerControl*> GetIconPlayers(PlayerControl *player = nullptr);
		static bool IsViewIcon(PlayerControl *player);

		static bool IsButton();

		static bool IseveryButton();

		static bool IsWin(PlayerControl *Arsonist);

	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(HudManager), nameof(HudManager.Update))] public class HudManagerUpdatePatch
		class HudManagerUpdatePatch
		{
		public:
			static void Postfix();
		};

	public:
		static bool IsArsonistWinFlag();

		static bool CheckAndEndGameForArsonistWin(ShipStatus *__instance);

		static void SetWinArsonist();
		static std::unordered_map<unsigned char, float> ArsonistTimer;

		static void ArsonistFinalStatus(PlayerControl *__instance);
	};
}
