#include "Jackal.h"
#include "../../ModeHandler.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles::Roles
{

	void Jackal::SpawnBot::Prefix(AmongUsClient *__instance)
	{
		if (!ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			return;
		}
	}
}
