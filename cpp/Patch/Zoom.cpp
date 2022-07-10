#include "Zoom.h"
#include "../MapOptions/MapOption.h"
#include "../Mode/ModeHandler.h"
#include "../ModHelpers.h"

using namespace HarmonyLib;
using namespace UnityEngine;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Patch
{

	void Zoom::Postfix(HudManager *__instance)
	{
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}) && MapOptions::MapOption::MouseZoom && PlayerControl::LocalPlayer::Data->IsDead)
		{
			if (Input->GetAxis(L"Mouse ScrollWheel") > 0)
			{
				if (Camera->main.orthographicSize > 1.0f)
				{
					Camera->main.orthographicSize /= 1.5f;
					__instance->transform.localScale /= 1.5f;
					__instance->UICamera.orthographicSize /= 1.5f;
					HudManager::Instance->TaskStuff.SetActive(false);
				}

				else if (Camera->main.orthographicSize > 3.0f)
				{
					Camera->main.orthographicSize /= 1.5f;
					__instance->transform.localScale /= 1.5f;
					__instance->UICamera.orthographicSize /= 1.5f;
				}
			}
			if (Input->GetAxis(L"Mouse ScrollWheel") < 0)
			{
				if (PlayerControl::LocalPlayer::Data->IsDead)
				{
					if (Camera->main.orthographicSize < 18.0f)
					{
						Camera->main.orthographicSize *= 1.5f;
						__instance->transform.localScale *= 1.5f;
						__instance->UICamera.orthographicSize *= 1.5f;
					}
				}
			}
			if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
			{
				if (Camera->main.orthographicSize != 3.0f)
				{
					HudManager::Instance->TaskStuff.SetActive(false);
					if (!PlayerControl::LocalPlayer::Data->IsDead)
					{
						__instance->ShadowQuad.gameObject.SetActive(false);
					}
				}
				else
				{
					HudManager::Instance->TaskStuff.SetActive(true);
					if (!PlayerControl::LocalPlayer::Data->IsDead)
					{
						__instance->ShadowQuad.gameObject.SetActive(true);
					}
				}
			}
			CreateFlag::NewFlag(L"Zoom");
		}
		else
		{
			CreateFlag::Run([&] ()
			{
				Camera->main->orthographicSize = 3.0f;
				HudManager::Instance->UICamera->orthographicSize = 3.0f;
				HudManager::Instance->transform->localScale = Vector3::one;
				if (MeetingHud::Instance != nullptr)
				{
					MeetingHud::Instance->transform->localScale = Vector3::one;
				}
				HudManager::Instance->Chat.transform->localScale = Vector3::one;
				if (!PlayerControl::LocalPlayer::Data->IsDead)
				{
					__instance->ShadowQuad.gameObject.SetActive(true);
				}
			}, L"Zoom");
		}
	}
}
