#include "CustomServer.h"
#include "../Config.h"

using namespace BepInEx;
using namespace BepInEx::Configuration;
using namespace BepInEx::IL2CPP;
using namespace HarmonyLib;
using namespace UnityEngine;
using namespace UnityEngine::Events;
using namespace UnityEngine::UI;

namespace SuperNewRoles::Patch
{

TextBoxTMP *RegionMenuOpenPatch::ipField;
TextBoxTMP *RegionMenuOpenPatch::portField;

	void RegionMenuOpenPatch::Postfix(RegionMenu *__instance)
	{
		auto template_Keyword = DestroyableSingleton<JoinGameButton*>::Instance;
		auto joinGameButtons = GameObject::FindObjectsOfType<JoinGameButton*>();
		for (auto t : *joinGameButtons)
		{ // The correct button has a background, the other 2 dont
			if (t->GameIdText != nullptr && t->GameIdText.Background != nullptr)
			{
				template_Keyword = t;
				break;
			}
		}
		if (template_Keyword == nullptr || template_Keyword->GameIdText == nullptr)
		{
			return;
		}

		if (ipField == nullptr || ipField->gameObject == nullptr)
		{
			ipField = UnityEngine::Object::Instantiate(template_Keyword->GameIdText, __instance->transform);
			ipField->gameObject->name = L"IpTextBox";
			auto arrow = ipField->transform.FindChild(L"arrowEnter");
			if (arrow == nullptr || arrow->gameObject == nullptr)
			{
				return;
			}
			UnityEngine::Object::DestroyImmediate(arrow->gameObject);

			ipField->transform->localPosition = new Vector3(0.225f, -1.0f, -100.0f);
			ipField->characterLimit = 30;
			ipField->AllowSymbols = true;
			ipField->ForceUppercase = false;
			ipField->SetText(ConfigRoles::getIp()->Value);
			std::function<void(float)> tempVar([&] (p)
			{
				ipField->outputText.SetText(ConfigRoles::getIp()->Value);
				ipField->SetText(ConfigRoles::getIp()->Value);
			});
			__instance->StartCoroutine(Effects::Lerp(0.1f, &tempVar));

			ipField->ClearOnFocus = false;
			ipField->OnEnter = ipField->OnChange = new Button::ButtonClickedEvent();
			ipField->OnFocusLost = new Button::ButtonClickedEvent();
			ipField->OnChange.AddListener(static_cast<UnityAction*>(onEnterOrIpChange));
			ipField->OnFocusLost.AddListener(static_cast<UnityAction*>(onFocusLost));

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//			void onEnterOrIpChange()
	//				{
	//					ConfigRoles.Ip.Value = ipField.text;
	//				}

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//			void onFocusLost()
	//				{
	//					UpdateRegions();
	//					__instance.ChooseOption(ServerManager.DefaultRegions[ServerManager.DefaultRegions.Length - 1]);
	//				}
		}

		if (portField == nullptr || portField->gameObject == nullptr)
		{
			portField = UnityEngine::Object::Instantiate(template_Keyword->GameIdText, __instance->transform);
			portField->gameObject->name = L"PortTextBox";
			auto arrow = portField->transform.FindChild(L"arrowEnter");
			if (arrow == nullptr || arrow->gameObject == nullptr)
			{
				return;
			}
			UnityEngine::Object::DestroyImmediate(arrow->gameObject);

			portField->transform->localPosition = new Vector3(0.225f, -1.75f, -100.0f);
			portField->characterLimit = 5;
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
			portField->SetText(ConfigRoles::getPort()->Value->ToString());
			std::function<void(float)> tempVar2([&] (p)
			{
				portField->outputText.SetText(ConfigRoles::getPort()->Value->ToString());
				portField->SetText(ConfigRoles::getPort()->Value->ToString());
			});
			__instance->StartCoroutine(Effects::Lerp(0.1f, &tempVar2));

			portField->ClearOnFocus = false;
			portField->OnEnter = portField->OnChange = new Button::ButtonClickedEvent();
			portField->OnFocusLost = new Button::ButtonClickedEvent();
			portField->OnChange.AddListener(static_cast<UnityAction*>(onEnterOrPortFieldChange));
			portField->OnFocusLost.AddListener(static_cast<UnityAction*>(onFocusLost));

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//			void onEnterOrPortFieldChange()
	//				{
	//					if (ushort.TryParse(portField.text, out ushort port))
	//					{
	//						ConfigRoles.Port.Value = port;
	//						portField.outputText.color = Color.white;
	//					}
	//					else
	//					{
	//						portField.outputText.color = Color.red;
	//					}
	//				}

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//			void onFocusLost()
	//				{
	//					UpdateRegions();
	//					__instance.ChooseOption(ServerManager.DefaultRegions[ServerManager.DefaultRegions.Length - 1]);
	//				}
		}
	}

std::vector<IRegionInfo*> RegionMenuOpenPatch::defaultRegions;

	void RegionMenuOpenPatch::UpdateRegions()
	{
		ServerManager *serverManager = DestroyableSingleton<ServerManager*>::Instance;
		std::vector<IRegionInfo*> regions = defaultRegions;

		auto CustomRegion = new DnsRegionInfo(ConfigRoles::getIp()->Value, L"Custom", StringNames::NoTranslation, ConfigRoles::getIp()->Value, ConfigRoles::getPort()->Value, false);
		regions = regions.Concat(std::vector<IRegionInfo*> {CustomRegion->CastFast<IRegionInfo*>()})->ToArray();
		ServerManager->DefaultRegions = regions;
		serverManager->AvailableRegions = regions;

		delete CustomRegion;
	}
}
