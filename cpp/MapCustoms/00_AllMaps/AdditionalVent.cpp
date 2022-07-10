#include "AdditionalVent.h"
#include "../../Helpers/MapUtilities.h"
#include "../main.h"
#include "../MapCustom.h"
#include "../../Main.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::MapOptions;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::MapCustoms
{

std::vector<AdditionalVents*> AdditionalVents::AllVents;
bool AdditionalVents::flag = false;

	AdditionalVents::AdditionalVents(Vector3 *p)
	{
		// Create the vent
		auto referenceVent = UnityEngine::Object::FindObjectOfType<Vent*>();
		vent = UnityEngine::Object::Instantiate<Vent*>(referenceVent);
		vent->transform->position = p;
		vent->Left = nullptr;
		vent->Right = nullptr;
		vent->Center = nullptr;
		Vent *tmp = MapUtilities::CachedShipStatus->AllVents[0];
		vent->EnterVentAnim = tmp->EnterVentAnim;
		vent->ExitVentAnim = tmp->ExitVentAnim;
		vent->Offset = new Vector3(0.0f, 0.25f, 0.0f);
		vent->Id = ShipStatus::Instance->AllVents->Select([&] (std::any x)
		{
			x::Id;
		})->Max() + 1; // Make sure we have a unique id
		auto allVentsList = ShipStatus::Instance->AllVents.ToList();
		allVentsList.push_back(vent);
		ShipStatus::Instance->AllVents = allVentsList.ToArray();
		vent->gameObject.SetActive(true);
		vent->name = L"AdditionalVent_" + vent->Id;
		vent->transform->localScale = new Vector3(1.2f, 1.2f, 1.2f);
		AllVents.push_back(this);
	}

	void AdditionalVents::AddAdditionalVents()
	{
		if (AdditionalVents::flag)
		{
			return;
		}
		AdditionalVents::flag = true;
		if (AmongUsClient::Instance->GameState != InnerNet::InnerNetClient::GameStates::Started)
		{
			return;
		}
		std::wcout << L"AddAdditionalVents" << std::endl;

		//MiraHQにベントを追加する
		if (MapCustomHandler::isMapCustom(MapCustomHandler::MapCustomId::Mira) && MapCustoms::MapCustom::MiraAdditionalVents->getBool())
		{
			Vector3 tempVar(11.3518f, 10.4786f, PlayerControl::LocalPlayer::transform::position::z + 1.0f);
			AdditionalVents *vents1 = new AdditionalVents(&tempVar); // 研究室
			Vector3 tempVar2(12.1288f, 7.2f, PlayerControl::LocalPlayer::transform::position::z + 1.0f);
			AdditionalVents *vents2 = new AdditionalVents(&tempVar2); // Y字下
			Vector3 tempVar3(19.574f, 17.3698f, PlayerControl::LocalPlayer::transform::position::z + 1.0f);
			AdditionalVents *vents3 = new AdditionalVents(&tempVar3); // アドミン
			vents1->vent->Left = vents3->vent; // 研究室 - アドミン
			vents1->vent->Right = vents2->vent; // 研究室 - Y字下
			vents2->vent->Center = vents3->vent; // Y字下- アドミン
			vents2->vent->Left = vents1->vent; // Y字下- 研究室
			vents3->vent->Right = vents1->vent; // アドミン - 研究室
			vents3->vent->Left = vents2->vent; // アドミン - Y字下

//C# TO C++ CONVERTER TODO TASK: A 'delete vents3' statement was not added since vents3 was assigned to another object. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete vents2' statement was not added since vents2 was assigned to another object. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete vents1' statement was not added since vents1 was assigned to another object. Handle memory management manually.
		}

		// Polusにベントを追加する
		if (MapCustomHandler::isMapCustom(MapCustomHandler::MapCustomId::Polus) && MapCustoms::MapCustom::PolusAdditionalVents->getBool())
		{
			Vector3 tempVar4(36.54f, -21.77f, PlayerControl::LocalPlayer::transform::position::z + 1.0f);
			AdditionalVents *vents1 = new AdditionalVents(&tempVar4); // 標本室
			Vector3 tempVar5(11.5522f, -21.1158f, PlayerControl::LocalPlayer::transform::position::z + 1.0f);
			AdditionalVents *vents2 = new AdditionalVents(&tempVar5); // ウェポン
			Vector3 tempVar6(26.67f, -17.54f, PlayerControl::LocalPlayer::transform::position::z + 1.0f);
			AdditionalVents *vents3 = new AdditionalVents(&tempVar6); // バイタル
			vents1->vent->Left = vents3->vent; // 標本室 - バイタル
			vents1->vent->Right = vents2->vent; // 標本室 - ウェポン
			vents2->vent->Center = vents3->vent; // ウェポン- バイタル
			vents2->vent->Left = vents1->vent; // ウェポン- 標本室
			vents3->vent->Right = vents1->vent; // バイタル - 標本室
			vents3->vent->Left = vents2->vent; // バイタル - ウェポン

//C# TO C++ CONVERTER TODO TASK: A 'delete vents3' statement was not added since vents3 was assigned to another object. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete vents2' statement was not added since vents2 was assigned to another object. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete vents1' statement was not added since vents1 was assigned to another object. Handle memory management manually.
		}

		// AirShipにベントを追加する
		if (MapCustomHandler::isMapCustom(MapCustomHandler::MapCustomId::Airship) && MapCustoms::MapCustom::AirShipAdditionalVents->getBool())
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"べんとおおおお");
			Vector3 tempVar7(23.5483f, -5.589f, PlayerControl::LocalPlayer::transform::position::z + 1.0f);
			AdditionalVents *vents1 = new AdditionalVents(&tempVar7); // 診察室
			Vector3 tempVar8(24.8562f, 5.2692f, PlayerControl::LocalPlayer::transform::position::z + 1.0f);
			AdditionalVents *vents2 = new AdditionalVents(&tempVar8); // ラウンジ
			Vector3 tempVar9(5.9356f, 3.0133f, PlayerControl::LocalPlayer::transform::position::z + 1.0f);
			AdditionalVents *vents3 = new AdditionalVents(&tempVar9); // メイン
			vents1->vent->Right = vents2->vent; //診察-ラウンジ
			vents2->vent->Left = vents1->vent; //ラウンジ-診察
			vents2->vent->Right = vents3->vent; //ラウンジ-メイン
			vents3->vent->Right = vents2->vent; // メイン-ラウンジ

			Vector3 tempVar10(6.7651f, -10.2f, PlayerControl::LocalPlayer::transform::position::z + 1.0f);
			AdditionalVents *vents4 = new AdditionalVents(&tempVar10); // セキュ
			Vector3 tempVar11(18.1884f, -3.991f, PlayerControl::LocalPlayer::transform::position::z + 1.0f);
			AdditionalVents *vents5 = new AdditionalVents(&tempVar11); // エレキ
			Vector3 tempVar12(21.1574f, -1.3543f, PlayerControl::LocalPlayer::transform::position::z + 1.0f);
			AdditionalVents *vents6 = new AdditionalVents(&tempVar12); // シャワー
			vents4->vent->Right = vents5->vent; //セキュ-エレキ
			vents5->vent->Left = vents4->vent; //エレキ-セキュ
			vents5->vent->Right = vents6->vent; //エレキ-シャワー
			vents6->vent->Left = vents5->vent; //シャワー-エレキF

//C# TO C++ CONVERTER TODO TASK: A 'delete vents6' statement was not added since vents6 was assigned to another object. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete vents5' statement was not added since vents5 was assigned to another object. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete vents4' statement was not added since vents4 was assigned to another object. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete vents3' statement was not added since vents3 was assigned to another object. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete vents2' statement was not added since vents2 was assigned to another object. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete vents1' statement was not added since vents1 was assigned to another object. Handle memory management manually.
		}
	}

	void AdditionalVents::ClearAndReload()
	{
		std::wcout << L"additionalVentsClearAndReload" << std::endl;
		flag = false;
		AllVents = std::vector<AdditionalVents*>();
	}
}
