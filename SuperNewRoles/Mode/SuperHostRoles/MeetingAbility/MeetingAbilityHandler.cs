using SuperNewRoles.CustomRPC;
using System;
using System.Collections.Generic;
using System.Text;

namespace SuperNewRoles.Mode.SuperHostRoles.MeetingAbility
{
    public static class MeetingAbilityHandler
    {
        public static Dictionary<byte, bool> MeetingAbilityData;

        public static bool IsAbilityMode(this PlayerControl player)
        {
            return IsAbilityMode(player.PlayerId);
        }
        public static bool IsAbilityMode(byte player)
        {
            return MeetingAbilityData.ContainsKey(player) && MeetingAbilityData[player];
        }
        public static bool IsVoteMode(this PlayerControl player)
        {
            return !IsAbilityMode(player);
        }
        public static void SetAbilityMode(this PlayerControl player,bool IsAbility)
        {
            if (MeetingAbilityData.ContainsKey(player.PlayerId))
            {
                MeetingAbilityData[player.PlayerId] = IsAbility;
            }
        }
        public static bool IsVoteMode(byte player)
        {
            return !IsAbilityMode(player);
        }
        public static void ClearAndReloads()
        {
            MeetingAbilityData = new Dictionary<byte, bool>();
        }
        //trueを返すと通常の投票になります。
        public static bool VoteHandle(PlayerControl player,PlayerControl target)
        {
            if (!MeetingAbilityData.ContainsKey(player.PlayerId)) MeetingAbilityData.Add(player.PlayerId, false);
            RoleId role = player.getRole();
            if (!CanUseAbilityRole(role)) return true;
            if (target.IsBot())
            {
                player.SetAbilityMode(player.IsVoteMode());
                MeetingHud.Instance.RpcClearVote(player.getClientId());
                return false;
            }
            else if (player.IsVoteMode())
            {
                return true;
            }
            return true;
        }
        public static bool CanUseAbility(PlayerControl player)
        {
            return CanUseAbilityRole(player.getRole());
        }
        public static bool CanUseAbilityRole(RoleId role)
        {
            return true;
            switch (role)
            {
                case RoleId.MeetingSheriff:
                    return true;
            }
            return false;
        }
    }
}
