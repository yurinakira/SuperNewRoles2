#include "Blackoutfix.h"
#include "../ModeHandler.h"

using namespace HarmonyLib;

namespace SuperNewRoles::Mode::SuperHostRoles
{

	void Blackoutfix::CheckForEndVotingPatch::Prefix(MeetingHud *__instance)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (Mode::ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {Mode::ModeId::SuperHostRoles}))
		{
			EndMeetingPatch();
		}
	}

	void Blackoutfix::EndMeetingPatch()
	{
		//BotManager.Spawn("暗転対策");
	}
}
