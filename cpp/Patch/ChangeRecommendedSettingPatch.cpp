#include "ChangeRecommendedSettingPatch.h"
#include "../Mode/ModeHandler.h"

using namespace HarmonyLib;
using namespace UnityEngine;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles
{

	bool ChangeRecommendedSettingPatch::Prefix(GameOptionsData *__instance, int numPlayers, GameModes *modes)
	{
		//通常モードとSHRモード
		numPlayers = Mathf::Clamp(numPlayers, 4, 15);
		__instance->PlayerSpeedMod = __instance->MapId == 4 ? 1.25f : 1.0f; //AirShipなら1.25、それ以外は1
		__instance->CrewLightMod = 0.5f;
		__instance->ImpostorLightMod = 1.75f;
		__instance->KillCooldown = 30;
		__instance->NumCommonTasks = 2;
		__instance->NumLongTasks = 3;
		__instance->NumShortTasks = 5;
		__instance->NumEmergencyMeetings = 1;
		__instance->TaskBarMode = TaskBarMode::Invisible;
		if (modes != GameModes::OnlineGame)
		{
			__instance->NumImpostors = GameOptionsData::RecommendedImpostors[numPlayers];
		}
		__instance->KillDistance = 0;
		__instance->DiscussionTime = 0;
		__instance->VotingTime = 150;
		__instance->isDefaults = true;
		__instance->ConfirmImpostor = false;
		__instance->VisualTasks = false;
		__instance->EmergencyCooldown = static_cast<int>(__instance->killCooldown) - 15; //キルクールより15秒短く
		__instance->RoleOptions->ShapeshifterCooldown = 10.0f;
		__instance->RoleOptions->ShapeshifterDuration = 30.0f;
		__instance->RoleOptions->ShapeshifterLeaveSkin = false;
		__instance->RoleOptions->ImpostorsCanSeeProtect = false;
		__instance->RoleOptions->ScientistCooldown = 15.0f;
		__instance->RoleOptions->ScientistBatteryCharge = 5.0f;
		__instance->RoleOptions->GuardianAngelCooldown = 60.0f;
		__instance->RoleOptions->ProtectionDurationSeconds = 10.0f;
		__instance->RoleOptions->EngineerCooldown = 30.0f;
		__instance->RoleOptions->EngineerInVentMaxTime = 15.0f;
		switch (ModeHandler::GetMode(false))
		{
			//ハイドアンドシーク
			case ModeId::HideAndSeek:
				__instance->PlayerSpeedMod = 1.75f;
				__instance->CrewLightMod = 5.0f;
				__instance->ImpostorLightMod = 0.25f;
				__instance->NumImpostors = 1;
				__instance->NumCommonTasks = 0;
				__instance->NumLongTasks = 0;
				__instance->NumShortTasks = 6;
				__instance->KillCooldown = 10.0f;
				__instance->TaskBarMode = 0;
				break;
			//バトルロイヤル
			case ModeId::BattleRoyal:
				__instance->PlayerSpeedMod = 1.75f;
				__instance->ImpostorLightMod = 2.0f;
				__instance->KillCooldown = 1.0f;
				__instance->TaskBarMode = TaskBarMode::Invisible;
				break;
			//ゾンビモード
			case ModeId::Zombie:

				__instance->PlayerSpeedMod = 1.5f;
				__instance->CrewLightMod = 1.5f;
				__instance->ImpostorLightMod = 0.25f;
				__instance->NumImpostors = 1;
				__instance->NumCommonTasks = 0;
				__instance->NumLongTasks = 0;
				__instance->NumShortTasks = 6;
				__instance->TaskBarMode = 0;
				break;
			//ケイドロモード
			case ModeId::CopsRobbers:
				__instance->PlayerSpeedMod = 1.5f;
				__instance->CrewLightMod = 2.0f;
				__instance->ImpostorLightMod = 1.5f;
				__instance->NumCommonTasks = 0;
				__instance->NumLongTasks = 0;
				__instance->NumShortTasks = 6;
				__instance->TaskBarMode = 0;
				break;
		}
		return false;
	}
}
