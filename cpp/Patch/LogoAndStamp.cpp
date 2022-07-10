//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "LogoAndStamp.h"
#include "../obj/Debug/netstandard2.1/ThisAssembly.h"
#include "../TranslateDate.h"
#include "../AutoUpdate.h"
#include "../Main.h"
#include "DebugMode.h"
#include "../Mode/ModeHandler.h"
#include "../Helpers/CachedPlayer.h"
#include "../Config.h"
#include "../CustomCosmetics/DownLoadCustomhat.h"
#include "../CustomCosmetics/DownLoadCustomPlate.h"
#include "../CustomCosmetics/DownLoadCustomVisor.h"
#include "../ModHelpers.h"
#include "HorseModePatch.h"

using namespace BepInEx::IL2CPP::Utils;
using namespace HarmonyLib;
using namespace Newtonsoft::Json::Linq;
using namespace SuperNewRoles::CustomCosmetics;
using namespace SuperNewRoles::Patch;
using namespace TMPro;
using namespace Twitch;
using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace SuperNewRoles::Patches
{

std::wstring CredentialsPatch::baseCredentials = StringHelper::formatSimple(LR"(<size=130%><color=#ffa500>Super</color><color=#ff0000>New</color><color=#00ff00>Roles</color></size> v{0})", SuperNewRolesPlugin::Version);

	void CredentialsPatch::VersionShowerPatch::Prefix(VersionShower *__instance)
	{
		//CustomPlate.UnlockedNamePlatesPatch.Postfix(HatManager.Instance);
	}

std::wstring CredentialsPatch::VersionShowerPatch::modColor = L"#a6d289";

	void CredentialsPatch::VersionShowerPatch::Postfix(VersionShower *__instance)
	{

		auto amongUsLogo = GameObject::Find(L"bannerLogo_AmongUs");
		if (amongUsLogo == nullptr)
		{
			return;
		}
		auto credentials = UnityEngine::Object::Instantiate<TMPro::TextMeshPro*>(__instance->text);
		credentials->transform->position = new Vector3(0, 0.0f, 0);
		//ブランチ名表示
		std::wstring credentialsText = L"";
		if (ThisAssembly::Git::Branch != L"master") //masterビルド以外の時
		{
			//色+ブランチ名+コミット番号
			credentialsText = StringHelper::formatSimple(L"\r\n<color={0}>{1}({2})</color>", modColor, ThisAssembly::Git::Branch, ThisAssembly::Git::Commit);
		}
		credentialsText += ModTranslation::getString(L"creditsMain");
		credentials->SetText(credentialsText);

		credentials->alignment = TMPro::TextAlignmentOptions::Center;
		credentials->fontSize *= 0.9f;
		AutoUpdate::checkForUpdate(credentials);

		auto version = UnityEngine::Object::Instantiate<TMPro::TextMeshPro*>(credentials);
		version->transform->position = new Vector3(0, -0.35f, 0);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		version->SetText(std::wstring::Format(ModTranslation::getString(L"creditsVersion"), SuperNewRolesPlugin::Version->ToString()));

		credentials->transform.SetParent(amongUsLogo->transform);
		version->transform.SetParent(amongUsLogo->transform);
	}

	void CredentialsPatch::PingTrackerPatch::Postfix(PingTracker *__instance)
	{
		__instance->text->alignment = TMPro::TextAlignmentOptions::TopRight;
		if (AmongUsClient::Instance->GameState == InnerNet::InnerNetClient::GameStates::Started)
		{
			__instance->text->text = StringHelper::formatSimple(L"{0}\n{1}", baseCredentials, __instance->text.text);
			try
			{
				if (DebugMode::IsDebugMode())
				{
					__instance->text.text += L"\n" + ModTranslation::getString(L"DebugModeOn");
				}
				if (!Mode::ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {Mode::ModeId::Default}))
				{
					__instance->text.text += L"\n" + ModTranslation::getString(L"SettingMode") + L":" + Mode::ModeHandler::ThisModeSetting->getString();
				}
			}
			catch (...)
			{
			}
			//ブランチ名表示
			if (ThisAssembly::Git::Branch != L"master") //masterビルド以外の時
			{
				//改行+Branch名+コミット番号
				__instance->text.text += L"\n" + (StringHelper::formatSimple(L"{0}({1})", ThisAssembly::Git::Branch, ThisAssembly::Git::Commit));
			}
			if (CachedPlayer::LocalPlayer->Data->IsDead)
			{
				__instance->transform->localPosition = new Vector3(3.45f, __instance->transform.localPosition.y, __instance->transform.localPosition.z);
			}
			else
			{
				__instance->transform->localPosition = new Vector3(4.2f, __instance->transform.localPosition.y, __instance->transform.localPosition.z);
			}
		}
		else
		{
			__instance->text->text = StringHelper::formatSimple(L"{0}\n{1}\n{2}", baseCredentials, ModTranslation::getString(L"creditsFull"), __instance->text.text);
			__instance->transform->localPosition = new Vector3(3.5f, __instance->transform.localPosition.y, __instance->transform.localPosition.z);
		}
	}

