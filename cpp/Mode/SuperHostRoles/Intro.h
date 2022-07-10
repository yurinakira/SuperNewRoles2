#pragma once

#include "../ModeHandler.h"
#include "../../Roles/IntroHandler.h"
#include <string>
#include <stdexcept>
#include <any>

using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class Intro
	{
	public:
		static Il2CppSystem::Collections::Generic::List<PlayerControl*> *ModeHandler(IntroCutscene *__instance);
		static void IntroHandler(IntroCutscene *__instance);
		static void RoleTextHandler(IntroCutscene *__instance);
	};
}
