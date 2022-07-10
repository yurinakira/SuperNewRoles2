#pragma once

#include <vector>
#include <limits>

using namespace SuperNewRoles::CustomObject;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Vulture
	{
	private:
		static std::vector<DeadBody*> Targets;
	public:
		class FixedUpdate
		{
		public:
			static void Postfix();
		};
	};
}
