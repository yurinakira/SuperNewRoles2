#include "GameStartPatch.h"
#include "../Main.h"
#include "../Mode/ModeHandler.h"

using namespace HarmonyLib;
using namespace UnityEngine;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Patch
{

	bool GameStartPatch::MakePublicPatch::Prefix()
	{
		bool NameIncludeMod = SaveManager::PlayerName->ToLower().Contains(L"mod");
		bool NameIncludeSNR = SaveManager::PlayerName->ToUpper().Contains(L"SNR");
		bool NameIncludeSHR = SaveManager::PlayerName->ToUpper().Contains(L"SHR");
		if (NameIncludeMod && !NameIncludeSNR)
		{
			SuperNewRolesPlugin::Logger->LogWarning(L"\"mod\"が名前に含まれている状態では公開部屋にすることはできません。");
			return false;
		}
		else if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles, false}) && NameIncludeSNR && !NameIncludeSHR || ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles, false}) && NameIncludeMod && !NameIncludeSHR)
		{
			SuperNewRolesPlugin::Logger->LogWarning(L"SHRモードで\"SNR\"が名前に含まれている状態では公開部屋にすることはできません。");
			return false;
		}
		return true;
	}

	void GameStartPatch::LobbyCountDownTimer::Postfix(GameStartManager *__instance)
	{
		if (Input->GetKeyDown(KeyCode::F8) && GameStartManager::_instance && AmongUsClient::Instance->AmHost)
		{
			GameStartManager::Instance->countDownTimer = 0;
		}
		if (Input->GetKeyDown(KeyCode::F7) && GameStartManager::_instance && AmongUsClient::Instance->AmHost)
		{
			GameStartManager::Instance->ResetStartState();
		}
	}
}
