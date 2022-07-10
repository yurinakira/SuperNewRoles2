#pragma once

#include <vector>
#include <functional>

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Seer
	{
	//&MadSeer & EvilSeer & SeerFriends & JackalSeer & Sidekick(Seer)
	private:
		static Sprite *SoulSprite;
	public:
		static Sprite *getSoulSprite();

	public:
		class ExileControllerWrapUpPatch final
		{
		public:
			static void WrapUpPostfix(GameData::PlayerInfo *exiled);

		public:
			class MurderPlayerPatch final
			{
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target)
				static void Postfix(PlayerControl *__instance, PlayerControl *target);
			};
		};
	};
}
