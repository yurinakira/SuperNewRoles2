#pragma once

#include "../ModeHandler.h"
#include "../../stringhelper.h"

using namespace UnityEngine;

namespace SuperNewRoles::Mode::HideAndSeek
{
	class Intro
	{
	public:
		static Il2CppSystem::Collections::Generic::List<PlayerControl*> *ModeHandler(IntroCutscene *__instance);
		static void IntroHandler(IntroCutscene *__instance);
	};
}
