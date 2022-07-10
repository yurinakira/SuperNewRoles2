//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "SetNames.h"
#include "../BotManager.h"
#include "../ModHelpers.h"
#include "../Helpers/CachedPlayer.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Roles/RoleHelper.h"
#include "../Roles/RoleClass.h"
#include "TaskCount.h"
#include "../CustomOption/CustomOptionDate.h"
#include "../Intro/IntroDate.h"
#include "../Roles/Demon.h"
#include "../Roles/Arsonist.h"
#include "../Roles/Madmate.h"
#include "../Roles/JackalFriends.h"
#include "../Mode/ModeHandler.h"
#include "../Sabotage/SabotageManager.h"
#include "../Sabotage/CognitiveDeficit/main.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Roles;
using namespace TMPro;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

std::unordered_map<int, std::wstring> SetNamesClass::AllNames;

	void SetNamesClass::SetPlayerNameColor(PlayerControl *p, Color *color)
	{
		if (SuperNewRoles::BotManager::IsBot(p))
		{
			return;
		}
		SuperNewRoles::ModHelpers::nameText(p)->color = color;
		if (MeetingHud::Instance)
		{
			for (PlayerVoteArea *player : MeetingHud::Instance->playerStates)
			{
				if (p->PlayerId == player->TargetPlayerId)
				{
					player->NameText->color = color;
				}
			}
		}
	}

	void SetNamesClass::SetPlayerNameText(PlayerControl *p, const std::wstring &text)
	{
		if (SuperNewRoles::BotManager::IsBot(p))
		{
			return;
		}
		SuperNewRoles::ModHelpers::nameText(p)->text = text;
		if (MeetingHud::Instance)
		{
			for (PlayerVoteArea *player : MeetingHud::Instance->playerStates)
			{
				if (player->TargetPlayerId == p->PlayerId)
				{
					player->NameText->text = text;
					return;
				}
			}
		}
	}

	void SetNamesClass::resetNameTagsAndColors()
	{
		std::unordered_map<unsigned char, PlayerControl*> playersById = ModHelpers::allPlayersById();

		for (auto pro : PlayerInfos)
		{
			pro->Value->text = L"";
		}
		for (auto pro : MeetingPlayerInfos)
		{
			pro->Value->text = L"";
		}
		for (auto player : CachedPlayer::AllPlayers)
		{
			bool hidename = ModHelpers::hidePlayerName(PlayerControl::LocalPlayer, player);
			SuperNewRoles::ModHelpers::nameText(player)->text = hidename ? L"" : player->CurrentOutfit.PlayerName;
			if (PlayerControl::LocalPlayer::isImpostor() && (SuperNewRoles::RoleHelpers::isImpostor(player) || SuperNewRoles::RoleHelpers::isRole(player, RoleId::Spy)))
			{
				SetPlayerNameColor(player, RoleClass::ImpostorRed);
			}
			else
			{
				SetPlayerNameColor(player, Color::white);
			}
		}
	}

