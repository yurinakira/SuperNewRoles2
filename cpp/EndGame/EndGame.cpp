//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "EndGame.h"
#include "../ModHelpers.h"
#include "../CustomOption/CustomOptionDate.h"
#include "../Roles/RoleClass.h"
#include "../TranslateDate.h"
#include "../Roles/RoleHelper.h"
#include "../Mode/ModeHandler.h"
#include "../Mode/Zombie/main.h"
#include "../Helpers/CachedPlayer.h"
#include "../Main.h"
#include "../OutfitManager.h"
#include "../Mode/SuperHostRoles/SyncSetting.h"
#include "../Patch/TaskCount.h"
#include "../BotManager.h"
#include "../Roles/Demon.h"
#include "../Roles/Arsonist.h"
#include "../Mode/BattleRoyal/main.h"
#include "../Buttons/CustomButton.h"
#include "../AllRoleSetClass.h"
#include "../Patch/DebugMode.h"
#include "../Sabotage/Patch.h"
#include "../Mode/PlusModeHandler.h"
#include "../Roles/EvilEraser.h"
#include "../CustomRPC/CustomRPC.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace SuperNewRoles::Sabotage;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles::EndGame
{

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
	void ShipStatusPatch::Postfix2(ShipStatus *__instance, bool &__result)
	{
		__result = false;
	}

std::vector<PlayerRoleInfo*> AdditionalTempData::playerRoles;
GameOverReason *AdditionalTempData::gameOverReason;
WinCondition AdditionalTempData::winCondition = WinCondition::Default;
std::vector<WinCondition> AdditionalTempData::additionalWinConditions;
std::unordered_map<int, PlayerControl*> AdditionalTempData::plagueDoctorInfected;
std::unordered_map<int, float> AdditionalTempData::plagueDoctorProgress;

	void AdditionalTempData::clear()
	{
		playerRoles.clear();
		additionalWinConditions.clear();
		winCondition = WinCondition::Default;
	}

	std::wstring AdditionalTempData::PlayerRoleInfo::getPlayerName() const
	{
		return PlayerName;
	}

	void AdditionalTempData::PlayerRoleInfo::setPlayerName(const std::wstring &value)
	{
		PlayerName = value;
	}

	std::wstring AdditionalTempData::PlayerRoleInfo::getNameSuffix() const
	{
		return NameSuffix;
	}

	void AdditionalTempData::PlayerRoleInfo::setNameSuffix(const std::wstring &value)
	{
		NameSuffix = value;
	}

	std::vector<Intro::IntroDate*> AdditionalTempData::PlayerRoleInfo::getRoles() const
	{
		return Roles;
	}

	void AdditionalTempData::PlayerRoleInfo::setRoles(const std::vector<Intro::IntroDate*> &value)
	{
		Roles = value;
	}

	std::wstring AdditionalTempData::PlayerRoleInfo::getRoleString() const
	{
		return RoleString;
	}

	void AdditionalTempData::PlayerRoleInfo::setRoleString(const std::wstring &value)
	{
		RoleString = value;
	}

	int AdditionalTempData::PlayerRoleInfo::getTasksCompleted() const
	{
		return TasksCompleted;
	}

	void AdditionalTempData::PlayerRoleInfo::setTasksCompleted(int value)
	{
		TasksCompleted = value;
	}

	int AdditionalTempData::PlayerRoleInfo::getTasksTotal() const
	{
		return TasksTotal;
	}

	void AdditionalTempData::PlayerRoleInfo::setTasksTotal(int value)
	{
		TasksTotal = value;
	}

	int AdditionalTempData::PlayerRoleInfo::getPlayerId() const
	{
		return PlayerId;
	}

	void AdditionalTempData::PlayerRoleInfo::setPlayerId(int value)
	{
		PlayerId = value;
	}

	int AdditionalTempData::PlayerRoleInfo::getColorId() const
	{
		return ColorId;
	}

	void AdditionalTempData::PlayerRoleInfo::setColorId(int value)
	{
		ColorId = value;
	}

	FinalStatus AdditionalTempData::PlayerRoleInfo::getStatus() const
	{
		return Status;
	}

	void AdditionalTempData::PlayerRoleInfo::setStatus(FinalStatus value)
	{
		Status = value;
	}

	Intro::IntroDate *AdditionalTempData::PlayerRoleInfo::getIntroDate() const
	{
		return IntroDate;
	}

	void AdditionalTempData::PlayerRoleInfo::setIntroDate(Intro::IntroDate *value)
	{
		IntroDate = value;
	}

	Intro::IntroDate *AdditionalTempData::PlayerRoleInfo::getGhostIntroDate() const
	{
		return GhostIntroDate;
	}

	void AdditionalTempData::PlayerRoleInfo::setGhostIntroDate(Intro::IntroDate *value)
	{
		GhostIntroDate = value;
	}

bool EndGameManagerSetUpPatch::IsHaison = false;
TMPro::TMP_Text *EndGameManagerSetUpPatch::textRenderer;

	void EndGameManagerSetUpPatch::ShowProgressionPatch::Prefix()
	{
		if (textRenderer != nullptr)
		{
			textRenderer->gameObject.SetActive(false);
		}
	}

	void EndGameManagerSetUpPatch::Postfix(EndGameManager *__instance)
	{

		for (PoolablePlayer *pb : *__instance->transform.GetComponentsInChildren<PoolablePlayer*>())
		{
			UnityEngine::Object::Destroy(pb->gameObject);
		}
		int num = Mathf::CeilToInt(7.5f);
		std::vector<WinningPlayerData*> list = TempData::winners::GetFastEnumerator()->ToArray()->ToList()->OrderBy([&] (WinningPlayerData *b)
		{
			if (!b->IsYou)
			{
				return 0;
			}
			return -1;
		})->ToList<WinningPlayerData*>();

		for (int i = 0; i < list.size(); i++)
		{
			WinningPlayerData *winningPlayerData2 = list[i];
			int num2 = (i % 2 == 0) ? -1 : 1;
			int num3 = (i + 1) / 2;
			float num4 = static_cast<float>(num3) / static_cast<float>(num);
			float num5 = Mathf::Lerp(1.0f, 0.75f, num4);
			float num6 = static_cast<float>((i == 0) ? -8 : -1);
			PoolablePlayer *poolablePlayer = UnityEngine::Object::Instantiate<PoolablePlayer*>(__instance->PlayerPrefab, __instance->transform);

			poolablePlayer->transform->localPosition = new Vector3(1.0f * static_cast<float>(num2) * static_cast<float>(num3) * num5, FloatRange::SpreadToEdges(-1.125f, 0.0f, num3, num), num6 + static_cast<float>(num3) * 0.01f) * 0.9f;

			float num7 = Mathf::Lerp(1.0f, 0.65f, num4) * 0.9f;
			Vector3 *vector = new Vector3(num7, num7, 1.0f);
			poolablePlayer->transform->localScale = vector;
			poolablePlayer->UpdateFromPlayerOutfit(static_cast<GameData::PlayerOutfit*>(winningPlayerData2), PlayerMaterial::MaskType::ComplexUI, winningPlayerData2->IsDead, true);
			if (winningPlayerData2->IsDead)
			{
				poolablePlayer->cosmetics.currentBodySprite.BodySprite->sprite = poolablePlayer->cosmetics.currentBodySprite.GhostSprite;
				poolablePlayer->SetDeadFlipX(i % 2 == 0);
			}

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
