#pragma once

#include "../CustomRPC/CustomRPC.h"
#include "../Intro/IntroDate.h"
#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{
	class HandleGhostRole
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(RoleManager), nameof(RoleManager.TryAssignRoleOnDeath))] class AssignRole
		class AssignRole
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(RoleManager __instance, [HarmonyArgument(0)] PlayerControl player)
			static bool Prefix(RoleManager *__instance, PlayerControl *player);
		};
	public:
		static bool HandleAssign(PlayerControl *player);

		//アサインする役職を決める
		static RoleId Assing(std::vector<IntroDate*> &datas);
	};
}
