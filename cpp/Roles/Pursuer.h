#pragma once

#include <limits>
#include <stdexcept>

using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Pursuer
	{
	public:
		class PursureUpdate
		{
		public:
			static void Postfix();
		};
	};
}
