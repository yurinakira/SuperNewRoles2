#include "Chat.h"
#include "../../ModHelpers.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::EndGame;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{

bool Chat::IsOldSHR = false;
std::optional<CustomGameOverReason> Chat::WinCond;
std::vector<PlayerControl*> Chat::Winner;

	void Chat::GameStartManagerStartPatch::Postfix()
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (IsOldSHR && WinCond && AmongUsClient::Instance->AmHost)
		{
			auto Template = L"最終結果\n勝利陣営:{0}";
			if (WinCond == CustomGameOverReason::GodWin)
			{
				auto players = L"";
				try
				{
					for (auto p : Winner)
					{
						if (players == L"")
						{
							players += SuperNewRoles::ModHelpers::nameText(p)->text;
						}
						else
						{
							players += L"," + SuperNewRoles::ModHelpers::nameText(p)->text;
						}
					}
				}
				catch (...)
				{
				}
				//new LateTask(() => {
				PlayerControl::LocalPlayer::RpcSendChat(StringHelper::formatSimple(Template + L"\n勝者:{1}", L"神(God)", players));
				//}, 3f, "SendResult");
			}
			else if (WinCond == CustomGameOverReason::CrewmateWin)
			{
				//new LateTask(() => {
				PlayerControl::LocalPlayer::RpcSendChat(std::wstring::Format(Template, L"クルーメイト(Crewmate)"));
				//}, 3f, "SendResult");
			}
			else if (WinCond == CustomGameOverReason::ImpostorWin)
			{
				//new LateTask(() => {
				PlayerControl::LocalPlayer::RpcSendChat(std::wstring::Format(Template, L"インポスター(Impostor)"));
				//}, 3f, "SendResult");
			}
			else if (WinCond == CustomGameOverReason::JesterWin && !Winner.empty())
			{
				//new LateTask(() => {
				PlayerControl::LocalPlayer::RpcSendChat(StringHelper::formatSimple(Template + L"\n勝者:{1}", L"てるてる(Jester)", SuperNewRoles::ModHelpers::nameText(Winner[0])->text));
				// }, 3f, "SendResult");
			}
			else if (WinCond == CustomGameOverReason::WorkpersonWin && !Winner.empty())
			{
				// new LateTask(() => {
				PlayerControl::LocalPlayer::RpcSendChat(StringHelper::formatSimple(Template + L"\n勝者:{1}", L"仕事人(Workperson)", SuperNewRoles::ModHelpers::nameText(Winner[0])->text));
				//}, 3f, "SendResult");
			}
		}
		IsOldSHR = false;
		WinCond = std::nullopt;
		Winner = std::vector<PlayerControl*>();
	}
}
