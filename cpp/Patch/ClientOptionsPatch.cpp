//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "ClientOptionsPatch.h"
#include "../TranslateDate.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../Config.h"

using namespace HarmonyLib;
using namespace TMPro;
using namespace UnityEngine;
using namespace UnityEngine::Events;
using namespace UnityEngine::SceneManagement;
using namespace static UnityEngine::UI::Button;

namespace SuperNewRoles::Patch
{

std::vector<SelectionBehaviour*> ClientOptionsPatch::AllOptions = { new SelectionBehaviour(L"CustomStremerMode", [&] ()
{
			ConfigRoles::getStreamerMode()->Value = !ConfigRoles::getStreamerMode()->Value;
}, ConfigRoles::getStreamerMode()->Value), new SelectionBehaviour(L"CustomAutoUpdate", [&] ()
{
			ConfigRoles::getAutoUpdate()->Value = !ConfigRoles::getAutoUpdate()->Value;
		}, ConfigRoles::getAutoUpdate()->Value), new SelectionBehaviour(L"CustomAutoCopyGameCode", [&] ()
		{
			ConfigRoles::getAutoCopyGameCode()->Value = !ConfigRoles::getAutoCopyGameCode()->Value;
		}, ConfigRoles::getAutoCopyGameCode()->Value), new SelectionBehaviour(L"CustomProcessDown", [&] ()
		{
			ConfigRoles::getCustomProcessDown()->Value = !ConfigRoles::getCustomProcessDown()->Value;
		}, ConfigRoles::getCustomProcessDown()->Value), new SelectionBehaviour(L"CustomIsVersionErrorView", [&] ()
		{
			ConfigRoles::isVersionErrorView()->Value = !ConfigRoles::isVersionErrorView()->Value;
		}, ConfigRoles::isVersionErrorView()->Value), new SelectionBehaviour(L"CustomHideTaskArrows", [&] ()
		{
			TasksArrowsOption::hideTaskArrows = ConfigRoles::getHideTaskArrows()->Value = !ConfigRoles::getHideTaskArrows()->Value;
		}, ConfigRoles::getHideTaskArrows()->Value), new SelectionBehaviour(L"CustomDownloadSuperNewNamePlates", [&] ()
		{
			ConfigRoles::getDownloadSuperNewNamePlates()->Value = !ConfigRoles::getDownloadSuperNewNamePlates()->Value;
		}, ConfigRoles::getDownloadSuperNewNamePlates()->Value)};
GameObject *ClientOptionsPatch::popUp;
TextMeshPro *ClientOptionsPatch::titleText;
ToggleButtonBehaviour *ClientOptionsPatch::moreOptions;
std::vector<ToggleButtonBehaviour*> ClientOptionsPatch::modButtons;
TextMeshPro *ClientOptionsPatch::titleTextTitle;
ToggleButtonBehaviour *ClientOptionsPatch::buttonPrefab;
std::optional<Vector3*> ClientOptionsPatch::_origin;

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
	void ClientOptionsPatch::MainMenuManager_StartPostfix(MainMenuManager *__instance)
	{
		// Prefab for the title
		auto tmp = __instance->Announcement.transform.Find(L"Title_Text")->gameObject.GetComponent<TextMeshPro*>();
		tmp->alignment = TextAlignmentOptions::Center;
		tmp->transform.localPosition += Vector3::left * 0.2f;
		titleText = UnityEngine::Object::Instantiate(tmp);
		UnityEngine::Object::Destroy(titleText->GetComponent<TextTranslatorTMP*>());
		titleText->gameObject.SetActive(false);
		UnityEngine::Object::DontDestroyOnLoad(titleText);
	}

float ClientOptionsPatch::xOffset = 1.75f;

