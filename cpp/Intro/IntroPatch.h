#pragma once

#include <string>
#include <vector>
#include <any>

using namespace HarmonyLib;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::HideAndSeek;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace TMPro;
using namespace UnityEngine;

namespace SuperNewRoles::Patches
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch] class IntroPatch
	class IntroPatch
	{
	public:
		static void setupIntroTeamIcons(IntroCutscene *__instance, Il2CppSystem::Collections::Generic::List<PlayerControl*> *&yourTeam);

		static void setupIntroTeam(IntroCutscene *__instance, Il2CppSystem::Collections::Generic::List<PlayerControl*> *&yourTeam);

	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(IntroCutscene), nameof(IntroCutscene.OnDestroy))] class IntroCutsceneDestroyPatch
		class IntroCutsceneDestroyPatch
		{
		public:
			static void Prefix(IntroCutscene *__instance);
		};

	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(IntroCutscene), nameof(IntroCutscene.ShowRole))] class SetUpRoleTextPatch
		class SetUpRoleTextPatch
		{
		private:
			static unsigned char ToByteIntro(float f);
		public:
			static void Prefix(IntroCutscene *__instance);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(IntroCutscene), nameof(IntroCutscene.BeginCrewmate))] class BeginCrewmatePatch
		class BeginCrewmatePatch
		{
		public:
			static void Prefix(IntroCutscene *__instance, Il2CppSystem::Collections::Generic::List<PlayerControl*> *&teamToDisplay);

			static void Postfix(IntroCutscene *__instance, Il2CppSystem::Collections::Generic::List<PlayerControl*> *&teamToDisplay);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(IntroCutscene), nameof(IntroCutscene.BeginImpostor))] class BeginImpostorPatch
		class BeginImpostorPatch
		{
		public:
			static void Prefix(IntroCutscene *__instance, Il2CppSystem::Collections::Generic::List<PlayerControl*> *&yourTeam);

			static void Postfix(IntroCutscene *__instance, Il2CppSystem::Collections::Generic::List<PlayerControl*> *&yourTeam);
		};

	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(Constants), nameof(Constants.ShouldHorseAround))] public static class ShouldAlwaysHorseAround
		class ShouldAlwaysHorseAround final
		{
		public:
			static bool isHorseMode;
			static bool Prefix(bool &__result);
		};
	};
}
