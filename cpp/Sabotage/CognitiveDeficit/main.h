#pragma once

#include "../../CustomObject/Arrow.h"
#include <vector>
#include <limits>
#include <functional>
#include <optional>

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomObject;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;
using namespace static UnityEngine::UI::Button;

namespace SuperNewRoles::Sabotage::CognitiveDeficit
{
	class main final
	{
	public:
		static void StartSabotage();
		static float DefaultUpdateTime;
	private:
		static float ArrowUpdateColor;
	public:
		static float UpdateTime;
	private:
		static float DistanceTime;
	public:
		static float DefaultDistanceTime;
	private:
		static bool IsYellow;
		static std::vector<Arrow*> ArrowDatas;
		static std::vector<Vector2*> Datas;
	public:
		static std::vector<PlayerControl*> OKPlayers;
		static bool IsLocalEnd;
		static bool IsAllEndSabotage;
		static void Create(InfectedOverlay *__instance);
		static void Update();
		static void EndSabotage(PlayerControl *p);
	};
}
