#pragma once

#include <limits>

using namespace HarmonyLib;
using namespace Hazel;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::HideAndSeek
{
	class Patch
	{
	public:
		class RepairSystemPatch
		{
		public:
			static void Postfix(PlayerControl *__instance);
		};
	public:
		class HASFixed
		{
		public:
			static void Postfix(PlayerControl *__instance);
		};
	};
}
