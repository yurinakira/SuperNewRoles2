#pragma once

#include "../Patch/DeadPlayer.h"
#include <unordered_map>
#include <vector>
#include <tuple>

using namespace SuperNewRoles::Patch;
using namespace UnityEngine;

namespace SuperNewRoles::EndGame
{
	class FinalStatusPatch
	{
	public:
		class FinalStatusData final
		{
		public:
			static std::vector<std::tuple<Vector3*, bool>> localPlayerPositions;
			static std::vector<DeadPlayer*> deadPlayers;
			static std::unordered_map<int, FinalStatus> FinalStatuses;

			static void ClearFinalStatusData();
		};
	};
	enum class FinalStatus
	{
		Alive,
		Kill,
		Exiled,
		NekomataExiled,
		SheriffKill,
		SheriffMisFire,
		MeetingSheriffKill,
		MeetingSheriffMisFire,
		SelfBomb,
		BySelfBomb,
		Ignite,
		Disconnected,
		Dead,
		Sabotage
	};
}
