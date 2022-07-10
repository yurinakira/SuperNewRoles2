//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "main.h"
#include "../../Helpers/CachedPlayer.h"
#include "../SuperHostRoles/FixedUpdate.h"
#include "../../TranslateDate.h"
#include "../../LateTask.h"
#include "../../ModHelpers.h"
#include "../SuperHostRoles/Chat.h"
#include "../../Intro/IntroDate.h"
#include "../../Roles/RoleHelper.h"
#include "../../Roles/RoleClass.h"

using namespace Hazel;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::Werewolf
{

bool main::IsDiscussion = false;
bool main::IsFirst = false;
int main::AbilityTime = 0;
int main::DiscussionTime = 0;
std::unordered_map<int, int> main::SoothRoles;
std::vector<int> main::HunterKillPlayers;
std::vector<int> main::WolfKillPlayers;
std::vector<PlayerControl*> main::HunterPlayers;
PlayerControl *main::HunterExilePlayer;
int main::Time = 0;

	bool main::isAbility()
	{
		return !IsDiscussion;
	}

	void main::setAbility(bool value)
	{
		IsDiscussion = !value;
	}

	void main::ClearAndReload()
	{
		PlayerControl::GameOptions->KillCooldown = -1;
		PlayerControl::GameOptions->DiscussionTime = 0;
		CachedPlayer::LocalPlayer->PlayerControl->RpcSyncSettings(PlayerControl::GameOptions);
		for (auto p : CachedPlayer::AllPlayers)
		{
			SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(p);
		}
		IsDiscussion = true;
		IsFirst = true;
		DiscussionTime = 30;
		AbilityTime = 10;
		SoothRoles = std::unordered_map<int, int>();
		HunterKillPlayers = std::vector<int>();
		WolfKillPlayers = std::vector<int>();
		HunterPlayers = std::vector<PlayerControl*>();
		HunterExilePlayer = nullptr;
	}

	void main::IntroHandler()
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		PlayerControl::LocalPlayer::RpcSendChat(ModTranslation::getString(L"WereWolfMeetingNormal"));
		new LateTask([&] ()
		{
			IsDiscussion = true;
			PlayerControl::GameOptions->VotingTime = DiscussionTime;
			CachedPlayer::LocalPlayer->PlayerControl->RpcSyncSettings(PlayerControl::GameOptions);
			MeetingRoomManager::Instance->AssignSelf(PlayerControl::LocalPlayer, CachedPlayer::LocalPlayer->Data);
			FastDestroyableSingleton<HudManager*>::getInstance().OpenMeetingRoom(PlayerControl::LocalPlayer);
			PlayerControl::LocalPlayer::RpcStartMeeting(CachedPlayer::LocalPlayer->Data);
		}, 20, L"DiscussionStartMeeting");
	}

	void main::Wrapup(GameData::PlayerInfo *exiled)
	{
		IsDiscussion = !IsDiscussion;
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (isAbility())
		{
			PlayerControl::GameOptions->VotingTime = AbilityTime;
			PlayerControl::LocalPlayer::RpcSendChat(ModTranslation::getString(L"WereWolfMeetingAbility"));
			HunterExilePlayer = nullptr;
			SoothRoles = std::unordered_map<int, int>();
			HunterKillPlayers = std::vector<int>();
			WolfKillPlayers = std::vector<int>();
		}
		else
		{
			PlayerControl::GameOptions->VotingTime = DiscussionTime;
			PlayerControl::LocalPlayer::RpcSendChat(ModTranslation::getString(L"WereWolfMeetingNormal"));
			if (HunterExilePlayer != nullptr)
			{
				HunterExilePlayer->RpcMurderPlayer(HunterExilePlayer);
			}
			for (auto playerid : WolfKillPlayers)
			{
				PlayerControl *player = ModHelpers::playerById(static_cast<unsigned char>(playerid));
				if (player != nullptr)
				{
					player->RpcMurderPlayer(player);
				}
			}
		}
		if (IsDiscussion)
		{
			Time = 3;
			for (auto players : SoothRoles)
			{
				PlayerControl *source = ModHelpers::playerById(static_cast<unsigned char>(players.Key));
				PlayerControl *target = ModHelpers::playerById(static_cast<unsigned char>(players.Value));
				if (source == nullptr || target == nullptr || source->Data->Disconnected)
				{
					break;
				}
				std::wstring Chat = L"";
				auto RoleDate = IntroDate::GetIntroDate(SuperNewRoles::RoleHelpers::getRole(target), target);
				auto RoleName = ModTranslation::getString(L"Werewolf" + RoleDate->NameKey + L"Name");
				Chat += std::wstring::Format(ModTranslation::getString(L"WereWolfMediumAbilityText"), SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(target), RoleName);
				new LateTask([&] ()
				{
					SuperNewRoles::Helpers::RPCHelper::RPCSendChatPrivate(source, Chat);
				}, Time, L"AbilityChatSend");
				Time += 3;
			}
			if (exiled != nullptr)
			{
				for (auto player : RoleClass::SpiritMedium::SpiritMediumPlayer)
				{
					std::wstring Chat = L"";
					PlayerControl *target = exiled->Object;
					auto RoleDate = IntroDate::GetIntroDate(SuperNewRoles::RoleHelpers::getRole(target), target);
					auto RoleName = ModTranslation::getString(L"Werewolf" + RoleDate->NameKey + L"Name");
					Chat += std::wstring::Format(ModTranslation::getString(L"WereWolfMediumAbilityText"), SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(target), RoleName);
					new LateTask([&] ()
					{
						SuperNewRoles::Helpers::RPCHelper::RPCSendChatPrivate(player, Chat);
					}, Time, L"AbilityChatSend");
					Time += 3;
				}
			}
			for (auto players : HunterKillPlayers)
			{
				auto player = ModHelpers::playerById(static_cast<unsigned char>(players));
				player->RpcMurderPlayer(player);
			}
			if (Time <= 9)
			{
				Time += 7;
			}
			new LateTask([&] ()
			{
				GameData::PlayerInfo *target;

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
