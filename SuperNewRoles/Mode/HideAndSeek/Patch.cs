using HarmonyLib;
using Hazel;
using SuperNewRoles.Mode.SuperHostRoles;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace SuperNewRoles.Mode.HideAndSeek
{
    class Patch
    {
        public class HASFixed
        {
            public static void Postfix(PlayerControl __instance)
            {
                if (AmongUsClient.Instance.AmHost)
                {
                    foreach (PlayerControl player in PlayerControl.AllPlayerControls)
                    {
                        if (player.isImpostor())
                        {
                            if (player.nameText.text != ModHelpers.cs(Roles.RoleClass.ImpostorRed, player.getDefaultName()))
                            {
                                player.RpcSetName(ModHelpers.cs(Roles.RoleClass.ImpostorRed, player.getDefaultName()));
                            }
                        }
                        else
                        {
                            if (player.nameText.text != ModHelpers.cs(new Color32(0, 255, 0, byte.MaxValue), player.getDefaultName()))
                            {
                                player.RpcSetName(ModHelpers.cs(new Color32(0, 255, 0, byte.MaxValue), player.getDefaultName()));
                            }                        
                        }
                    }
                }
                HudManager.Instance.ReportButton.Hide();
                HudManager.Instance.AbilityButton.Hide();
                
            }
        }
    }
}
