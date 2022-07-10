#pragma once

#include "TeamRoleType.h"
#include <unordered_map>
#include <optional>

namespace SuperNewRoles::Roles
{
	class CountChanger final
	{
	public:
		class CountChangerPatch final
		{
		public:
			static void WrapUpPatch();
		};
	public:
		static bool isChange(PlayerControl *p);

		static TeamRoleType GetRoleType(PlayerControl *p);
		static bool IsChangeMadmate(PlayerControl *p);
		static bool IsChangeMadMayor(PlayerControl *p);
		static bool IsChangeMadStuntMan(PlayerControl *p);
		static bool IsChangeMadJester(PlayerControl *p);
		static bool IsChangeMadHawk(PlayerControl *p);
		static bool IsChangeMadSeer(PlayerControl *p);
		static bool IsChangeMadMaker(PlayerControl *p);
				static bool IsChangeBlackCat(PlayerControl *p);
		static bool IsChangeJackal(PlayerControl *p);
		static bool IsChangeSidekick(PlayerControl *p);
		static bool IsChangeJackalFriends(PlayerControl *p);
		static bool IsChangeSeerFriends(PlayerControl *p);
		static bool IsChangeJackalSeer(PlayerControl *p);
		static bool IsChangeSidekickSeer(PlayerControl *p);
		static std::optional<int> GetKey(std::unordered_map<int, int> &dics, int id);
		static TeamRoleType Get(PlayerControl *player);
	};
}
