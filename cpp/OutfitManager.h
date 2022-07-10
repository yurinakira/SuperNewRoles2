#pragma once

namespace SuperNewRoles
{
	class OutfitManager final
	{
	public:
		static void setOutfit(PlayerControl *pc, GameData::PlayerOutfit *outfit, bool visible = true);
		static void changeToPlayer(PlayerControl *pc, PlayerControl *target);
		static void resetChange(PlayerControl *pc);
	};
}
