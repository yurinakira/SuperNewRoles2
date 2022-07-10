#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <functional>
#include "exceptionhelper.h"
#include "../stringhelper.h"
#include "../tangible_filesystem.h"

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
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch] public static class CredentialsPatch
	class CredentialsPatch final
	{
	public:
		static std::wstring baseCredentials;

	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(VersionShower), nameof(VersionShower.Start))] private static class VersionShowerPatch
		class VersionShowerPatch final
		{
		private:
			static void Prefix(VersionShower *__instance);
		public:
			static std::wstring modColor;
		private:
			static void Postfix(VersionShower *__instance);
		};

	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PingTracker), nameof(PingTracker.Update))] private static class PingTrackerPatch
		class PingTrackerPatch final
		{
		private:
			static void Postfix(PingTracker *__instance);
		};
	public:
		static GenericPopup *popup;

	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MainMenuManager), nameof(MainMenuManager.Start))] public static class LogoPatch
		class LogoPatch final
		{
		public:
			static SpriteRenderer *renderer;
			static Sprite *bannerSprite;
			static Sprite *horseBannerSprite;
		private:
			static System::Collections::IEnumerator *ViewBoosterCoro(MainMenuManager *__instance);
		public:
			static std::wstring SponsersData;
			static std::wstring DevsData;

//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task<HttpStatusCode> FetchBoosters()
			static Task<HttpStatusCode> *FetchBoosters();
			static GameObject *CreditsPopup;
		private:
			static void ViewBoosterPatch(MainMenuManager *__instance);
			static bool Downloaded;
		public:
			static MainMenuManager *instance;
		private:
			static System::Collections::IEnumerator *ShowAnnouncementPopUp(MainMenuManager *__instance);
		public:
			static void Postfix(MainMenuManager *__instance);

		private:
			static System::Collections::IEnumerator *Download();

		public:
			static void loadSprites();

			static void updateSprite();

		private:
			static Task *DownloadTask;
		public:
//C# TO C++ CONVERTER TODO TASK: There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task<bool> DownloadSubmarged()
			static Task<bool> *DownloadSubmarged();
		private:
			static void showPopup(const std::wstring &message);

		public:
			static void setPopupText(const std::wstring &message);
		};
	};
}
