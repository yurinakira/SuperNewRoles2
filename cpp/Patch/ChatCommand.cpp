#include "ChatCommand.h"
#include "../ModHelpers.h"
#include "../Helpers/CachedPlayer.h"
#include "../Helpers/FastDestroyableSingleton.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;

namespace SuperNewRoles::Patch
{

int DynamicLobbies::LobbyLimit = 15;

	bool DynamicLobbies::SendChatPatch::Prefix(ChatController *__instance)
	{
		std::wstring text = __instance->TextArea.text;
		bool handled = false;
		if (AmongUsClient::Instance->GameState != InnerNetClient::GameStates::Started)
		{
			if (StringHelper::startsWith(StringHelper::toLower(text), L"/mp "))
			{ // Unfortunately server holds this - need to do more trickery
				if (AmongUsClient::Instance->AmHost && AmongUsClient::Instance->CanBan())
				{
					handled = true;
					if (!int::TryParse(text[4..], LobbyLimit))
					{
						__instance->AddChat(PlayerControl::LocalPlayer, L"使い方\n/mp {最大人数}");
					}
					else
					{
						if (!ModHelpers::isCustomServer())
						{
							LobbyLimit = Math::Clamp(LobbyLimit, 4, 15);
						}
						if (LobbyLimit != PlayerControl::GameOptions::MaxPlayers)
						{
							PlayerControl::GameOptions->MaxPlayers = LobbyLimit;
							DestroyableSingleton<GameStartManager*>::Instance->LastPlayerCount = LobbyLimit;
							CachedPlayer::LocalPlayer->PlayerControl->RpcSyncSettings(PlayerControl::GameOptions);
							__instance->AddChat(PlayerControl::LocalPlayer, StringHelper::formatSimple(L"ロビーの最大人数を{0}人に変更しました！", LobbyLimit));
						}
						else
						{
							__instance->AddChat(PlayerControl::LocalPlayer, StringHelper::formatSimple(L"プレイヤー最小人数は {0}です。", LobbyLimit));
						}
					}
				}
			}
			else if (StringHelper::startsWith(StringHelper::toLower(text), L"/kc "))
			{ // Unfortunately server holds this - need to do more trickery
				if (AmongUsClient::Instance->AmHost && AmongUsClient::Instance->CanBan())
				{
					handled = true;
					float cooltime;
					if (!float::TryParse(text[4..], cooltime))
					{
						__instance->AddChat(PlayerControl::LocalPlayer, L"使い方\n/kc {キルクールタイム}");
					}
					auto settime = cooltime;
					if (settime == 0)
					{
						settime = 0.00001f;
					}
					PlayerControl::GameOptions->KillCooldown = settime;
					CachedPlayer::LocalPlayer->PlayerControl->RpcSyncSettings(PlayerControl::GameOptions);
					__instance->AddChat(PlayerControl::LocalPlayer, StringHelper::formatSimple(L"キルクールタイムを{0}秒に変更しました！", cooltime));
				}
			}
			else if (StringHelper::startsWith(StringHelper::toLower(text), L"/rename "))
			{
				handled = true;
				PlayerControl::LocalPlayer::RpcSetName(StringHelper::replace(StringHelper::toLower(text), L"/rename ", L""));
			}

			if (AmongUsClient::Instance->GameMode == GameModes::FreePlay)
			{
				if (StringHelper::toLower(text) == L"/murder")
				{
					PlayerControl::LocalPlayer::Exiled();
					FastDestroyableSingleton<HudManager*>::getInstance().KillOverlay::ShowKillAnimation(CachedPlayer::LocalPlayer->Data, CachedPlayer::LocalPlayer->Data);
					handled = true;
				}
				else if (StringHelper::startsWith(StringHelper::toLower(text), L"/color "))
				{
					handled = true;
					int col;
					if (!int::TryParse(text[7..], col))
					{
						__instance->AddChat(PlayerControl::LocalPlayer, L"Unable to parse color id\nUsage: /color {id}");
					}
					col = Math::Clamp(col, 0, Palette->PlayerColors->Length - 1);
					PlayerControl::LocalPlayer::SetColor(col);
					__instance->AddChat(PlayerControl::LocalPlayer, L"Changed color succesfully");
					;
				}
				else if (StringHelper::startsWith(StringHelper::toLower(text), L"/name "))
				{
					handled = true;
					std::wstring col = text[6..];
					PlayerControl::LocalPlayer::SetName(col);
					__instance->AddChat(PlayerControl::LocalPlayer, L"Changed name succesfully");
					;
				}
			}
			if (handled)
			{
				__instance->TextArea->Clear();
				FastDestroyableSingleton<HudManager*>::getInstance().Chat->TimeSinceLastMessage = 0.0f;
				__instance->quickChatMenu.ResetGlyphs();
			}
		}
		return !handled;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix(InnerNet.InnerNetClient __instance, [HarmonyArgument(0)] GameOptionsData settings)
	void DynamicLobbies::SendChatPatch::InnerNetClientHostPatch::Prefix(InnerNet::InnerNetClient *__instance, GameOptionsData *settings)
	{
		LobbyLimit = settings->MaxPlayers;
		settings->MaxPlayers = 15; // Force 15 Player Lobby on Server
		SaveManager->ChatModeType = InnerNet::QuickChatModes::FreeChatOrQuickChat;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(InnerNet.InnerNetClient __instance, [HarmonyArgument(0)] GameOptionsData settings)
	void DynamicLobbies::SendChatPatch::InnerNetClientHostPatch::Postfix(InnerNet::InnerNetClient *__instance, GameOptionsData *settings)
	{
		settings->MaxPlayers = LobbyLimit;
	}

	void DynamicLobbies::SendChatPatch::InnerNetClientJoinPatch::Prefix(InnerNet::InnerNetClient *__instance)
	{
		SaveManager->ChatModeType = InnerNet::QuickChatModes::FreeChatOrQuickChat;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(AmongUsClient __instance, [HarmonyArgument(0)] ClientData client)
	bool DynamicLobbies::SendChatPatch::AmongUsClientOnPlayerJoined::Prefix(AmongUsClient *__instance, ClientData *client)
	{
		if (LobbyLimit < __instance->allClients->Count)
		{ // TODO: Fix this canceling start
			DisconnectPlayer(__instance, client->Id);
			return false;
		}
		return true;
	}

	void DynamicLobbies::SendChatPatch::AmongUsClientOnPlayerJoined::DisconnectPlayer(InnerNetClient *_this, int clientId)
	{
		if (!_this->AmHost)
		{
			return;
		}
		MessageWriter *messageWriter = MessageWriter::Get(SendOption::Reliable);
		messageWriter->StartMessage(4);
		messageWriter->Write(_this->GameId);
		messageWriter->WritePacked(clientId);
		messageWriter->Write(static_cast<unsigned char>(DisconnectReasons::GameFull));
		messageWriter->EndMessage();
		_this->SendOrDisconnect(messageWriter);
		messageWriter->Recycle();
	}
}
