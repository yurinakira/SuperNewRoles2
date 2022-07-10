#include "DeadPlayer.h"

namespace SuperNewRoles::Patch
{

std::vector<DeadPlayer*> DeadPlayer::deadPlayers;

	DeadPlayer::DeadPlayer(PlayerControl *player, DateTime timeOfDeath, DeathReason *deathReason, PlayerControl *killerIfExisting)
	{
		this->player = player;
		this->timeOfDeath = timeOfDeath;
		this->deathReason = deathReason;
		this->killerIfExisting = killerIfExisting;
	}
}
