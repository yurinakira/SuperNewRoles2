using Hazel;
using SuperNewRoles.CustomRPC;
using SuperNewRoles.Helpers;
using SuperNewRoles.Mode;
using SuperNewRoles.Patch;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SuperNewRoles.Roles
{
    public static class SchrodingersCat
    {
        public static void Sets(PlayerControl __instance,PlayerControl target)
        {
            switch (__instance.getRole())
            {
                case RoleId.Sheriff:
                case RoleId.MeetingSheriff:
                case RoleId.RemoteSheriff:
                    SetType(RoleClass.SchrodingerCat.SchrodingerCatType.Crewmate);
                    break;
                case RoleId.Jackal:
                case RoleId.TeleportingJackal:
                    SetType(RoleClass.SchrodingerCat.SchrodingerCatType.Jackal);
                    break;
                default:
                    if (__instance.isImpostor())
                    {
                        SetType(RoleClass.SchrodingerCat.SchrodingerCatType.Impostor);
                    }
                    break;
            }
        }
        public static void SetType(RoleClass.SchrodingerCat.SchrodingerCatType type)
        {
            SuperNewRolesPlugin.Logger.LogInfo("セットするタイプ:"+type);
            MessageWriter writer = RPCHelper.StartRPC(CustomRPC.CustomRPC.SetSchrodingerCatType);
            writer.Write(PlayerControl.LocalPlayer.PlayerId);
            writer.Write((byte)type);
            writer.EndRPC();
            RPCProcedure.SetSchrodingerCatType(PlayerControl.LocalPlayer.PlayerId,(byte)type);
        }
        public static void DeathPlayer(PlayerControl __instance,PlayerControl target)
        {
            if (PlayerControl.LocalPlayer.isRole(RoleId.SchrodingerCat) && target.PlayerId == PlayerControl.LocalPlayer.PlayerId && RoleClass.SchrodingerCat.Get() == RoleClass.SchrodingerCat.SchrodingerCatType.Default)
            {
                SetType(RoleClass.SchrodingerCat.SchrodingerCatType.VoteDead);
                Sets(__instance,target);
                var Writer = RPCHelper.StartRPC(CustomRPC.CustomRPC.ReviveRPC);
                Writer.Write(PlayerControl.LocalPlayer.PlayerId);
                Writer.EndRPC();
                PlayerControl.LocalPlayer.Revive();
                Writer = RPCHelper.StartRPC(CustomRPC.CustomRPC.CleanBody);
                Writer.Write(PlayerControl.LocalPlayer.PlayerId);
                Writer.EndRPC();
                RPCProcedure.CleanBody(PlayerControl.LocalPlayer.PlayerId);
            }
        }
        public static void Update()
        {
            if (ModeHandler.isMode(ModeId.Default))
            {
            } else if (ModeHandler.isMode(ModeId.SuperHostRoles))
            {

            }
        }
    }
}
