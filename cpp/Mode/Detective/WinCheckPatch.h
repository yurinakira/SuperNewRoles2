#pragma once

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace SuperNewRoles::Mode::Detective { class PlayerStatistics; }

using namespace SuperNewRoles::EndGame;

namespace SuperNewRoles::Mode::Detective
{
	class WinCheckPatch
	{
	public:
		static bool CheckEndGame(ShipStatus *__instance);
		static void CustomEndGame(ShipStatus *__instance, GameOverReason *reason, bool showAd);
		static bool CheckAndEndGameForSabotageWin(ShipStatus *__instance);
		static bool CheckAndEndGameForDisconnectWin(ShipStatus *__instance);
		static bool CheckAndEndGameForTaskWin(ShipStatus *__instance);

		static bool CheckAndEndGameForImpostorWin(ShipStatus *__instance, PlayerStatistics *statistics);

		static bool CheckAndEndGameForCrewmateWin(ShipStatus *__instance, PlayerStatistics *statistics);
		static void EndGameForSabotage(ShipStatus *__instance);

	public:
		class PlayerStatistics
		{
		private:
			int TeamImpostorsAlive = 0;
			int CrewAlive = 0;
			int TotalAlive = 0;

		public:
			int getTeamImpostorsAlive() const;
			void setTeamImpostorsAlive(int value);
			int getCrewAlive() const;
			void setCrewAlive(int value);
			int getTotalAlive() const;
			void setTotalAlive(int value);
			PlayerStatistics(ShipStatus *__instance);
		private:
			void GetPlayerCounts();
		};
	};
}
