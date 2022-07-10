#pragma once

using namespace Hazel;
using namespace SuperNewRoles::Helpers;

namespace SuperNewRoles::Roles
{
	class EvilEraser final
	{
	public:
		enum class BlockTypes
		{
			StuntmanGuard,
			MadStuntmanGuard,
			ClergymanLightOut,
			BaitReport,
			RedRidingHoodRevive,
			JackalSidekick,
			JackalSeerSidekick,
			NekomataExiled,
			FoxGuard
		};
	public:
		static bool IsBlock(BlockTypes blocktype, PlayerControl *player = nullptr);
		static bool IsBlockAndTryUse(BlockTypes blocktype, PlayerControl *player = nullptr);
		static void UseCount(PlayerControl *player);
		static bool IsOKAndTryUse(BlockTypes blocktype, PlayerControl *player = nullptr);
		static bool IsWinGodGuard;
		static bool IsGodWinGuard();

		static bool IsWinFoxGuard;
		static bool IsFoxWinGuard();
				static bool IsWinNeetGuard;
		static bool IsNeetWinGuard();
		static PlayerControl *GetOnCount();
	};
}
