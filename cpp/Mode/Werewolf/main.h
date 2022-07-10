#pragma once

#include "../../Roles/IntroHandler.h"
#include <string>
#include <unordered_map>
#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::Werewolf
{
	class main
	{
	public:
		static bool IsDiscussion;
		static bool IsFirst;
		static int AbilityTime;
		static int DiscussionTime;
		static std::unordered_map<int, int> SoothRoles;
		static std::vector<int> HunterKillPlayers;
		static std::vector<int> WolfKillPlayers;
		static std::vector<PlayerControl*> HunterPlayers;
		static PlayerControl *HunterExilePlayer;
		static int Time;
		static bool isAbility();
		static void setAbility(bool value);
		static void ClearAndReload();
		static void IntroHandler();
		static void Wrapup(GameData::PlayerInfo *exiled);
	};
}
