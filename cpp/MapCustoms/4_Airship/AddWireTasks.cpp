#include "AddWireTasks.h"
#include "../main.h"
#include "../MapCustom.h"
#include "../../Main.h"

using namespace HarmonyLib;
using namespace UnityEngine;

namespace SuperNewRoles::MapCustoms
{

	void OptimizeMapPatch::Postfix(ShipStatus *__instance)
	{
		addWireTasks();
	}

	void OptimizeMapPatch::addWireTasks()
	{
		// Airship配線タスク追加
		if (MapCustomHandler::isMapCustom(MapCustomHandler::MapCustomId::Airship) && MapCustom::AddWireTask->getBool())
		{
			ActivateWiring(L"task_wiresHallway2", 2);
			ActivateWiring(L"task_electricalside2", 3)->Room = SystemTypes::Armory;
			ActivateWiring(L"task_wireShower", 4);
			ActivateWiring(L"taks_wiresLounge", 5);
			ActivateWiring(L"panel_wireHallwayL", 6);
			ActivateWiring(L"task_wiresStorage", 7);
			ActivateWiring(L"task_electricalSide", 8)->Room = SystemTypes::VaultRoom;
			ActivateWiring(L"task_wiresMeeting", 9);
		}
	}

	Console *OptimizeMapPatch::ActivateWiring(const std::wstring &consoleName, int consoleId)
	{
		Console *console = ActivateConsole(consoleName);

		if (console == nullptr)
		{
			SuperNewRolesPlugin::Logger->LogError(StringHelper::formatSimple(L"consoleName \"{0}\" is null", consoleName));
			return nullptr;
		}

		if (!console->TaskTypes->Contains(TaskTypes::FixWiring))
		{
			auto list = console->TaskTypes.ToList();
			list.push_back(TaskTypes::FixWiring);
			console->TaskTypes = list.ToArray();
		}
		console->ConsoleId = consoleId;
		return console;
	}

	Console *OptimizeMapPatch::ActivateConsole(const std::wstring &objectName)
	{
		GameObject *obj = UnityEngine::GameObject::Find(objectName);
		if (obj == nullptr)
		{
			SuperNewRolesPlugin::Logger->LogError(StringHelper::formatSimple(L"Object \"{0}\" was not found!", objectName));
			return nullptr;
		}
		obj->layer = LayerMask::NameToLayer(L"ShortObjects");
		Console *console = obj->GetComponent<Console*>();
		PassiveButton *button = obj->GetComponent<PassiveButton*>();
		CircleCollider2D *collider = obj->GetComponent<CircleCollider2D*>();
		if (!console)
		{
			console = obj->AddComponent<Console*>();
			console->checkWalls = true;
			console->usableDistance = 0.7f;
			console->TaskTypes = std::vector<TaskTypes*>(0);
			console->ValidTasks = new UnhollowerBaseLib::Il2CppReferenceArray<TaskSet*>(0);
			auto list = ShipStatus::Instance->AllConsoles.ToList();
			list.push_back(console);
			ShipStatus::Instance->AllConsoles = new UnhollowerBaseLib::Il2CppReferenceArray<Console*>(list.ToArray());
		}
		if (console->Image == nullptr)
		{
			console->Image = obj->GetComponent<SpriteRenderer*>();
			console->Image->material = new Material(ShipStatus::Instance->AllConsoles[0].Image->material);
		}
		if (!button)
		{
			button = obj->AddComponent<PassiveButton*>();
			button->OnMouseOut = new UnityEngine::Events->UnityEvent();
			button->OnMouseOver = new UnityEngine::Events->UnityEvent();
			button->_CachedZ_k__BackingField = 0.1f;
			button->CachedZ = 0.1f;
		}
		if (!collider)
		{
			collider = obj->AddComponent<CircleCollider2D*>();
			collider->radius = 0.4f;
			collider->isTrigger = true;
		}
		return console;
	}
}
