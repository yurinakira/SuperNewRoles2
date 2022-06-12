using HarmonyLib;
using Hazel;
using System;
using System.Collections.Generic;
using SuperNewRoles.Patches;
using UnityEngine;
using SuperNewRoles.Buttons;
using SuperNewRoles.CustomOption;

namespace SuperNewRoles.Roles
{
    class OverLoader
    {
        public static void ResetCoolDown()
        {
            HudManagerStartPatch.OverLoaderOverLoadButton.MaxTimer = RoleClass.OverLoader.CoolTime;
            RoleClass.OverLoader.ButtonTimer = DateTime.Now;
        }
        public static void BoostStart()
        {
            MessageWriter writer = AmongUsClient.Instance.StartRpcImmediately(PlayerControl.LocalPlayer.NetId, (byte)CustomRPC.CustomRPC.SetOverLoad, Hazel.SendOption.Reliable, -1);
            writer.Write(true);
            writer.Write(PlayerControl.LocalPlayer.PlayerId);
            AmongUsClient.Instance.FinishRpcImmediately(writer);
            CustomRPC.RPCProcedure.SetOverLoad(true, PlayerControl.LocalPlayer.PlayerId);
            RoleClass.OverLoader.IsOverLoad = true;
            OverLoader.ResetCoolDown();
        }
        public static void OverLoad_NameStart()
        {
            CustomRPC.RPCProcedure.SetOverLoad_Name(true, PlayerControl.LocalPlayer.PlayerId);
        }
        public static void ResetSpeed()
        {
            MessageWriter writer = AmongUsClient.Instance.StartRpcImmediately(PlayerControl.LocalPlayer.NetId, (byte)CustomRPC.CustomRPC.SetOverLoad, Hazel.SendOption.Reliable, -1);
            writer.Write(false);
            writer.Write(PlayerControl.LocalPlayer.PlayerId);
            AmongUsClient.Instance.FinishRpcImmediately(writer);
            CustomRPC.RPCProcedure.SetOverLoad(false, PlayerControl.LocalPlayer.PlayerId);
            RoleClass.OverLoader.IsOverLoad = false;
        }
        public static void ResetOverLoad_Name()
        {
            CustomRPC.RPCProcedure.SetOverLoad_Name(false, PlayerControl.LocalPlayer.PlayerId);
        }

        public static void SpeedBoostCheck()
        {
            if (!RoleClass.OverLoader.IsOverLoad) return;
            if (HudManagerStartPatch.OverLoaderOverLoadButton.Timer + RoleClass.OverLoader.DurationTime <= RoleClass.OverLoader.CoolTime) SpeedBoostEnd();
        }
        public static void SpeedBoostEnd()
        {
            ResetSpeed();
            ResetCoolDown();
        }
        public static void OverLoad_NameEnd()
        {
            ResetOverLoad_Name();
        }
        public static bool IsOverLoader(PlayerControl Player)
        {
            if (RoleClass.OverLoader.OverLoaderPlayer.IsCheckListPlayerControl(Player))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        public static void EndMeeting()
        {

            HudManagerStartPatch.OverLoaderOverLoadButton.MaxTimer = RoleClass.OverLoader.CoolTime;
            RoleClass.OverLoader.ButtonTimer = DateTime.Now;
            ResetSpeed();
            ResetOverLoad_Name();

        }
    }
}
