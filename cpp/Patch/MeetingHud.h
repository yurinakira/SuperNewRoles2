#pragma once

#include <unordered_map>
#include <vector>
#include <limits>
#include <stdexcept>
#include <tuple>

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;
using namespace static MeetingHud;

namespace SuperNewRoles::Patch
{
	/*
	[HarmonyPatch(typeof(PlayerVoteArea), nameof(PlayerVoteArea.SetCosmetics))]
	class PlayerVoteAreaCosmetics
	{
	    private static Sprite blankNameplate = null;
	    public static void updateNameplate(PlayerVoteArea pva, byte playerId = Byte.MaxValue)
	    {
	        blankNameplate = blankNameplate ?? HatManager.Instance.AllNamePlates[0].viewData.viewData.Image;

	        var nameplate = blankNameplate;
	        var p = ModHelpers.playerById(playerId != byte.MaxValue ? playerId : pva.TargetPlayerId);
	        var nameplateId = p?.CurrentOutfit?.NamePlateId;
	        nameplate = HatManager.Instance.GetNamePlateById(nameplateId)?.viewData.viewData.Image;
	        pva.Background.sprite = nameplate;
	    }
	    static void Postfix(PlayerVoteArea __instance, GameData.PlayerInfo playerInfo)
	    {
	        updateNameplate(__instance, playerInfo.PlayerId);
	    }
	}*/
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.VotingComplete))] class VotingComplete
	class VotingComplete
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix(MeetingHud __instance, [HarmonyArgument(0)] VoterState[] states, [HarmonyArgument(1)] ref GameData.PlayerInfo exiled, [HarmonyArgument(2)] bool tie)
		static void Prefix(MeetingHud *__instance, std::vector<VoterState*> &states, GameData::PlayerInfo *&exiled, bool tie);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.CheckForEndVoting))] class CheckForEndVotingPatch
	class CheckForEndVotingPatch
	{
	public:
		static bool Prefix(MeetingHud *__instance);
		static bool isMayor(unsigned char id);
	private:
		static std::tuple<bool, unsigned char, PlayerVoteArea*> assassinVoteState(MeetingHud *__instance);
	};

	class ExtendedMeetingHud final
	{
	public:
		static std::unordered_map<unsigned char, int> CustomCalculateVotes(MeetingHud *__instance);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.SetForegroundForDead))] class MeetingHudSetForegroundForDeadPatch
	class MeetingHudSetForegroundForDeadPatch
	{
	public:
		static bool Prefix(MeetingHud *__instance);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.UpdateButtons))] class MeetingHudUpdateButtonsPatch
	class MeetingHudUpdateButtonsPatch
	{
	public:
		static bool PreFix(MeetingHud *__instance);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.Start))] class MeetingHudStartPatch
	class MeetingHudStartPatch
	{
	public:
		static void Prefix(MeetingHud *__instance);
		static void Postfix(MeetingHud *__instance);
	};
}
