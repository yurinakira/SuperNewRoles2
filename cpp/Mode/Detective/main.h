#pragma once

#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Detective
{
	class main
	{
	public:
		static bool IsNotDetectiveWin;
		static bool IsNotDetectiveVote;
		static bool IsDetectiveNotTask;
		static bool IsNotDetectiveMeetingButton;
		static PlayerControl *DetectivePlayer;
		static Color32 *DetectiveColor;
		static void ClearAndReload();
		static void RoleSelect();
		static void MurderPatch(PlayerControl *target);
	};
}