	void ClientOptionsPatch::OptionsUpdate::Postfix(OptionsMenuBehaviour *__instance)
	{
		if (__instance->CensorChatButton != nullptr)
		{
			__instance->CensorChatButton.gameObject.SetActive(false);
		}
		if (__instance->EnableFriendInvitesButton != nullptr)
		{
			__instance->EnableFriendInvitesButton.gameObject.SetActive(false);
		}
		if (__instance->StreamerModeButton != nullptr)
		{
			__instance->StreamerModeButton.gameObject.SetActive(false);
		}
		if (__instance->ColorBlindButton != nullptr)
		{
			__instance->ColorBlindButton.gameObject.SetActive(false);
		}
	}

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
	void ClientOptionsPatch::OptionsMenuBehaviour_StartPostfix(OptionsMenuBehaviour *__instance)
	{
		if (!__instance->CensorChatButton)
		{
			return;
		}
		if (!popUp)
		{
			CreateCustom(__instance);
		}

		if (!buttonPrefab)
		{
			buttonPrefab = UnityEngine::Object::Instantiate(__instance->CensorChatButton);
			UnityEngine::Object::DontDestroyOnLoad(buttonPrefab);
			buttonPrefab->name = L"CensorChatPrefab";
			buttonPrefab->gameObject.SetActive(false);
		}
		SetUpOptions(__instance);
		InitializeMoreButton(__instance);
	}

	void ClientOptionsPatch::CreateCustom(OptionsMenuBehaviour *prefab)
	{
		popUp = UnityEngine::Object::Instantiate(prefab->gameObject);
		UnityEngine::Object::DontDestroyOnLoad(popUp);
		auto transform = popUp->transform;
		auto pos = transform->localPosition;
		pos->z = -810.0f;
		transform->localPosition = pos;

		UnityEngine::Object::Destroy(popUp->GetComponent<OptionsMenuBehaviour*>());
		for (auto gObj : *popUp->gameObject.GetAllChilds())
		{
			L"Background" and_Keyword = dynamic_cast < L"Background"*>(gObj->name);
			if (and_Keyword == nullptr not_Keyword L"CloseButton")
			{
				UnityEngine::Object::Destroy(gObj);
			}
		}
		popUp->SetActive(false);
	}

	void ClientOptionsPatch::InitializeMoreButton(OptionsMenuBehaviour *__instance)
	{
		moreOptions = UnityEngine::Object::Instantiate(buttonPrefab, __instance->CensorChatButton.transform.parent);
		auto transform = __instance->CensorChatButton.transform;
		_origin = _origin ? _origin : transform->localPosition;

		transform->localPosition = _origin.value() + Vector3::left * 1.3f;
		moreOptions->transform->localPosition = _origin.value() + Vector3::right * 1.3f;
		auto pos = moreOptions->transform.localPosition;
		moreOptions->transform.localScale *= 1.1f;
		float count = 1.55f;
		moreOptions->transform->localPosition = new Vector3(pos->x * 1.5f, pos->y * count, pos->z);
		auto trans = moreOptions->transform.localPosition;
		moreOptions->gameObject.SetActive(true);
		trans = moreOptions->transform.position;
		moreOptions->Text.text = ModTranslation::getString(L"modOptionsText");
		auto moreOptionsButton = moreOptions->GetComponent<PassiveButton*>();
		moreOptionsButton->OnClick = new ButtonClickedEvent();
		moreOptionsButton->OnClick.AddListener(static_cast<std::function<void()>>([&] ()
		{
			if (!popUp)
			{
				return;
			}
    
			if (__instance->transform.parent && __instance->transform->parent == FastDestroyableSingleton<HudManager*>::getInstance().transform)
			{
				popUp->transform.SetParent(FastDestroyableSingleton<HudManager*>::getInstance().transform);
				popUp->transform->localPosition = new Vector3(0, 0, -800.0f);
			}
			else
			{
				popUp->transform.SetParent(nullptr);
				UnityEngine::Object::DontDestroyOnLoad(popUp);
			}
			CheckSetTitle();
			RefreshOpen(__instance);
		}));
	}


//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
