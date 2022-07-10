#pragma once

#include <string>
#include <unordered_map>
#include <optional>

using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Intro;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class main
	{
	public:
		static void ClearAndReloads();
		static PlayerControl *RealExiled;
		static void SendAllRoleChat();
	};
}