std::unordered_map<unsigned char, TextMeshPro*> SetNamesClass::PlayerInfos;
std::unordered_map<unsigned char, TextMeshPro*> SetNamesClass::MeetingPlayerInfos;

	void SetNamesClass::SetPlayerRoleInfoView(PlayerControl *p, Color *roleColors, const std::wstring &roleNames, std::optional<Color*> &GhostRoleColor, const std::wstring &GhostRoleNames)
	{
		if (SuperNewRoles::BotManager::IsBot(p))
		{
			return;
		}
		bool commsActive = RoleHelpers::IsComms();
		TMPro::TextMeshPro *playerInfo = PlayerInfos.find(p->PlayerId) != PlayerInfos.end() ? PlayerInfos[p->PlayerId] : nullptr;
		if (playerInfo == nullptr)
		{
			playerInfo = UnityEngine::Object::Instantiate(SuperNewRoles::ModHelpers::nameText(p), SuperNewRoles::ModHelpers::nameText(p)->transform.parent);
			playerInfo->fontSize *= 0.75f;
			playerInfo->gameObject->name = L"Info";
			PlayerInfos[p->PlayerId] = playerInfo;
		}

		// Set the position every time bc it sometimes ends up in the wrong place due to camoflauge
		playerInfo->transform->localPosition = SuperNewRoles::ModHelpers::nameText(p)->transform.localPosition + Vector3::up * 0.5f;

		PlayerVoteArea *playerVoteArea = MeetingHud->Instance == nullptr ? nullptr : (MeetingHud::Instance->playerStates == nullptr ? nullptr : MeetingHud::Instance->playerStates.FirstOrDefault([&] (std::any x)
		{
			return x->TargetPlayerId == p->PlayerId;
		}));
		TMPro::TextMeshPro *meetingInfo = MeetingPlayerInfos.find(p->PlayerId) != MeetingPlayerInfos.end() ? MeetingPlayerInfos[p->PlayerId] : nullptr;
		if (meetingInfo == nullptr && playerVoteArea != nullptr)
		{
			meetingInfo = UnityEngine::Object::Instantiate(playerVoteArea->NameText, playerVoteArea->NameText.transform.parent);
			meetingInfo->transform.localPosition += Vector3::down * 0.1f;
			meetingInfo->fontSize = 1.5f;
			meetingInfo->gameObject->name = L"Info";
			MeetingPlayerInfos[p->PlayerId] = meetingInfo;
		}

		// Set player name higher to align in middle
		if (meetingInfo != nullptr && playerVoteArea != nullptr)
		{
			auto playerName = playerVoteArea->NameText;
			playerName->transform->localPosition = new Vector3(0.3384f, 0.0311f + 0.0683f, -0.1f);
		}
		std::wstring TaskText = L"";
		try
		{
			if (!SuperNewRoles::RoleHelpers::isClearTask(p))
			{
				if (commsActive)
				{
					auto all = std::get<1>(TaskCount::TaskDateNoClearCheck(p->Data));
					TaskText += ModHelpers::cs(Color::yellow, L"(?/" + all + L")");
				}
				else
				{
//C# TO C++ CONVERTER NOTE: The following 'decomposition declaration' requires C++17:
//ORIGINAL LINE: var(complate, all) = TaskCount.TaskDateNoClearCheck(p.Data);
					auto [complate, all] = TaskCount::TaskDateNoClearCheck(p->Data);
					TaskText += ModHelpers::cs(Color::yellow, L"(" + complate + L"/" + all + L")");
				}
			}
		}
		catch (...)
		{
		}
		std::wstring playerInfoText = L"";
		std::wstring meetingInfoText = L"";
		playerInfoText = StringHelper::formatSimple(L"{0}", CustomOptions::cs(roleColors, roleNames));
		if (GhostRoleNames != L"")
		{
			playerInfoText = StringHelper::formatSimple(L"{0}({1})", CustomOptions::cs(static_cast<Color*>(GhostRoleColor), GhostRoleNames), playerInfoText);
		}
		playerInfoText += TaskText;
		meetingInfoText = StringHelper::trim(playerInfoText);
		playerInfo->text = playerInfoText;
		playerInfo->gameObject.SetActive(p->Visible);
		if (meetingInfo != nullptr)
		{
			meetingInfo->text = MeetingHud::Instance->state == MeetingHud::VoteStates::Results ? L"" : meetingInfoText;
		}
		SuperNewRoles::ModHelpers::nameText(p)->color = roleColors;
	}

	void SetNamesClass::SetPlayerRoleInfo(PlayerControl *p)
	{
		if (SuperNewRoles::BotManager::IsBot(p))
		{
			return;
		}
		std::wstring roleNames;
		Color *roleColors;
		std::wstring GhostroleNames = L"";
		std::optional<Color*> GhostroleColors;
		auto role = SuperNewRoles::RoleHelpers::getRole(p);
		if (role == RoleId::DefaultRole || (role == RoleId::Bestfalsecharge && SuperNewRoles::RoleHelpers::isAlive(p)))
		{
			if (SuperNewRoles::RoleHelpers::isImpostor(p))
			{
				roleNames = L"ImpostorName";
				roleColors = RoleClass::ImpostorRed;
			}

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
