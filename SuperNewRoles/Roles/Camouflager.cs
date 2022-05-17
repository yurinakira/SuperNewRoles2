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
    public static class Camouflager
    {

        public static void ResetCoolDown()
        {
            HudManagerStartPatch.CamouflageButton.MaxTimer = RoleClass.Camouflager.CoolTime;
            RoleClass.Camouflager.ButtonTimer = DateTime.Now;
        }
        public static bool isCamouflager(PlayerControl Player)
        {
            if (RoleClass.Camouflager.CamouflagerPlayer.IsCheckListPlayerControl(Player))
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
            HudManagerStartPatch.CamouflageButton.MaxTimer = RoleClass.Camouflager.CoolTime;
            RoleClass.Camouflager.ButtonTimer = DateTime.Now;
        }

        public static void Update()
        {
            float oldCamouflageTimer = RoleClass.Camouflager.CamouflageTimer;

            RoleClass.Camouflager.CamouflageTimer -= Time.deltaTime;

            // Everyone but morphling reset
            if (oldCamouflageTimer > 0f && RoleClass.Camouflager.CamouflageTimer <= 0f)
            {
                if (ModeHandler.isMode(ModeId.Default))
                {
                    RoleClass.Camouflager.ResetCamouflage();
                } else if (ModeHandler.isMode(ModeId.SuperHostRoles))
                {
                    var starter = RoleClass.Camouflager.Started;
                    RoleClass.Camouflager.Started = 255;
                    foreach (PlayerControl p in PlayerControl.AllPlayerControls)
                    {
                        if (p.IsPlayer())
                        {
                            p.RpcShapeshift(p, true);
                        }
                        p.RpcSetName(p.getDefaultName());
                    }
                }
            }
        }
    }
}