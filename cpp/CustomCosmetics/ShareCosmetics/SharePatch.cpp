#include "SharePatch.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../Config.h"
#include "../../CustomRPC/CustomRPC.h"
#include "ShareNamePlate.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace UnityEngine;

namespace SuperNewRoles::CustomCosmetics::ShareCosmetics
{

std::unordered_map<int, std::wstring> SharePatch::PlayerUrl;
std::unordered_map<int, std::wstring> SharePatch::PlayerDatas;
std::unordered_map<int, CosmeticsObject*> SharePatch::PlayerObjects;
int SharePatch::GameStartManagerUpdatePatch::Proce = 0;

	void SharePatch::GameStartManagerUpdatePatch::Postfix(GameStartManager *__instance)
	{
		Proce++;
		if (Proce >= 10)
		{
			MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ShareCosmetics), Hazel::SendOption::Reliable, -1);
			writer->Write(static_cast<unsigned char>(CachedPlayer::LocalPlayer->PlayerId));
			writer->Write(ConfigRoles::getShareCosmeticsNamePlatesURL()->Value);
			AmongUsClient::Instance->FinishRpcImmediately(writer);
			CustomRPC::RPCProcedure::ShareCosmetics(static_cast<unsigned char>(CachedPlayer::LocalPlayer->PlayerId), ConfigRoles::getShareCosmeticsNamePlatesURL()->Value);
			Proce = 0;
		}
		/**
		SuperNewRolesPlugin.Logger.LogInfo("-plates-");
		SuperNewRolesPlugin.Logger.LogInfo(SharePatch.PlayerObjects[CachedPlayer.LocalPlayer.PlayerId].GUID);
		SuperNewRolesPlugin.Logger.LogInfo("ALL:"+ PlayerObjects[CachedPlayer.LocalPlayer.PlayerId].AllNamePlates);
		foreach (NamePlatesObject a in SharePatch.PlayerObjects[CachedPlayer.LocalPlayer.PlayerId].AllNamePlates)
		{
		    SuperNewRolesPlugin.Logger.LogInfo("--");
		    SuperNewRolesPlugin.Logger.LogInfo("NAME"+a.Name);
		    SuperNewRolesPlugin.Logger.LogInfo("AUTHOR"+a.Author);
		    SuperNewRolesPlugin.Logger.LogInfo("URL"+a.Url);
		    //SuperNewRolesPlugin.Logger.LogInfo("--");
		}
		SuperNewRolesPlugin.Logger.LogInfo("--------");
		**/
	}

	void SharePatch::GameStartManagerStartPatch::Postfix()
	{
		ShareNamePlate::NamePlateSprites = std::unordered_map<int, Sprite*>();
		PlayerUrl = std::unordered_map<int, std::wstring>();
		PlayerDatas = std::unordered_map<int, std::wstring>();
		PlayerObjects = std::unordered_map<int, CosmeticsObject*>();
	}
}
