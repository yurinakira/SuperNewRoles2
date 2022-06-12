using HarmonyLib;
using SuperNewRoles.Mode;
using System;
using System.Collections.Generic;
using System.Text;
using Hazel;
using SuperNewRoles.Buttons;
using UnityEngine;

namespace SuperNewRoles.Roles
{
    [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.MurderPlayer))]
    public class SetGuard
    {
        public static void Prefix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target [HarmonyArgument(1)] PlayerControl killer)
        {
            //ガードセット
            if (__instance.PlayerId != target.PlayerId)
            {
                if (target.isRole(CustomRPC.RoleId.SchrodingerCat))
                {
                    target.RpcProtectPlayer(target, 0);
                    // KillerRole = CustomRPC.RoleId.Bakery;
                    //target.setRole(KillerRole);
                }
            }
        }
    }
    public class a
    {
        public string b
        {
            if(killer.isImpostor) return "Impostor";
        }
    }
}