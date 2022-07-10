#include "CachedPlayer.h"
#include "../Main.h"

using namespace HarmonyLib;
using namespace InnerNet;
using namespace UnityEngine;

namespace SuperNewRoles
{

std::unordered_map<std::intptr_t, CachedPlayer*> CachedPlayer::PlayerPtrs;
std::vector<CachedPlayer*> CachedPlayer::AllPlayers;
CachedPlayer *CachedPlayer::LocalPlayer;

	CachedPlayer::operator bool()
	{
		return this != nullptr && this->PlayerControl;
	}

	CachedPlayer::operator PlayerControl*()
	{
		return this->PlayerControl;
	}

	CachedPlayer::operator PlayerPhysics*()
	{
		return this->PlayerPhysics;
	}

	MethodBase *CachedPlayerPatches::CacheLocalPlayerPatch::TargetMethod()
	{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
		auto type = typeof(PlayerControl)->GetNestedTypes(AccessTools::all).FirstOrDefault([&] (std::any t)
		{
			return t->Name.Contains(L"Start");
		});
		return AccessTools::Method(type, L"MoveNext");
	}

	void CachedPlayerPatches::CacheLocalPlayerPatch::SetLocalPlayer()
	{
		auto localPlayer = PlayerControl::LocalPlayer;
		if (!localPlayer)
		{
			CachedPlayer::LocalPlayer = nullptr;
			return;
		}

		auto cached = CachedPlayer::AllPlayers.FirstOrDefault([&] (std::any p)
		{
			return p::PlayerControl->Pointer == localPlayer->Pointer;
		});
		if (cached != nullptr)
		{
			CachedPlayer::LocalPlayer = cached;
			return;
		}
	}

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
	void CachedPlayerPatches::CachePlayerPatch(PlayerControl *__instance)
	{
		if (__instance->notRealPlayer)
		{
			return;
		}
		auto player = new CachedPlayer();
		player->transform = __instance->transform;
		player->PlayerControl = __instance;
		player->PlayerPhysics = __instance->MyPhysics;
		player->NetTransform = __instance->NetTransform;
		CachedPlayer::AllPlayers.push_back(player);
		CachedPlayer::PlayerPtrs[__instance->Pointer] = player;

	#if defined(DEBUG)
		for (auto cachedPlayer : CachedPlayer::AllPlayers)
		{
			if (!cachedPlayer->PlayerControl || !cachedPlayer->PlayerPhysics || !cachedPlayer->NetTransform || !cachedPlayer->transform)
			{
				SuperNewRolesPlugin::Logger->LogError(L"CachedPlayer {cachedPlayer.PlayerControl.name} has null fields");
			}
		}
	#endif

//C# TO C++ CONVERTER TODO TASK: A 'delete player' statement was not added since player was passed to a method or constructor. Handle memory management manually.
	}

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
	void CachedPlayerPatches::RemoveCachedPlayerPatch(PlayerControl *__instance)
	{
		if (__instance->notRealPlayer)
		{
			return;
		}
		CachedPlayer::AllPlayers.RemoveAll([&] (std::any p)
		{
			return p::PlayerControl->Pointer == __instance->Pointer;
		});
		CachedPlayer::PlayerPtrs.erase(__instance->Pointer);
	}

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
	void CachedPlayerPatches::AddCachedDataOnDeserialize()
	{
		for (auto cachedPlayer : CachedPlayer::AllPlayers)
		{
			cachedPlayer->Data = cachedPlayer->PlayerControl->Data;
			cachedPlayer->PlayerId = cachedPlayer->PlayerControl->PlayerId;
			cachedPlayer->NetId = cachedPlayer->PlayerControl->NetId;
		}
	}

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
	void CachedPlayerPatches::AddCachedDataOnAddPlayer()
	{
		for (auto cachedPlayer : CachedPlayer::AllPlayers)
		{
			cachedPlayer->Data = cachedPlayer->PlayerControl->Data;
			cachedPlayer->PlayerId = cachedPlayer->PlayerControl->PlayerId;
			cachedPlayer->NetId = cachedPlayer->PlayerControl->NetId;
		}
	}

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
	void CachedPlayerPatches::SetCachedPlayerId(PlayerControl *__instance)
	{
		CachedPlayer::PlayerPtrs[__instance->Pointer]->PlayerId = __instance->PlayerId;
		CachedPlayer::PlayerPtrs[__instance->Pointer]->NetId = __instance->NetId;
	}
}
