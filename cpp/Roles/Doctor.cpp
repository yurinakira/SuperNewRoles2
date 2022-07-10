#include "Doctor.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleClass.h"
#include "../Patch/DeadPlayer.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles
{

float Doctor::VitalsPatch::vitalsTimer = 0.0f;
TMPro::TextMeshPro *Doctor::VitalsPatch::TimeRemaining;
std::vector<TMPro::TextMeshPro*> Doctor::VitalsPatch::hackerTexts;

	void Doctor::VitalsPatch::ResetData()
	{
		vitalsTimer = 0.0f;
		if (TimeRemaining != nullptr)
		{
			UnityEngine::Object::Destroy(TimeRemaining);
			TimeRemaining = nullptr;
		}
	}

	void Doctor::VitalsPatch::VitalsMinigameUpdatePatch::Postfix(VitalsMinigame *__instance)
	{
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::Doctor) && !RoleClass::Doctor::MyPanelFlag)
		{
			for (int k = 0; k < __instance->vitals->Length; k++)
			{
				VitalsPanel *vitalsPanel = __instance->vitals[k];
				GameData::PlayerInfo *player = GameData::Instance->AllPlayers[k];

				// Hacker update
				if (vitalsPanel->IsDead)
				{
					DeadPlayer *deadPlayer = DeadPlayer::deadPlayers.empty() ? nullptr : (DeadPlayer::deadPlayers.Where([&] (std::any x)
					{
						if (x::player != nullptr)
						{
							x::player::PlayerId;
						}
					} == player == nullptr ? nullptr : player->PlayerId)?.FirstOrDefault());
					if (deadPlayer != nullptr && deadPlayer->timeOfDeath != nullptr && k < hackerTexts.size() && hackerTexts[k] != nullptr)
					{
						float timeSinceDeath = static_cast<float>((DateTime::UtcNow - deadPlayer->timeOfDeath).TotalMilliseconds);
						hackerTexts[k]->gameObject.SetActive(true);
						hackerTexts[k]->text = BankersRounding::round(timeSinceDeath / 1000) + L"s";
					}
				}
			}
		}
		else
		{
			for (auto text : hackerTexts)
			{
				if (text != nullptr && text->gameObject != nullptr)
				{
					text->gameObject.SetActive(false);
				}
			}
		}
	}
}
