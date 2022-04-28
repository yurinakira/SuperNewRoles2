using HarmonyLib;
using System;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

namespace SuperNewRoles.Map.Agartha.Patch.Task
{
    public static class CustomDoorTask
    {
        public static Dictionary<int, int> DoorData;
        [HarmonyPatch(typeof(DoorConsole),nameof(DoorConsole.Use))]
        class UsePatch
        {
            public static bool Prefix(DoorConsole __instance)
            {
                //IL_006f: Unknown result type (might be due to invalid IL or missing references)
                if (!Data.IsMap(CustomMapNames.Agartha))
                {
                    return true;
                }
                __instance.CanUse(PlayerControl.LocalPlayer.Data, out var canUse, out var _);
                if (!canUse)
                {
                    return false;
                }
                SuperNewRolesPlugin.Logger.LogInfo("実行！");
                SoundManager.Instance.PlaySound(ModHelpers.loadAudioClipFromResources("SuperNewRoles.Resources.Agartha.DoorSound.raw"), false,1.5f);
                if (DoorData.ContainsKey(__instance.MyDoor.Id))
                {
                    DoorData[__instance.MyDoor.Id]--;
                    SuperNewRolesPlugin.Logger.LogInfo("残り:" + DoorData[__instance.MyDoor.Id]);
                    if (DoorData[__instance.MyDoor.Id] <= 0)
                    {
                        __instance.MyDoor.SetDoorway(true);
                        DoorData[__instance.MyDoor.Id] = 10;
                    }
                } else
                {
                    DoorData[__instance.MyDoor.Id] = 9;
                }
                return false;
            }
        }
    }
}
