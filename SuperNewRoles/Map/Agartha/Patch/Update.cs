using HarmonyLib;
using SuperNewRoles.Sabotage;
using System;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

namespace SuperNewRoles.Map.Agartha.Patch
{
    class Update
    {
        [HarmonyPatch(typeof(ShipStatus),nameof(ShipStatus.CloseDoorsOfType))]
        class CloseDoorsOftype
        {
            public static void Postfix(ShipStatus __instance,[HarmonyArgument(0)] SystemTypes room)
            {
                if (SabotageManager.InfectedOverlayInstance == null)
                {
                    SetPosition.KeepTimes[room] = SabotageManager.SabotageMaxTime;
                } else {
                    ShipStatus.Instance.Systems[SystemTypes.Doors].TryCast<DoorsSystemType>().timers[room] = SabotageManager.SabotageMaxTime;
                }
            }
        }
        public static void FixedUpdate()
        {
            if (SabotageManager.InfectedOverlayInstance == null)
            {
                foreach (var data in SetPosition.KeepTimes)
                {
                    SetPosition.KeepTimes[data.Key] -= Time.fixedDeltaTime;
                }
                return;
            }
            if (SetPosition.KeepTimes.Count <= 0)
            {
                var doorsystemtype = ShipStatus.Instance.Systems[SystemTypes.Doors].TryCast<DoorsSystemType>();
                foreach (var data in SetPosition.KeepTimes)
                {
                    doorsystemtype.timers[data.Key] = data.Value;
                }
                SetPosition.KeepTimes = new Dictionary<SystemTypes, float>();
            }
            foreach (var data in SetPosition.CustomDoors)
            {
                float timer = ShipStatus.Instance.Systems[SystemTypes.Doors].TryCast<DoorsSystemType>().GetTimer(data.Key);
                float num = (SabotageManager.InfectedOverlayInstance.CanUseDoors ? (timer / 30f) : 1f);
                foreach (var data2 in data.Value)
                {
                    data2.Value.material.SetFloat("_Percent", num);
                }
            }
        }
    }
}
