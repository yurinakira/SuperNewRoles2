#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <optional>

using namespace SuperNewRoles::Helpers;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::CopsRobbers
{
	class main final
	{
	public:
		static void ClearAndReloads();
		static bool IsStart;
		static PlayerControl *GetBot();
		static std::vector<int> Arrest;
		static std::unordered_map<int, std::optional<SystemTypes*>> ArrestPositions;
		static bool IsMove;
		static std::unordered_map<int, std::optional<SystemTypes*>> SpawnPosition;
		static bool IsArrest(PlayerControl *player);
		static std::unordered_map<MapNames*, std::vector<SystemTypes*>> Rooms;
		static MapNames *GetMap();
		static bool EndGameCheck(ShipStatus *__instance);
		static void ChangeCosmetics();
		static SystemTypes *GetRandomSpawnPosition(PlayerControl *player);
		static SystemTypes *SetRandomArrestPosition(PlayerControl *player);
		static void RemoveArrest(PlayerControl *player);
		static Vector2 *getPosition(SystemTypes *type);
	private:
		static float ImpostorMoveTime;
		static int LastCount;
		static float LastUpdate;
	public:
		static std::vector<unsigned char> TeleportIDs;
		static void Teleport(PlayerControl *player, Vector2 *position);
		static void HudUpdate();
	};
}
