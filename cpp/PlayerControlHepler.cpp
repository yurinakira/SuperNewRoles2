#include "PlayerControlHepler.h"
#include "ModHelpers.h"
#include "Intro/IntroDate.h"
#include "Roles/RoleHelper.h"
#include "TranslateDate.h"
#include "CustomOption/CustomOptionDate.h"
#include "Roles/RoleClass.h"
#include "CustomRPC/CustomRPC.h"

using namespace InnerNet;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles
{

	bool PlayerControlHepler::IsMod(PlayerControl *player)
	{
		if (player == nullptr)
		{
			return false;
		}
		return IsMod(SuperNewRoles::ModHelpers::getClientId(player));
	}

	bool PlayerControlHepler::IsMod(ClientData *player)
	{
		if (player == nullptr)
		{
			return false;
		}
		return IsMod(player->Id);
	}

	bool PlayerControlHepler::IsMod(int player)
	{
		if (player == AmongUsClient::Instance->HostId && AmongUsClient::Instance->AmHost)
		{
			return true;
		}
		return SuperNewRoles::Patch::ShareGameVersion::GameStartManagerUpdatePatch::VersionPlayers.find(player) != SuperNewRoles::Patch::ShareGameVersion::GameStartManagerUpdatePatch::VersionPlayers.end();
	}

	void PlayerControlHepler::clearAllTasks(PlayerControl *player)
	{
		if (player == nullptr)
		{
			return;
		}
		for (int i = 0; i < player->myTasks->Count; i++)
		{
			PlayerTask *playerTask = player->myTasks[i];
			playerTask->OnRemove();
			UnityEngine::Object::Destroy(playerTask->gameObject);
		}
		player->myTasks->Clear();

		if (player->Data != nullptr && player->Data->Tasks != nullptr)
		{
			player->Data->Tasks->Clear();
		}
	}

	void PlayerControlHepler::refreshRoleDescription(PlayerControl *player)
	{
		if (player == nullptr)
		{
			return;
		}

		std::vector<Intro::IntroDate*> infos = {Intro::IntroDate::GetIntroDate(SuperNewRoles::RoleHelpers::getRole(player), player)};

		auto toRemove = std::vector<PlayerTask*>();
		auto aaa = false;
		auto mytxt = L"";
		for (PlayerTask *t : *player->myTasks)
		{
			auto textTask = t->gameObject.GetComponent<ImportantTextTask*>();
			if (textTask != nullptr)
			{
				if (aaa == false)
				{
					mytxt = textTask->Text;
				}
				auto info = infos.FirstOrDefault([&] (std::any x)
				{
					return textTask->Text.StartsWith(ModTranslation::getString(x::NameKey + L"Name"));
				});
				if (info != nullptr)
				{
					infos.Remove(info); // TextTask for this RoleInfo does not have to be added, as it already exists
				}
				else
				{
					toRemove.push_back(t); // TextTask does not have a corresponding RoleInfo and will hence be deleted
				}
			}
		}

		for (auto t : toRemove)
		{
			t->OnRemove();
			player->myTasks->Remove(t);
			UnityEngine::Object::Destroy(t->gameObject);
		}

		// Add TextTask for remaining RoleInfos
		for (auto roleInfo : infos)
		{
			GameObject tempVar(L"RoleTask");
			auto task = (&tempVar)->AddComponent<ImportantTextTask*>();
			task->transform.SetParent(player->transform, false);

			task->Text = CustomOption::CustomOptions::cs(roleInfo->color, StringHelper::formatSimple(L"{0}: {1}", ModTranslation::getString(roleInfo->NameKey + L"Name"), roleInfo->TitleDesc));
			if (SuperNewRoles::RoleHelpers::IsLovers(player))
			{
				task->Text += L"\n" + ModHelpers::cs(RoleClass::Lovers::color, ModTranslation::getString(L"LoversName") + L": " + std::wstring::Format(ModTranslation::getString(L"LoversIntro"), PlayerControl::LocalPlayer::GetOneSideLovers() == nullptr ? std::any() : (((PlayerControl::LocalPlayer::GetOneSideLovers()->Data == nullptr ? nullptr : PlayerControl::LocalPlayer::GetOneSideLovers().Data->PlayerName) != nullptr) ? (PlayerControl::LocalPlayer::GetOneSideLovers()->Data == nullptr ? nullptr : PlayerControl::LocalPlayer::GetOneSideLovers().Data->PlayerName) : L"")));
			}
			if (!SuperNewRoles::RoleHelpers::isGhostRole(player, RoleId::DefaultRole))
			{
				auto GhostRoleInfo = IntroDate::GetIntroDate(SuperNewRoles::RoleHelpers::getGhostRole(player), player);
				task->Text += L"\n" + CustomOption::CustomOptions::cs(GhostRoleInfo->color, StringHelper::formatSimple(L"{0}: {1}", ModTranslation::getString(GhostRoleInfo->NameKey + L"Name"), GhostRoleInfo->TitleDesc));
			}
			/**
			if (player.IsQuarreled())
			{
			    task.Text += "\n" + ModHelpers.cs(RoleClass.Quarreled.color, String.Format(ModTranslation.getString("QuarreledIntro"), SetNamesClass.AllNames[PlayerControl.LocalPlayer.GetOneSideQuarreled().PlayerId]));
			}
			**/

			player->myTasks->Insert(0, task);
		}
	}
}
