#pragma once

#include "../ModeHandler.h"
#include <string>

using namespace UnityEngine;

namespace SuperNewRoles::Mode::Zombie
{
	class Intro
	{
	public:
		static Il2CppSystem::Collections::Generic::List<PlayerControl*> *ModeHandler(IntroCutscene *__instance);
		static void IntroHandler(IntroCutscene *__instance);

		static void YouAreHandle(IntroCutscene *__instance);
	};
}
