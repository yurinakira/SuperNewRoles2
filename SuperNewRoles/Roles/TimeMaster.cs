using HarmonyLib;
using Hazel;
using System;
using SuperNewRoles.Patches;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using SuperNewRoles.Buttons;
using SuperNewRoles.CustomOption;
using SuperNewRoles.Helpers;
using SuperNewRoles.Mode;
using SuperNewRoles.Mode.SuperHostRoles;

namespace SuperNewRoles.Roles
{

    class TimeMaster
    {

        public static void ResetCoolDown()
        {
            HudManagerStartPatch.TimeMasterTimeMasterShieldButton.MaxTimer = RoleClass.TimeMaster.Cooldown;
            RoleClass.TimeMaster.ButtonTimer = DateTime.Now;
        }
        public static bool IsTimeMaster(PlayerControl Player)
        {
            if (RoleClass.TimeMaster.TimeMasterPlayer.IsCheckListPlayerControl(Player))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        public static void TimeShieldStart()
        {
            RoleClass.TimeMaster.ShieldActive = true;
        }

        public static void TimeShieldEnd()
        {
            if (!RoleClass.TimeMaster.ShieldActive) return;
            RoleClass.TimeMaster.ShieldActive = false;

        }
        public static void EndMeeting()
        {
            HudManagerStartPatch.TimeMasterTimeMasterShieldButton.MaxTimer = RoleClass.TimeMaster.Cooldown;
            RoleClass.TimeMaster.ButtonTimer = DateTime.Now;
            RoleClass.TimeMaster.ShieldActive = false;
        }

        public static void ResetTimeMasterButton()
        {
            HudManagerStartPatch.TimeMasterTimeMasterShieldButton.Timer = HudManagerStartPatch.TimeMasterTimeMasterShieldButton.MaxTimer;
            HudManagerStartPatch.TimeMasterTimeMasterShieldButton.isEffectActive = false;
            HudManagerStartPatch.TimeMasterTimeMasterShieldButton.actionButton.cooldownTimerText.color = Palette.EnabledColor;
        }

    }

    /*public static class TimeMaster
    {
        public static void ResetTimeMasterButton()
        {
            HudManagerStartPatch.TimeMasterTimeMasterShieldButton.Timer = HudManagerStartPatch.TimeMasterTimeMasterShieldButton.MaxTimer;
            HudManagerStartPatch.TimeMasterTimeMasterShieldButton.isEffectActive = false;
            HudManagerStartPatch.TimeMasterTimeMasterShieldButton.actionButton.cooldownTimerText.color = Palette.EnabledColor;
        }

        public static void ResetCoolDown()
        {
            HudManagerStartPatch.TimeMasterTimeMasterShieldButton.MaxTimer = RoleClass.TimeMaster.Cooldown;
            RoleClass.TimeMaster.ButtonTimer = DateTime.Now;
        }
        public static bool IsTimeMaster(PlayerControl Player)
        {
            if (RoleClass.TimeMaster.TimeMasterPlayer.IsCheckListPlayerControl(Player))
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
            HudManagerStartPatch.TimeMasterTimeMasterShieldButton.MaxTimer = RoleClass.TimeMaster.Cooldown;
            RoleClass.TimeMaster.ButtonTimer = DateTime.Now;
        }
    }*/
}
