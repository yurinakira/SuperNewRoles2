#pragma once

#include <string>

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::SuperHostRoles::Roles
{
	class GetRoleTextClass final
	{
	public:
		static std::wstring GetRoleTextPostfix(PlayerControl *p);
		static std::wstring GetNameTextPostfix(PlayerControl *p);
	};
}
