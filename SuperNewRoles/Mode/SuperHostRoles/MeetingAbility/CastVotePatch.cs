using HarmonyLib;
using System;
using System.Collections.Generic;
using System.Text;

namespace SuperNewRoles.Mode.SuperHostRoles.MeetingAbility
{
    [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.CastVote))]
    class CastVotePatch
    {
        public static bool Prefix(MeetingHud __instance, [HarmonyArgument(0)] byte srcPlayerId, [HarmonyArgument(1)] byte suspectPlayerId)
        {
            static int IndexOf<T>(T[] self, Predicate<T> pred)
            {
                for (int i = 0; i < self.Length; i++)
                {
                    if (pred(self[i]))
                    {
                        return i;
                    }
                }
                return -1;
            }
            if (!ModeHandler.isMode(ModeId.SuperHostRoles)) return true;
            int num = IndexOf(__instance.playerStates, (PlayerVoteArea pv) => pv.TargetPlayerId == srcPlayerId);
            PlayerVoteArea playerVoteArea = __instance.playerStates[num];
            if (!playerVoteArea.AmDead)
            {
                if (MeetingAbilityHandler.VoteHandle(ModHelpers.playerById(srcPlayerId), ModHelpers.playerById(suspectPlayerId)))
                {
                    if (PlayerControl.LocalPlayer.PlayerId == srcPlayerId || AmongUsClient.Instance.GameMode != 0)
                    {
                        SoundManager.Instance.PlaySound(__instance.VoteLockinSound, loop: false);
                    }
                    playerVoteArea.SetVote(suspectPlayerId);
                    __instance.SetDirtyBit(1u);
                    __instance.CheckForEndVoting();
                    if (!playerVoteArea.DidVote)
                    {
                        PlayerControl.LocalPlayer.RpcSendChatNote(srcPlayerId, ChatNoteTypes.DidVote);
                    }
                }
            }
            return false;
        }
    }
}
