#include "FinalStatus.h"

using namespace SuperNewRoles::Patch;
using namespace UnityEngine;

namespace SuperNewRoles::EndGame
{

std::vector<std::tuple<Vector3*, bool>> FinalStatusPatch::FinalStatusData::localPlayerPositions;
std::vector<DeadPlayer*> FinalStatusPatch::FinalStatusData::deadPlayers;
std::unordered_map<int, FinalStatus> FinalStatusPatch::FinalStatusData::FinalStatuses;

	void FinalStatusPatch::FinalStatusData::ClearFinalStatusData()
	{
		localPlayerPositions = std::vector<std::tuple<Vector3*, bool>>();
		deadPlayers = std::vector<DeadPlayer*>();
		FinalStatuses = std::unordered_map<int, FinalStatus>();
	}
}
