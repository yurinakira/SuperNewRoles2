#pragma once

#include "../../Intro/IntroDate.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "../../stringhelper.h"

using namespace InnerNet;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class RoleChat
	{
	public:
		static bool SendChat(ChatController *__instance);
		static std::wstring GetRoleDes(const std::wstring &rolename);
		static IntroDate *GetNameIntroDate(const std::wstring &role);
	};
}
