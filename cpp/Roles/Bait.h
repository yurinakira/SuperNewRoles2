#pragma once

using namespace Hazel;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Bait
	{
	public:
		class BaitUpdate
		{
		public:
			static void Postfix(PlayerControl *__instance);
		};
	};
}
