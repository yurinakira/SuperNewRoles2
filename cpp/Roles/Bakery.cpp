#include "Bakery.h"
#include "RoleClass.h"
#include "../Mode/ModeHandler.h"
#include "../Mode/SuperHostRoles/main.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleHelper.h"
#include "../TranslateDate.h"
#include "../Main.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{

TMPro::TextMeshPro *Bakery::breadText;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(ExileController __instance, [HarmonyArgument(0)] GameData.PlayerInfo exiled, [HarmonyArgument(1)] bool tie)
	bool Bakery::Prefix(ExileController *__instance, GameData::PlayerInfo *exiled, bool tie)
	{
		if (RoleClass::Assassin::TriggerPlayer == nullptr)
		{
			return true;
		}

		if (__instance->specialInputHandler != nullptr)
		{
			__instance->specialInputHandler->disableVirtualCursor = true;
		}
		ExileController->Instance = __instance;
		ControllerManager::Instance->CloseAndResetAll();

		__instance->Text.gameObject.SetActive(false);
		__instance->Text.text = L"";

		PlayerControl *player = RoleClass::Assassin::TriggerPlayer;

		std::wstring printStr;

		auto exile = ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}) ? Mode::SuperHostRoles::main::RealExiled : exiled->Object;
		if (exile != nullptr && SuperNewRoles::RoleHelpers::isRole(exile, CustomRPC::RoleId::Marine))
		{
			printStr = player->Data->PlayerName + ModTranslation::getString(L"AssassinSucsess");
			RoleClass::Assassin::IsImpostorWin = true;
		}
		else
		{
			printStr = player->Data->PlayerName + ModTranslation::getString(L"AssassinFail");
			RoleClass::Assassin::DeadPlayer = RoleClass::Assassin::TriggerPlayer;
		}
		RoleClass::Assassin::TriggerPlayer = nullptr;
		__instance->exiled = nullptr;
		__instance->Player->gameObject.SetActive(false);
		__instance->completeString = printStr;
		__instance->ImpostorText->text = L"";
		__instance->StartCoroutine(__instance->Animate());
		return false;
	}

	bool Bakery::BakeryAlive()
	{
		for (auto p : RoleClass::Bakery::BakeryPlayer)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p))
			{
				SuperNewRolesPlugin::Logger->LogInfo(L"パン屋が生きていると判定されました");
				return true;
			}
		}
		SuperNewRolesPlugin::Logger->LogInfo(L"パン屋が生きていないと判定されました");
		return false;
	}

	std::wstring Bakery::GetExileText()
	{
		//翻訳
		auto rand = new System::Random();
		if (rand->Next(1, 10) == 1)
		{
			delete rand;
			return ModTranslation::getString(L"BakeryExileText2");
		}
		else
		{
			delete rand;
			return ModTranslation::getString(L"BakeryExileText");
		}

		delete rand;
	}

	void Bakery::Postfix(ExileController *__instance)
	{
		breadText = UnityEngine::Object::Instantiate(__instance->ImpostorText, __instance->Text.transform);
		breadText->text = GetExileText(); //文字の内容を変える
		bool isBakeryAlive = BakeryAlive(); //Boolの取得(生存判定)
		if (isBakeryAlive) //if文(Bakeryが生きていたら実行)
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"パン屋がパンを焼きました"); //ログ
			if (PlayerControl::GameOptions::ConfirmImpostor)
			{
				breadText->transform.localPosition += new UnityEngine::Vector3(0.0f, -0.4f, 0.0f); //位置がエ
			}
			else
			{
				breadText->transform.localPosition += new UnityEngine::Vector3(0.0f, -0.2f, 0.0f);
			}
			breadText->gameObject.SetActive(true); //文字の表示
		}
	}

	void Bakery::BakeryChatDisable::Postfix(ExileController *__instance)
	{
		breadText->gameObject.SetActive(false);
	}
}
