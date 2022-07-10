#pragma once

#include <string>
#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::Helpers;
using namespace UnityEngine;

namespace SuperNewRoles
{
	class BotManager final
	{
	public:
		static std::vector<PlayerControl*> AllBots;
		static bool IsBot(PlayerControl *player);
		static bool IsPlayer(PlayerControl *player);
		static PlayerControl *Spawn(const std::wstring &name = L"Bot", unsigned char BotPlayerId = 1);
		static void Despawn(PlayerControl *Bot);
		static void AllBotDespawn();
	};
}
