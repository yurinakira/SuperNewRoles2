#pragma once

#include "../CustomRPC/CustomRPC.h"

using namespace SuperNewRoles::CustomRPC;

namespace SuperNewRoles::Roles
{
	class Minimalist
	{
	public:
		class MurderPatch
		{
		public:
			static void Postfix(PlayerControl *__instance);
		};
	public:
		class FixedUpdate
		{
		public:
			static void Postfix(RoleId role);
		};
	};
}
