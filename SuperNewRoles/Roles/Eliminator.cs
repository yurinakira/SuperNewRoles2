using System;
using System.Collections.Generic;
using System.Linq;
using Hazel;
using SuperNewRoles.Buttons;
using SuperNewRoles.CustomRPC;
using UnityEngine;

namespace SuperNewRoles.Roles
{
    public static class Eliminator
    {
        public static void resetCoolDown()
        {
            HudManagerStartPatch.DoubleKillerMainKillButton.MaxTimer = RoleClass.Eliminator.KillCoolTime;
            HudManagerStartPatch.DoubleKillerMainKillButton.Timer = RoleClass.Eliminator.KillCoolTime;
        }
        public static void EndMeeting()
        {
            resetCoolDown();
        }
        public static void setPlayerOutline(PlayerControl target, Color color)
        {
            if (target == null || target.MyRend == null) return;

            target.MyRend().material.SetFloat("_Outline", 1f);
            target.MyRend().material.SetColor("_OutlineColor", color);
        }
    }
}
