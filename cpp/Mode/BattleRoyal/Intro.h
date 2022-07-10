#pragma once

#include "../ModeHandler.h"
#include <limits>

using namespace UnityEngine;

namespace SuperNewRoles::Mode::BattleRoyal
{
	class Intro
	{
	public:
		static Il2CppSystem::Collections::Generic::List<PlayerControl*> *ModeHandler(IntroCutscene *__instance);
		static void IntroHandler(IntroCutscene *__instance);
	};
}
