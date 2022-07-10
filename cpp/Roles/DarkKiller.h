#pragma once

namespace SuperNewRoles::Roles
{
	class DarkKiller
	{
	public:
		class MurderPatch
		{
		public:
			static void Postfix(PlayerControl *__instance);
		};
	public:
		static void SetDarkKillerButton();
	public:
		class FixedUpdate
		{
		public:
			static void Postfix();
		};
	};
}
