#include "main.h"
#include "MapCustom.h"
#include "../Mode/ModeHandler.h"
#include "00_AllMaps/AdditionalVent.h"
#include "2_Polus/SpecimenVital.h"
#include "4_Airship/MoveElecPad.h"

using namespace HarmonyLib;
using namespace UnityEngine;
using namespace static PlayerControl;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::MapCustoms
{

	bool MapCustomHandler::isMapCustom(MapCustomId mapCustomId, bool IsChache)
	{
		bool tempVar4;
		switch (mapCustomId)
		{
			case MapCustomId::Skeld:
				tempVar4 = GameOptions->MapId == 0 && MapCustom::MapCustomOption->getBool() && MapCustom::SkeldSetting->getBool() && ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default});
				break;
			case MapCustomId::Mira:
				tempVar4 = GameOptions->MapId == 1 && MapCustom::MapCustomOption->getBool() && MapCustom::MiraSetting->getBool() && ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default});
				break;
			case MapCustomId::Polus:
				tempVar4 = GameOptions->MapId == 2 && MapCustom::MapCustomOption->getBool() && MapCustom::PolusSetting->getBool() && ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default});
				break;
			case MapCustomId::Airship:
				tempVar4 = GameOptions->MapId == 4 && MapCustom::MapCustomOption->getBool() && MapCustom::AirshipSetting->getBool() && ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default});
				break;
			default:
				tempVar4 = false;
				break;
		}
		return tempVar4;
	}

	void IntroCutsceneOnDestroyPatch::Prefix(IntroCutscene *__instance)
	{
		// ベントを追加する
		AdditionalVents::AddAdditionalVents();

		// スペシメンにバイタルを移動する
		SpecimenVital::moveVital();

		//配電盤を移動させる
		MoveElecPad::MoveElecPads();

		GameObject *gapRoom = DestroyableSingleton<ShipStatus*>::Instance->FastRooms[SystemTypes::GapRoom].gameObject;
		// ぬ～んを消す
		if (MapCustomHandler::isMapCustom(MapCustomHandler::MapCustomId::Airship) && MapCustom::AirshipDisableMovingPlatform->getBool())
		{
			gapRoom->GetComponentInChildren<MovingPlatformBehaviour*>().gameObject.SetActive(false);
			gapRoom->GetComponentsInChildren<PlatformConsole*>().ForEach([&] (std::any x)
			{
				x::gameObject::SetActive(false);
			});
		}
	}
}
