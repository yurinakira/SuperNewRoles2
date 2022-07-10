#pragma once

namespace SuperNewRoles::Roles
{
	class Vampire
	{
	public:
		class FixedUpdate final
		{
		public:
			static void Postfix();
		};
	};
}
