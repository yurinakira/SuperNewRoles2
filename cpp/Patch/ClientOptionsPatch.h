#pragma once

#include <string>
#include <vector>
#include <limits>
#include <functional>
#include <optional>
#include "../stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace SuperNewRoles::Patch { class SelectionBehaviour; }

using namespace HarmonyLib;
using namespace TMPro;
using namespace UnityEngine;
using namespace UnityEngine::Events;
using namespace UnityEngine::SceneManagement;
using namespace static UnityEngine::UI::Button;
//C# TO C++ CONVERTER TODO TASK: C# to C++ Converter could not confirm whether this is a namespace alias or a type alias:
//using Object = UnityEngine::Object;

namespace SuperNewRoles::Patch
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch] public static class ClientOptionsPatch
	class ClientOptionsPatch final
	{
	private:
		static std::vector<SelectionBehaviour*> AllOptions;

		static GameObject *popUp;
		static TextMeshPro *titleText;

		static ToggleButtonBehaviour *moreOptions;
		static std::vector<ToggleButtonBehaviour*> modButtons;
		static TextMeshPro *titleTextTitle;

		static ToggleButtonBehaviour *buttonPrefab;
		static std::optional<Vector3*> _origin;

	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPostfix][HarmonyPatch(typeof(MainMenuManager), nameof(MainMenuManager.Start))] public static void MainMenuManager_StartPostfix(MainMenuManager __instance)
		static void MainMenuManager_StartPostfix(MainMenuManager *__instance);
		static float xOffset;
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(OptionsMenuBehaviour), nameof(OptionsMenuBehaviour.Update))] class OptionsUpdate
		class OptionsUpdate
		{
		public:
			static void Postfix(OptionsMenuBehaviour *__instance);
		};
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPostfix][HarmonyPatch(typeof(OptionsMenuBehaviour), nameof(OptionsMenuBehaviour.Start))] public static void OptionsMenuBehaviour_StartPostfix(OptionsMenuBehaviour __instance)
		static void OptionsMenuBehaviour_StartPostfix(OptionsMenuBehaviour *__instance);

	private:
		static void CreateCustom(OptionsMenuBehaviour *prefab);

		static void InitializeMoreButton(OptionsMenuBehaviour *__instance);

		static void RefreshOpen(OptionsMenuBehaviour *__instance);

		static void CheckSetTitle();

		static void SetUpOptions(OptionsMenuBehaviour *__instance);

		static std::vector<GameObject*> GetAllChilds(GameObject *Go);

	public:
		static void updateTranslations();

	public:
		class SelectionBehaviour
		{
		public:
			std::wstring Title;
			std::function<bool()> OnClick;
			bool DefaultValue = false;

			SelectionBehaviour(const std::wstring &title, std::function<bool()> onClick, bool defaultValue);
		};
	};

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(TextBoxTMP), nameof(TextBoxTMP.SetText))] public static class HiddenTextPatch
	class HiddenTextPatch final
	{
	private:
		static void Postfix(TextBoxTMP *__instance);
	};
}
