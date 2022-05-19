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
        static void SetType(RoleClass.SchrodingerCat.SchrodingerCatType type)
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
            SuperNewRolesPlugin.Logger.LogInfo("シュレメLP");
            if (PlayerControl.LocalPlayer.isRole(RoleId.SchrodingerCat) && target.PlayerId == PlayerControl.LocalPlayer.PlayerId && RoleClass.SchrodingerCat.Get() == RoleClass.SchrodingerCat.SchrodingerCatType.Default)
            {
                SuperNewRolesPlugin.Logger.LogInfo("通過");
                SetType(RoleClass.SchrodingerCat.SchrodingerCatType.VoteDead);
                SuperNewRolesPlugin.Logger.LogInfo("dead");
                SuperNewRolesPlugin.Logger.LogInfo("死亡通過");
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
                var Writer = RPCHelper.StartRPC(CustomRPC.CustomRPC.ReviveRPC);
                Writer.Write(PlayerControl.LocalPlayer.PlayerId);
                Writer.EndRPC();
                //RPCProcedure.ReviveRPC(PlayerControl.LocalPlayer.PlayerId);
                PlayerControl.LocalPlayer.Revive();
                SuperNewRolesPlugin.Logger.LogInfo("リバイブ");
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