GenericPopup *CredentialsPatch::popup;
SpriteRenderer *CredentialsPatch::LogoPatch::renderer;
Sprite *CredentialsPatch::LogoPatch::bannerSprite;
Sprite *CredentialsPatch::LogoPatch::horseBannerSprite;

	System::Collections::IEnumerator *CredentialsPatch::LogoPatch::ViewBoosterCoro(MainMenuManager *__instance)
	{
		while (true)
		{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
			yield return new WaitForSeconds(1.0f);
			if (Downloaded)
			{
				if (__instance != nullptr)
				{
					ViewBoosterPatch(__instance);
				}
				break;
			}
		}
	}

std::wstring CredentialsPatch::LogoPatch::SponsersData = L"";
std::wstring CredentialsPatch::LogoPatch::DevsData = L"";

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task<HttpStatusCode> FetchBoosters()
	Task<HttpStatusCode> *CredentialsPatch::LogoPatch::FetchBoosters()
	{
		if (!Downloaded)
		{
			Downloaded = true;
			HttpClient *http = new HttpClient();
			http->DefaultRequestHeaders->CacheControl = new CacheControlHeaderValue();
			http->DefaultRequestHeaders.CacheControl->NoCache = true;
			http->DefaultRequestHeaders.CacheControl->OnlyIfCached = false;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
			System::Uri tempVar(L"https://raw.githubusercontent.com/ykundesu/SuperNewRoles/master/CreditsData.json");
			auto response = await http->GetAsync(&tempVar, HttpCompletionOption::ResponseContentRead);
			try
			{
				if (response->StatusCode != HttpStatusCode::OK)
				{
					SuperNewRolesPlugin::Logger->LogInfo(L"NOTOK!!!");

					delete http;
					return response->StatusCode;
				};
				if (response->Content == nullptr)
				{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
					std::wcout << L"Server returned no data: " << response->StatusCode.ToString() << std::endl;

					delete http;
					return HttpStatusCode::ExpectationFailed;
				}
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to 'await' in C++:
				std::wstring json = await response->Content->ReadAsStringAsync();
				JToken *jobj = JObject::Parse(json);

				auto devs = jobj[L"Devs"];
				for (JToken *current = devs->First; current != nullptr; current = current->Next)
				{
					if (current->HasValues)
					{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
						DevsData += current[L"name"] == nullptr ? L"" : current[L"name"].ToString() + L"\n";
					}
				}

				auto Sponsers = jobj[L"Sponsers"];
				for (JToken *current = Sponsers->First; current != nullptr; current = current->Next)
				{
					if (current->HasValues)
					{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
						SponsersData += current[L"name"] == nullptr ? L"" : current[L"name"].ToString() + L"\n";
					}
				}
			}
			catch (const std::runtime_error &e)
			{
				SuperNewRolesPlugin::Logger->LogError(e);
			}

			delete http;
		}
		return HttpStatusCode::OK;
	}

GameObject *CredentialsPatch::LogoPatch::CreditsPopup;

	void CredentialsPatch::LogoPatch::ViewBoosterPatch(MainMenuManager *__instance)
	{
		auto template_Keyword = __instance->transform.FindChild(L"StatsPopup");

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
