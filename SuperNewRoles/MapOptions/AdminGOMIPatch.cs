using System;
using System.Collections.Generic;
using System.Text;
using UnityEngine;
using HarmonyLib;

namespace SuperNewRoles.MapOptions
{
    public static class ChangeRoomArea
    {
        public static void ChangeAdmin(Transform Map)
        {
            Transform CountOverlay = Map.FindChild("CountOverlay");

            //GameObject.Destroy(CountOverlay.FindChild("halls_photos").gameObject);
            CountOverlay.FindChild("Ventilation").localPosition += new Vector3(9999,9999,9999);
            CountOverlay.FindChild("Hall of Portraits").localPosition += new Vector3(9999,9999,9999);/*
            CountOverlay.FindChild("Comms").localPosition = new Vector3(-2.25f, 2.36f, -20f);
            CountOverlay.FindChild("MedBay").localPosition = new Vector3(-2.1f, 0.75f, -20f);
            CountOverlay.FindChild("Reactor").localPosition = new Vector3(-4.5f, 1.4f, 0f);
            CountOverlay.FindChild("Laboratory").localPosition = new Vector3(4.5f, -4f, 0f);*/
        }
        public static Transform MapObject;
        public static void MinimapChange(MapBehaviour __instance)
        {
            MapObject = GameObject.Find("AirshipMap(Clone)").transform;
            ChangeRoomArea.ChangeAdmin(MapObject);
        }
    }
    public static class Patch
    {
        [HarmonyPatch(typeof(MapBehaviour), nameof(MapBehaviour.Awake))]
        class ChangeMapPatch
        {
            public static void Postfix(MapBehaviour __instance)
            {
                if (PlayerControl.GameOptions.MapId == 4)
                {
                    SuperNewRolesPlugin.Logger.LogInfo("マップ変更処理");
                    ChangeRoomArea.MinimapChange(__instance);
                }
            }
        }
    }
}
