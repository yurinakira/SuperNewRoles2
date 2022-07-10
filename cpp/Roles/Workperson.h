#pragma once

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;

namespace SuperNewRoles::Roles
{
	class Workperson
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(IntroCutscene), nameof(IntroCutscene.BeginCrewmate))] class BeginCrewmatePatch
		class BeginCrewmatePatch
		{
		public:
			static void Postfix(ShipStatus *__instance);
		};
	};
}
