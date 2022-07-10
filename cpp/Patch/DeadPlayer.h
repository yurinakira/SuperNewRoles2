#pragma once

#include <vector>

namespace SuperNewRoles::Patch
{
	class DeadPlayer
	{
	public:
		static std::vector<DeadPlayer*> deadPlayers;
		PlayerControl *player;
		DateTime timeOfDeath;
		DeathReason *deathReason;
		PlayerControl *killerIfExisting;

		virtual ~DeadPlayer()
		{
			delete player;
			delete deathReason;
			delete killerIfExisting;
		}

		DeadPlayer(PlayerControl *player, DateTime timeOfDeath, DeathReason *deathReason, PlayerControl *killerIfExisting);
	};
}
