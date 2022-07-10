#include "TitleMenuPatch.h"

using namespace HarmonyLib;
using namespace Newtonsoft::Json::Linq;
using namespace SuperNewRoles::CustomCosmetics;
using namespace SuperNewRoles::Patch;
using namespace Twitch;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace static UnityEngine::UI::Button;

namespace SuperNewRoles::Patch
{

const std::wstring MainMenuPatch::snrdiscordserver = L"https://discord.gg/6DjxfaDsAj";

	void MainMenuPatch::Prefix(MainMenuManager *__instance)
	{
		auto template_Keyword = GameObject::Find(L"ExitGameButton");
		if (template_Keyword == nullptr)
		{
			return;
		}

		auto buttonDiscord = UnityEngine::Object::Instantiate(template_Keyword, nullptr);
		if (FileSystem::fileExists(StringHelper::replace(Assembly::GetExecutingAssembly()->Location, L"SuperNewRoles.dll", L"Submerged.dll")))
		{
			buttonDiscord->transform->localPosition = new Vector3(buttonDiscord->transform.localPosition.x, buttonDiscord->transform.localPosition.y + 0.6f, buttonDiscord->transform.localPosition.z);
		}
		else
		{
			buttonDiscord->transform->localPosition = new Vector3(buttonDiscord->transform.localPosition.x, buttonDiscord->transform.localPosition.y + 1.2f, buttonDiscord->transform.localPosition.z);
		}

		auto textDiscord = buttonDiscord->transform.GetChild(0)->GetComponent<TMPro::TMP_Text*>();
		std::function<void(float)> tempVar([&] (p)
		{
			textDiscord->SetText(L"Discord");
		});
		__instance->StartCoroutine(Effects::Lerp(0.1f, &tempVar));

		PassiveButton *passiveButtonDiscord = buttonDiscord->GetComponent<PassiveButton*>();
		SpriteRenderer *buttonSpriteDiscord = buttonDiscord->GetComponent<SpriteRenderer*>();

		passiveButtonDiscord->OnClick = new Button::ButtonClickedEvent();
		passiveButtonDiscord->OnClick.AddListener(static_cast<std::function<void()>>([&] ()
		{
			Application->OpenURL(snrdiscordserver);
		}));

		Color *discordColor = new Color32(88, 101, 242, std::numeric_limits<unsigned char>::max());
		buttonSpriteDiscord->color = textDiscord->color = discordColor;
		passiveButtonDiscord->OnMouseOut.AddListener(static_cast<std::function<void()>>([&] ()
		{
			buttonSpriteDiscord->color = textDiscord->color = discordColor;
		}));

		auto buttonTwitter = UnityEngine::Object::Instantiate(template_Keyword, nullptr);
		if (FileSystem::fileExists(StringHelper::replace(Assembly::GetExecutingAssembly()->Location, L"SuperNewRoles.dll", L"Submerged.dll")))
		{
			buttonTwitter->transform->localPosition = new Vector3(buttonTwitter->transform.localPosition.x, buttonTwitter->transform.localPosition.y + 1.2f, buttonTwitter->transform.localPosition.z);
		}
		else
		{
			buttonTwitter->transform->localPosition = new Vector3(buttonTwitter->transform.localPosition.x, buttonTwitter->transform.localPosition.y + 1.8f, buttonTwitter->transform.localPosition.z);
		}

		auto textTwitter = buttonTwitter->transform.GetChild(0)->GetComponent<TMPro::TMP_Text*>();
		std::function<void(float)> tempVar2([&] (p)
		{
			textTwitter->SetText(L"Twitter");
		});
		__instance->StartCoroutine(Effects::Lerp(0.1f, &tempVar2));

		PassiveButton *passiveButtonTwitter = buttonTwitter->GetComponent<PassiveButton*>();
		SpriteRenderer *buttonSpriteTwitter = buttonTwitter->GetComponent<SpriteRenderer*>();

		passiveButtonTwitter->OnClick = new Button::ButtonClickedEvent();

		Color *TwitterColor = new Color32(29, 155, 240, std::numeric_limits<unsigned char>::max());
		buttonSpriteTwitter->color = textTwitter->color = TwitterColor;
		passiveButtonTwitter->OnMouseOut.AddListener(static_cast<std::function<void()>>([&] ()
		{
			buttonSpriteTwitter->color = textTwitter->color = TwitterColor;
		}));

		auto buttonTwitterSNRDevs = UnityEngine::Object::Instantiate(template_Keyword, nullptr);
		buttonTwitterSNRDevs->SetActive(false);

		auto buttonTwitterSuperNewRoles = UnityEngine::Object::Instantiate(template_Keyword, nullptr);
		buttonTwitterSuperNewRoles->SetActive(false);

		passiveButtonTwitter->OnClick.AddListener(static_cast<std::function<void()>>([&] ()
		{
			buttonTwitterSNRDevs->SetActive(true);
			auto textTwitterSNRDevs = buttonTwitterSNRDevs->transform.GetChild(0)->GetComponent<TMPro::TMP_Text*>();
			std::function<void(float)> tempVar3([&] (p)
			{
					textTwitterSNRDevs->SetText(L"SuperNewRolesの人");
			});
			__instance->StartCoroutine(Effects::Lerp(0.1f, &tempVar3));
			buttonTwitterSNRDevs->transform->localPosition = new Vector3(buttonTwitter->transform.localPosition.x + 1.1f, buttonTwitter->transform.localPosition.y + -0.3f, buttonTwitter->transform.localPosition.z);
			PassiveButton *passivebuttonTwitterSNRDevs = buttonTwitterSNRDevs->GetComponent<PassiveButton*>();
			SpriteRenderer *buttonSpriteTwitterSNRDevs = buttonTwitterSNRDevs->GetComponent<SpriteRenderer*>();
			passivebuttonTwitterSNRDevs->OnClick = new Button::ButtonClickedEvent();
			passivebuttonTwitterSNRDevs->OnClick.AddListener(static_cast<std::function<void()>>([&] ()
			{
				Application->OpenURL(L"https://twitter.com/SNRDevs");
			}));
    
			buttonTwitterSuperNewRoles->SetActive(true);
			auto textTwitterSuperNewRoles = buttonTwitterSuperNewRoles->transform.GetChild(0)->GetComponent<TMPro::TMP_Text*>();
			std::function<void(float)> tempVar4([&] (p)
			{
					textTwitterSuperNewRoles->SetText(L"Super New Roles");
			});
			__instance->StartCoroutine(Effects::Lerp(0.1f, &tempVar4));
			buttonTwitterSuperNewRoles->transform->localPosition = new Vector3(buttonTwitter->transform.localPosition.x + 1.1f, buttonTwitter->transform.localPosition.y + 0.3f, buttonTwitter->transform.localPosition.z);
			PassiveButton *passivebuttonTwitterSuperNewRoles = buttonTwitterSuperNewRoles->GetComponent<PassiveButton*>();
			SpriteRenderer *buttonSpriteTwitterSuperNewRoles = buttonTwitterSuperNewRoles->GetComponent<SpriteRenderer*>();
			passivebuttonTwitterSuperNewRoles->OnClick = new Button::ButtonClickedEvent();
			passivebuttonTwitterSuperNewRoles->OnClick.AddListener(static_cast<std::function<void()>>([&] ()
			{
				Application->OpenURL(L"https://twitter.com/SuperNewRoles");
			}));
		}));

		delete TwitterColor;
		delete discordColor;
	}
}
