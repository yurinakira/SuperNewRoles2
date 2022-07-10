#pragma once

#include "../CustomOption/CustomOptionModel.h"
#include "../Intro/IntroDate.h"
#include "../Roles/TeamRoleType.h"
#include <string>
#include <vector>
#include "../stringhelper.h"

using namespace BepInEx::IL2CPP::Utils;
using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerPhysics), nameof(PlayerPhysics.CoSpawnPlayer))] public class AmongUsClientOnPlayerJoinedPatch
	class AmongUsClientOnPlayerJoinedPatch
	{
	public:
		static void Postfix(PlayerPhysics *__instance, LobbyBehaviour *lobby);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ChatController), nameof(ChatController.AddChat))] class AddChatPatch
	class AddChatPatch
	{
	private:
		static std::wstring SNR;
		static std::wstring SNRCommander;
	public:
		static std::wstring WelcomeToSuperNewRoles;

		static bool Prefix(PlayerControl *sourcePlayer, const std::wstring &chatText);
	private:
		static std::wstring GetChildText(std::vector<CustomOption::CustomOption*> &options, const std::wstring &indent);
		static std::wstring GetOptionText(CustomRoleOption *RoleOption, IntroDate *intro);
		static std::wstring GetTeamText(TeamRoleType type);
		static std::wstring GetText(CustomRoleOption *option);
		static std::wstring GetInRole(std::vector<CustomRoleOption*> &optionsnotorder);
		static void RoleCommand(PlayerControl *target = nullptr, float SendTime = 1.5f);
		static void GetInRoleCommand(PlayerControl *target = nullptr);
		static void Send(PlayerControl *target, const std::wstring &rolename, const std::wstring &text, float time = 0);
	public:
		static void SendCommand(PlayerControl *target, const std::wstring &command, const std::wstring &SendName = L"NONE");
	private:
		static System::Collections::IEnumerator *AllSend(const std::wstring &SendName, const std::wstring &command, const std::wstring &name, float time = 0);
		static System::Collections::IEnumerator *PrivateSend(PlayerControl *target, const std::wstring &SendName, const std::wstring &command, float time = 0);
	}; /*
    [HarmonyPatch(typeof(ChatController),nameof(ChatController.AddChat))]
    class ChatHandler
    {
        public static bool Prefix(ChatController __instance, [HarmonyArgument(0)] ref PlayerControl sourcePlayer, [HarmonyArgument(1)] ref string chatText)
        {

            if (!(bool)(UnityEngine.Object)sourcePlayer || !(bool)(UnityEngine.Object)PlayerControl.LocalPlayer)
                return false;
            GameData.PlayerInfo data1 = CachedPlayer.LocalPlayer.Data;
            GameData.PlayerInfo data2 = sourcePlayer.Data;
            if (data2 == null || data1 == null || data2.IsDead && (!PlayerControl.LocalPlayer.isDead() || PlayerControl.LocalPlayer.isRole(CustomRPC.RoleId.NiceRedRidingHood)))
                return false;
            if (__instance.chatBubPool.NotInUse == 0)
                __instance.chatBubPool.ReclaimOldest();
            ChatBubble bubble = FastDestroyableSingleton<HudManager>.Instance.Chat.chatBubPool.Get<ChatBubble>();
            try
            {
                bubble.transform.SetParent(__instance.scroller.Inner);
                bubble.transform.localScale = Vector3.one;
                int num = (UnityEngine.Object)sourcePlayer == (UnityEngine.Object)PlayerControl.LocalPlayer ? 1 : 0;
                if (num != 0)
                    bubble.SetRight();
                else
                    bubble.SetLeft();
                bool flag = (bool)(UnityEngine.Object)data1.Role && (bool)(UnityEngine.Object)data2.Role && data1.Role.NameColor == data2.Role.NameColor;
                bool didVote = (bool)(UnityEngine.Object)MeetingHud.Instance && MeetingHud.Instance.DidVote(sourcePlayer.PlayerId);
                https://media.discordapp.net/attachments/965644999578513450/967642315541856286/2022-04-24_3.png?width=875&height=492           bubble.SetCosmetics(data2);
                __instance.SetChatBubbleName(bubble, data2, data2.IsDead, didVote, flag ? data2.Role.NameColor : Color.white);
                if (SaveManager.CensorChat)
                    chatText = BlockedWords.CensorWords(chatText);
                bubble.SetText(chatText);
                bubble.AlignChildren();
                __instance.AlignAllBubbles();
                if (!FastDestroyableSingleton<HudManager>.Instance.Chat.IsOpen && FastDestroyableSingleton<HudManager>.Instance.Chat.notificationRoutine == null)
                    FastDestroyableSingleton<HudManager>.Instance.Chat.notificationRoutine = __instance.StartCoroutine(__instance.BounceDot());
                if (num != 0)
                    return false;
                SoundManager.Instance.PlaySound(__instance.MessageSound, false).pitch = (float)(0.5 + (double)sourcePlayer.PlayerId / 15.0);
            }
            catch (Exception ex)
            {
                SuperNewRolesPlugin.Logger.LogError((object)ex);
                FastDestroyableSingleton<HudManager>.Instance.Chat.chatBubPool.Reclaim((PoolableBehavior)bubble);
            }
            return false;
        }
    }
    **/
}
