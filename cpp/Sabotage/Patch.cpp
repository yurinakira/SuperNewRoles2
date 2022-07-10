#include "Patch.h"
#include "../Helpers/CachedPlayer.h"
#include "../OutfitManager.h"
#include "SabotageManager.h"
#include "../Mode/ModeHandler.h"
#include "CognitiveDeficit/main.h"
#include "../Helpers/FastDestroyableSingleton.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Sabotage
{

	void Patch::OpenMeetingPatch::Prefix(HudManager *__instance)
	{
		for (auto p : CachedPlayer::AllPlayers)
		{
			SuperNewRoles::OutfitManager::resetChange(p);
		}
	}

	void Patch::SetUpCustomButton::Postfix(InfectedOverlay *__instance)
	{
		SabotageManager::InfectedOverlayInstance = __instance;
		//SuperNewRolesPlugin.Logger.LogInfo("ローカルの座標:"+CachedPlayer.LocalPlayer.transform.position);
	}

	void Patch::SetUpCustomSabotageButton::Postfix(InfectedOverlay *__instance)
	{
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			CognitiveDeficit::main::Create(__instance);
		}
	}

	void Patch::EmergencyUpdatePatch::Postfix(EmergencyMinigame *__instance)
	{
		if (!SabotageManager::IsOKMeeting())
		{
			__instance->state = 2;
			__instance->ButtonActive = false;
			__instance->StatusText->text = FastDestroyableSingleton<TranslationController*>::getInstance().GetString(StringNames::EmergencyDuringCrisis);
			__instance->NumberText->text = L"";
			__instance->ClosedLid.gameObject.SetActive(true);
			__instance->OpenLid.gameObject.SetActive(false);
		}
	}
}
