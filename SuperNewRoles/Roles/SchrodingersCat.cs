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
            MessageWriter writer = RPCHelper.StartRPC(CustomRPC.CustomRPC.SetSchrodingerCatType);
            writer.Write(PlayerControl.LocalPlayer.PlayerId);
            writer.Write((byte)type);
            writer.EndRPC();
            RPCProcedure.SetSchrodingerCatType(PlayerControl.LocalPlayer.PlayerId,(byte)type);
        }
        public static void Update()
        {
            if (ModeHandler.isMode(ModeId.Default))
            {
                if (PlayerControl.LocalPlayer.isRole(RoleId.SchrodingerCat) && RoleClass.SchrodingerCat.Get() == RoleClass.SchrodingerCat.SchrodingerCatType.Default && PlayerControl.LocalPlayer.isDead())
                {
                    SetType(RoleClass.SchrodingerCat.SchrodingerCatType.VoteDead);
                    new LateTask(() =>
                    {
                        DeadPlayer deadPlayer = DeadPlayer.deadPlayers?.Where(x => x.player?.PlayerId == PlayerControl.LocalPlayer.PlayerId)?.FirstOrDefault();

                        if (deadPlayer.killerIfExisting != null)
                        {
                            switch (deadPlayer.killerIfExisting.getRole())
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
                                    if (deadPlayer.killerIfExisting.isImpostor())
                                    {
                                        SetType(RoleClass.SchrodingerCat.SchrodingerCatType.Impostor);
                                    }
                                    break;
                            }
                        }
                        var Writer = RPCHelper.StartRPC(CustomRPC.CustomRPC.ReviveRPC);
                        Writer.Write(PlayerControl.LocalPlayer.PlayerId);
                        Writer.EndRPC();
                        CustomRPC.RPCProcedure.ReviveRPC(PlayerControl.LocalPlayer.PlayerId);
                        Writer = RPCHelper.StartRPC(CustomRPC.CustomRPC.CleanBody);
                        Writer.Write(PlayerControl.LocalPlayer.PlayerId);
                        Writer.EndRPC();
                        CustomRPC.RPCProcedure.CleanBody(PlayerControl.LocalPlayer.PlayerId);
                    }, 0.1f);
                }
            } else if (ModeHandler.isMode(ModeId.SuperHostRoles))
            {

            }
        }
    }
}
