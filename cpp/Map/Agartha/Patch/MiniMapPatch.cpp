#include "MiniMapPatch.h"
#include "../../ImageManager.h"
#include "../ImageManager.h"
#include "../../../Helpers/FastDestroyableSingleton.h"
#include "../../../LateTask.h"

using namespace HarmonyLib;
using namespace TMPro;
using namespace UnityEngine;

namespace SuperNewRoles::Map::Agartha::Patch
{

	void MiniMapPatch::MinimapChange(MapBehaviour *__instance)
	{
		Transform *MapObject = GameObject::Find(L"HqMap(Clone)")->transform;
		Transform *Background = MapObject->FindChild(L"Background");
		Transform *RoomNames = MapObject->FindChild(L"RoomNames");
		SpriteRenderer *render = Background->GetComponent<SpriteRenderer*>();
		render->sprite = ImageManager::getMiniMap();
		render->transform.localScale *= 0.75f;
		//AdminRoomName
		Transform *AdminRoom = RoomNames->FindChild(L"Admin");
		AdminRoom->GetComponent<TextMeshPro*>()->text = FastDestroyableSingleton<TranslationController*>::getInstance().GetString(StringNames::Admin);
		AdminRoom->localPosition = new Vector3(0.2f, -0.95f, 0.0f);

		//CommsRoomName
		Transform *CommsRoom = RoomNames->FindChild(L"Comms");
		CommsRoom->localPosition = new Vector3(-1.72f, 1.95f, 0.0f); //1.38f, -0.95f, 0f);

		//LaboratoryRoomName
		Transform *LaboratoryRoom = RoomNames->FindChild(L"Laboratory");
		LaboratoryRoom->localPosition = new Vector3(2.35f, -0.95f, 0.0f);

		//MedBayRoomName
		Transform *MedBayRoom = RoomNames->FindChild(L"MedBay");
		MedBayRoom->localPosition = new Vector3(-1.7f, 0.52f, 0.0f);

		//SecurityRoomName
		Transform *SecurityRoom = RoomNames->FindChild(L"Storage");
		SecurityRoom->name = L"Security";
		new LateTask([&] ()
		{
			SecurityRoom->GetComponent<TextMeshPro*>()->text = FastDestroyableSingleton<TranslationController*>::getInstance().GetString(StringNames::Security);
		}, 0.0f, L"SetMapText");
		SecurityRoom->localPosition = new Vector3(1.38f, -0.95f, 0.0f);

		//LifeSuppRoomName
		Transform *LifeSuppRoom = RoomNames->FindChild(L"Lockers");
		LifeSuppRoom->name = L"LifeSupp";
		new LateTask([&] ()
		{
			LifeSuppRoom->GetComponent<TextMeshPro*>()->text = FastDestroyableSingleton<TranslationController*>::getInstance().GetString(StringNames::LifeSupp);
		}, 0.0f, L"SetMapText");
		LifeSuppRoom->localPosition = new Vector3(-1.72f, -0.48f, 0.0f);

		//MeetingRoomName
		Transform *MeetingRoom = RoomNames->FindChild(L"Decontam");
		MeetingRoom->name = L"Meeting";
		new LateTask([&] ()
		{
			MeetingRoom->GetComponent<TextMeshPro*>()->text = FastDestroyableSingleton<TranslationController*>::getInstance().GetString(StringNames::MeetingRoom);
		}, 0.0f, L"SetMapText");
		MeetingRoom->localPosition = new Vector3(0.8f, 0.85f, 0.0f);

		//ElectricalRoomName
		Transform *ElectricalRoom = RoomNames->FindChild(L"LaunchPad");
		ElectricalRoom->name = L"Electrical";
		new LateTask([&] ()
		{
			ElectricalRoom->GetComponent<TextMeshPro*>()->text = FastDestroyableSingleton<TranslationController*>::getInstance().GetString(StringNames::Electrical);
		}, 0.0f, L"SetMapText");
		ElectricalRoom->localPosition = new Vector3(2.27f, 0.85f, 0);

		//ToolRoomName
		Transform *ToolRoom = RoomNames->FindChild(L"Office");
		ToolRoom->name = L"Tool";
		new LateTask([&] ()
		{
			ToolRoom->GetComponent<TextMeshPro*>()->text = ModTranslation::getString(L"Agartha_ToolRoom");
		}, 0.0f, L"SetMapText");
		ToolRoom->localPosition = new Vector3(-1.72f, -1.9f, 0.0f);

		//WareHouseName
		Transform *WareHouse = RoomNames->FindChild(L"Balcony");
		WareHouse->name = L"WareHouse";
		new LateTask([&] ()
		{
			WareHouse->GetComponent<TextMeshPro*>()->text = ModTranslation::getString(L"Agartha_WareHouse");
		}, 0.0f, L"SetMapText");
		WareHouse->localPosition = new Vector3(-3.37f, -1.2f, 0);

		//WorkRoomName
		Transform *WorkRoom = RoomNames->FindChild(L"Reactor");
		WorkRoom->name = L"WorkRoom";
		new LateTask([&] ()
		{
			WorkRoom->GetComponent<TextMeshPro*>()->text = ModTranslation::getString(L"Agartha_WorkRoom");
		}, 0.0f, L"SetMapText");
		WorkRoom->localPosition = new Vector3(-3.37f, 1.25f, 0);

		RoomNames->FindChild(L"Cafeteria").gameObject.SetActive(false);
		RoomNames->FindChild(L"Greenhouse").gameObject.SetActive(false);
	}
}
