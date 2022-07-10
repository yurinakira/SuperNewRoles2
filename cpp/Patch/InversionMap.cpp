#include "InversionMap.h"
#include "../CustomOption/CustomOptionDate.h"
#include "../SubmergedCompatibility.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

GameObject *inversion::skeld;
GameObject *inversion::mira;
GameObject *inversion::polus;
GameObject *inversion::airship;

	void inversion::Prefix()
	{
		if (AmongUsClient::Instance->GameMode != GameModes::FreePlay && CustomOptions::enableMirroMap->getBool())
		{
			if (PlayerControl::GameOptions->MapId == 0)
			{
				skeld = GameObject::Find(L"SkeldShip(Clone)");
				skeld->transform->localScale = new Vector3(-1.2f, 1.2f, 1.2f);
				ShipStatus::Instance->InitialSpawnCenter = new Vector2(0.8f, 0.6f);
				ShipStatus::Instance->MeetingSpawnCenter = new Vector2(0.8f, 0.6f);
			}
			else if (PlayerControl::GameOptions->MapId == 1)
			{
				mira = GameObject::Find(L"MiraShip(Clone)");
				mira->transform->localScale = new Vector3(-1.0f, 1.0f, 1.0f);
				ShipStatus::Instance->InitialSpawnCenter = new Vector2(4.4f, 2.2f);
				ShipStatus::Instance->MeetingSpawnCenter = new Vector2(-25.3921f, 2.5626f);
				ShipStatus::Instance->MeetingSpawnCenter2 = new Vector2(-25.3921f, 2.5626f);
			}
			else if (PlayerControl::GameOptions->MapId == 2)
			{
				polus = GameObject::Find(L"PolusShip(Clone)");
				polus->transform->localScale = new Vector3(-1.0f, 1.0f, 1.0f);
				ShipStatus::Instance->InitialSpawnCenter = new Vector2(-16.7f, -2.1f);
				ShipStatus::Instance->MeetingSpawnCenter = new Vector2(-19.5f, -17.0f);
				ShipStatus::Instance->MeetingSpawnCenter2 = new Vector2(-19.5f, -17.0f);
			}
			else if (SubmergedCompatibility::isSubmerged())
			{
				ShipStatus::Instance->InitialSpawnCenter = new Vector2(-3.4f, -28.35f);
				ShipStatus::Instance->MeetingSpawnCenter = new Vector2(-3.4f, -28.35f);
				ShipStatus::Instance->MeetingSpawnCenter2 = new Vector2(-3.4f, -28.35f);
				ShipStatus::Instance->transform->localScale = new Vector3(-0.8f, 0.8f, 0.9412f);
			}
			/*else if(PlayerControl.GameOptions.MapId == 4 && CustomOptionHolder.InversionAShip.getBool())
			{
			    airship = GameObject.Find("Airship(Clone)");
			    airship.transform.localScale = new Vector3(-0.7f, 0.7f, 1f);
			    airshipの選択スポーンシステムの対応ができてないため非表示
			}*/
		}
	}
}
