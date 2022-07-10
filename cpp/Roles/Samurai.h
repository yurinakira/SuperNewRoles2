#pragma once

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Samurai
	{
	public:
		class MurderPatch
		{
		public:
			static void Postfix(PlayerControl *__instance);
		};
	public:
		static void SetSamuraiButton();
	public:
		class FixedUpdate
		{
		public:
			static void Postfix();
		};
		//自爆魔関連
	public:
		static void EndMeeting();
		static void ResetCoolDown();
		static bool isSamurai(PlayerControl *Player);
		static void SamuraiKill();
		static bool Getsword(PlayerControl *source, PlayerControl *player);
		static void IsSword();
	};
}
