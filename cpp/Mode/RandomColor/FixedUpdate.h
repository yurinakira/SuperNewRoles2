#pragma once

using namespace HarmonyLib;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::RandomColor
{
	class FixedUpdate final
	{
	private:
		static int MaxColorCount;
	public:
		static float UpdateTime;
		static bool IsRandomNameColor;
		static bool IsHideName;
		static bool IsHideNameSet;
		static bool IsRandomColorMeeting;
		static bool IsMeetingIn;
		static void Update();
	};
}
