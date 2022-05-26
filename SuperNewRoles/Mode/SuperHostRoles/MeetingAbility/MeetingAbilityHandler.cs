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
        public static void VoteHandle(PlayerControl player,PlayerControl target)
        {
            if (!MeetingAbilityData.ContainsKey(player.PlayerId)) MeetingAbilityData.Add(player.PlayerId, false);
            RoleId role = player.getRole();
            if (!CanUseAbilityRole(role)) return;
            if (target.IsBot())
            {
                player.SetAbilityMode(player.IsVoteMode());
                return;
            }
        }
        public static bool CanUseAbility(PlayerControl player)
        {
            return CanUseAbilityRole(player.getRole());
        }
        public static bool CanUseAbilityRole(RoleId role)
        {
            switch (role)
            {

            }
            return false;
        }
    }
}
