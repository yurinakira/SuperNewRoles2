#include "CopyGameCode.h"
#include "../Config.h"

using namespace HarmonyLib;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

	void CopyGameCode::GameStartManagerStartPatch::Postfix(GameStartManager *__instance)
	{
		if (ConfigRoles::getAutoCopyGameCode()->Value)
		{
			std::wstring code = InnerNet::GameCode::IntToGameName(AmongUsClient::Instance->GameId);
			GUIUtility->systemCopyBuffer = code;
		}
	}
}
