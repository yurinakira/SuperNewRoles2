#include "DefaultCustomSettingChangePatch.h"

using namespace BepInEx::Configuration;
using namespace HarmonyLib;
using namespace Hazel;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

	void DefaultCustomSettingChangePatch::GameSettingMenuStartPatch::Prefix(GameSettingMenu *__instance)
	{
		__instance->HideForOnline = std::vector<Transform*> ();
	}

	void DefaultCustomSettingChangePatch::GameSettingMenuStartPatch::Postfix(GameSettingMenu *__instance)
	{
		// Setup mapNameTransform
		auto mapNameTransform = __instance->AllItems.FirstOrDefault([&] (std::any x)
		{
			return x::gameObject::activeSelf && x::name->Equals(L"MapName", StringComparison::OrdinalIgnoreCase);
		});
		if (mapNameTransform == nullptr)
		{
			return;
		}

		auto options = new Il2CppSystem::Collections::Generic->List<Il2CppSystem::Collections::Generic::KeyValuePair<std::wstring, int>*>();
		for (int i = 0; i < Constants->MapNames->Length; i++)
		{
			auto kvp = new Il2CppSystem::Collections::Generic->KeyValuePair<std::wstring, int>();
			kvp->key = Constants->MapNames[i];
			kvp->value = i;
			options->Add(kvp);

//C# TO C++ CONVERTER TODO TASK: A 'delete kvp' statement was not added since kvp was passed to a method or constructor. Handle memory management manually.
		}
		mapNameTransform->GetComponent<KeyValueOption*>()->Values = options;

		delete options;
	}
}
