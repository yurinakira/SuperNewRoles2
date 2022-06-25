using System;
using System.Collections.Generic;
using System.Text;
using UnityEngine;
using HarmonyLib;

namespace SuperNewRoles.Map.Agartha.Patch
{
    public static class ChangeRoomArea
    {
        public static void ApplyChanges(ShipStatus __instance)
        {
            if (Data.IsMap(CustomMapNames.Airship))
            {
                if (__instance.Type == ShipStatus.MapType.Ship)
                {
                    Transform MiraShip = GameObject.Find("Airship(Clone)").transform;
                    Agartha.Patch.ChangeRoomArea.Change(MiraShip);
                }
            }
        }
        public static void Change(Transform MiraShip)
        {
            //会議室
            Transform Cafe = MiraShip.FindChild("halls_photos");
            PolygonCollider2D CafeCol = Cafe.gameObject.GetComponent<PolygonCollider2D>();
            CafeCol.points = new Vector2[] { new Vector2(1f, 4.9f), new Vector2(3.45f, 4.9f), new Vector2(3.45f, -5.15f), new Vector2(-3.45f, -5.15f), new Vector2(-3.45f, -1.8f), new Vector2(-3.42f, -0.4f), new Vector2(-3.2f, 3.3f), new Vector2(-1.65f, 5f), new Vector2(-0.3f, 5f), new Vector2(1f, 4.9f) };
            /*
                        //コミュ
                        Transform Comms = MiraShip.FindChild("Comms");
                        PolygonCollider2D CommsCol = Comms.gameObject.AddComponent<PolygonCollider2D>();
                        CommsCol.isTrigger = true;
                        CommsCol.points = new Vector2[] { new Vector2(-18.5f, 19.5f), new Vector2(-18.5f, 16.7f), new Vector2(-13.5f, 16.7f), new Vector2(-13.5f, 19.5f), new Vector2(-18.5f, 19.5f) };
                        Comms.GetComponent<SkeldShipRoom>().roomArea = CommsCol;

                        //医務室
                        Transform MedBay = MiraShip.FindChild("MedBay");
                        PolygonCollider2D MedBayCol = MedBay.gameObject.AddComponent<PolygonCollider2D>();
                        MedBayCol.isTrigger = true;
                        MedBayCol.points = new Vector2[] { new Vector2(-19f, 15f), new Vector2(-19f, 12.2f), new Vector2(-12.5f, 12.2f), new Vector2(-12.5f, 15f), new Vector2(-19f, 15f) };
                        MedBay.GetComponent<SkeldShipRoom>().roomArea = MedBayCol;

                        //仕事場
                        Transform Reactor = MiraShip.FindChild("Reactor");
                        PolygonCollider2D ToolRoomCol = Reactor.gameObject.AddComponent<PolygonCollider2D>();
                        ToolRoomCol.isTrigger = true;
                        ToolRoomCol.points = new Vector2[] { new Vector2(-8.7f, 11.5f), new Vector2(-8.7f, 0f), new Vector2(-15f, 0f), new Vector2(-15f, 11.5f), new Vector2(-8.7f, 11.5f) };
                        Reactor.GetComponent<ReactorShipRoom>().roomArea = ToolRoomCol;

                        Transform Laboratory = MiraShip.FindChild("Laboratory");
                        PolygonCollider2D LaboratoryRoomCol = Laboratory.gameObject.AddComponent<PolygonCollider2D>();
                        LaboratoryRoomCol.isTrigger = true;
                        LaboratoryRoomCol.points = new Vector2[] { new Vector2(5.7f, -5.5f), new Vector2(5.7f, -10.5f), new Vector2(10.7f, -10.5f), new Vector2(10.7f, -5.5f), new Vector2(5.7f, -5.5f) };
                        Laboratory.GetComponent<SkeldShipRoom>().roomArea = LaboratoryRoomCol;*/
        }
        public static void ChangeAdmin(Transform Map)
        {
            Transform CountOverlay = Map.FindChild("CountOverlay");

            CountOverlay.FindChild("halls_photos").localPosition = new Vector3(10000000000000000.05f, 555555555555555555555.75f, 0f);/*
            CountOverlay.FindChild("Comms").localPosition = new Vector3(-2.25f, 2.36f, -20f);
            CountOverlay.FindChild("MedBay").localPosition = new Vector3(-2.1f, 0.75f, -20f);
            CountOverlay.FindChild("Reactor").localPosition = new Vector3(-4.5f, 1.4f, 0f);
            CountOverlay.FindChild("Laboratory").localPosition = new Vector3(4.5f, -4f, 0f);*/
        }
        public static Transform MapObject;
        public static void MinimapChange(MapBehaviour __instance)
        {
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
                if (Data.IsMap(CustomMapNames.Airship))
                {
                    SuperNewRolesPlugin.Logger.LogInfo("マップ変更処理");
                    Agartha.Patch.MiniMapPatch.MinimapChange(__instance);
                }
            }
        }
    }
}
