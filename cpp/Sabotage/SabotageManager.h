#pragma once

#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::Helpers;

namespace SuperNewRoles::Sabotage
{
	class SabotageManager final
	{
	public:
		static CustomSabotage thisSabotage;
		static std::vector<ButtonBehavior*> CustomButtons;
	public:
		enum class CustomSabotage
		{
			None,
			CognitiveDeficit
		};
	public:
		static bool IsOK(CustomSabotage sabotage);
		static bool IsOKMeeting();
		static InfectedOverlay *InfectedOverlayInstance;
		static constexpr float SabotageMaxTime = 30.0f;
		static void SetSabotage(PlayerControl *player, CustomSabotage Sabotage, bool Is);
		static void ClearAndReloads();
		static void Update();
		static void CustomSabotageRPC(PlayerControl *p, CustomSabotage type, bool Is);
	};
}
