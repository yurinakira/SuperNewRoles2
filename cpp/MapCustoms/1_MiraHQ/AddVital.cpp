#include "AddVital.h"
#include "../main.h"
#include "../MapCustom.h"

using namespace BepInEx::IL2CPP::Utils;
using namespace HarmonyLib;
using namespace Hazel;
using namespace UnityEngine;
using namespace UnityEngine::AddressableAssets;
using namespace UnityEngine::ResourceManagement::AsyncOperations;

namespace SuperNewRoles::MapCustoms
{

	void AddVitals::Postfix()
	{
		if (MapCustomHandler::isMapCustom(MapCustomHandler::MapCustomId::Mira) && MapCustoms::MapCustom::AddVitalsMira->getBool())
		{
			Transform *Vital = GameObject::Instantiate(getPolusObject()->transform.FindChild(L"Office").FindChild(L"panel_vitals"), GameObject::Find(L"MiraShip(Clone)")->transform);
			Vital->transform->position = new Vector3(8.5969f, 14.6337f, 0.0142f);
		}
	}

	GameObject *AddVitals::getPolusObject()
	{
		return Polus->gameObject;
	}

ShipStatus *AddVitals::Polus;

	System::Collections::IEnumerator *AddVitals::LoadPolus()
	{
		while (static_cast<UnityEngine::Object*>(static_cast<std::any>(AmongUsClient::Instance)) == nullptr)
		{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
			yield return nullptr;
		}
		AsyncOperationHandle<GameObject*> *polusAsset = AmongUsClient::Instance->ShipPrefabs->ToArray()[2].LoadAsset<GameObject*>();
		while (!polusAsset->IsDone)
		{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
			yield return nullptr;
		}
		Polus = polusAsset->Result->GetComponent<ShipStatus*>();
	}

bool AmongUsClient_Awake_Patch::Loaded = false;

	void AmongUsClient_Awake_Patch::Prefix(AmongUsClient *__instance)
	{
		if (!Loaded)
		{
			(static_cast<MonoBehaviour*>(static_cast<std::any>(__instance)))->StartCoroutine(AddVitals::LoadPolus());
		}
		Loaded = true;
	}
}
