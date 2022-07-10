#include "SelectTask.h"
#include "../Mode/ModeHandler.h"
#include "../ModHelpers.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;

namespace SuperNewRoles::Patch
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix(GameData __instance, [HarmonyArgument(0)] byte playerId, [HarmonyArgument(1)] ref UnhollowerBaseLib.Il2CppStructArray<byte> taskTypeIds)
	void SelectTask::RpcSetTasksPatch::Prefix(GameData *__instance, unsigned char playerId, UnhollowerBaseLib::Il2CppStructArray<unsigned char> *&taskTypeIds)
	{
		if (GameData::Instance->GetPlayerById(playerId).Object.IsBot() || taskTypeIds->Length == 0)
		{
			taskTypeIds = std::vector<unsigned char>(0);
			return;
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles, ModeId::Default}) && AmongUsClient::Instance->GameMode != GameModes::FreePlay)
		{
//C# TO C++ CONVERTER NOTE: The following 'decomposition declaration' requires C++17:
//ORIGINAL LINE: var(commont, shortt, longt) = GameData.Instance.GetPlayerById(playerId).Object.GetTaskCount();
			auto [commont, shortt, longt] = GameData::Instance->GetPlayerById(playerId).Object.GetTaskCount();
			auto TasksList = ModHelpers::generateTasks(commont, shortt, longt);
			taskTypeIds = new UnhollowerBaseLib::Il2CppStructArray<unsigned char>(TasksList.size());
			for (int i = 0; i < TasksList.size(); i++)
			{
				taskTypeIds[i] = TasksList[i];
			}
		}
	}
}
