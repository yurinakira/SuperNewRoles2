using BepInEx.IL2CPP.Utils;
using HarmonyLib;
using PowerTools;
using SuperNewRoles.Sabotage;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using static UnityEngine.UI.Button;

namespace SuperNewRoles.Map.Agartha.Patch
{
    public static class SetPosition
    {
        public static void ObjectsDestroy(Transform MiraShip)
        {
            Transform greenhousePanel = MiraShip.FindChild("Garden").FindChild("greenhousePanel");
            GameObject.Destroy(greenhousePanel.GetComponent<SpriteRenderer>());
            GameObject.Destroy(greenhousePanel.GetComponent<PolygonCollider2D>());
        }
        public static void MapPositionChange(InfectedOverlay __instance)
        {
            int i = 0;
            foreach(ButtonBehavior button in __instance.allButtons)
            {
                //コミュ
                if (i == 0)
                {
                    button.transform.localPosition = new Vector3(-3.15f, 4.3f, -1f);
                }
                //停電
                else if (i == 1) {
                    button.transform.localPosition = new Vector3(3.6f, 2f, -1f);
                }
                //O2
                else if (i == 2)
                {
                    button.transform.localPosition = new Vector3(-3.65f, -0.5f, -1f);

                }else if (i == 3)
                {
                    button.gameObject.SetActive(false);
                }
                SuperNewRolesPlugin.Logger.LogInfo(button.name+":"+i);
                i++;
            }
            var Listed = __instance.allButtons.ToList();
            Listed.RemoveAt(3);
            __instance.allButtons = Listed.ToArray();
            CustomDoors = new Dictionary<SystemTypes, Dictionary<ButtonBehavior, SpriteRenderer>>();
            foreach (var data in DoorSabotages)
            {
                ButtonBehavior button = InfectedOverlay.Instantiate(__instance.allButtons[0], __instance.allButtons[0].transform.parent);
                button.name = "DoorButton";
                 button.transform.localPosition = data.Key;
                button.spriteRenderer.sprite = Map.ImageManager.GetDoorSabotageButton();
                button.OnClick = new ButtonClickedEvent();

                button.OnClick.AddListener((Action)(() =>
                {
                    SuperNewRolesPlugin.Logger.LogInfo("くりっく");
                    if (SabotageManager.InfectedOverlayInstance.CanUseDoors && ShipStatus.Instance.Systems[SystemTypes.Doors].TryCast<DoorsSystemType>().GetTimer(data.Value) <= 0)
                    {
                        SuperNewRolesPlugin.Logger.LogInfo("つうか");
                        ShipStatus.Instance.RpcCloseDoorsOfType(data.Value);
                        ShipStatus.Instance.Systems[SystemTypes.Doors].TryCast<DoorsSystemType>().timers[data.Value] = SabotageManager.SabotageMaxTime;
                    }
                }));
                __instance.allButtons.AddItem(button);
                var dic = new Dictionary<ButtonBehavior, SpriteRenderer>();
                dic.Add(button, button.GetComponent<SpriteRenderer>());
                CustomDoors.Add(data.Value, dic);
            }
        }
        static Dictionary<Vector3, SystemTypes> DoorSabotages = new Dictionary<Vector3, SystemTypes>() {
            { new Vector3(-0.65f, 3.2f, 0f), SystemTypes.MeetingRoom },{ new Vector3(-3.12f, 3.675f, 0f), SystemTypes.Comms},
            { new Vector3(-3.12f, 2.95f, 0f), SystemTypes.MedBay },{ new Vector3(-4.78f, 3.6f, 0f), SystemTypes.Reactor},
            { new Vector3(-3.13f, 1.2f, 0f), SystemTypes.LifeSupp},{ new Vector3(-3.13f, 0.55f, 0f), SystemTypes.LockerRoom},
            { new Vector3(-4.78f, 1.15f, 0f), SystemTypes.Launchpad},{ new Vector3(-1.1f, 1.4f, 0f), SystemTypes.Admin},
            { new Vector3(-0.25f, 1.4f, 0f), SystemTypes.Security},{ new Vector3(0.88f, 1.375f, 0f), SystemTypes.Laboratory}
        };
        public static Dictionary<SystemTypes, float> KeepTimes;
        public static Dictionary<SystemTypes,Dictionary<ButtonBehavior,SpriteRenderer>> CustomDoors;
        public static PlainDoor CreateDoor(SystemTypes room,Vector3 position,Vector3? scale = null,int id = -1,int index = 3)
        {
            if (id == -1)
            {
                id = GetDoorAvailableId();
            }
            if (scale == null)
            {
                scale = new Vector3(1,1,1);
            }
            PlainDoor door = GameObject.Instantiate(MapLoader.Airship.AllDoors[index],miraship);
            door.transform.localScale = (Vector3)scale;
            door.transform.position = position;
            door.Id = id;
            door.Room = room;
            return door;
        }
        [HarmonyPatch(typeof(PlainDoor),nameof(PlainDoor.Start))]
        class start
        {
            public static void Postfix(PlainDoor __instance)
            {
                //__instance.GetComponent<SpriteRenderer>().sprite = ImageManager.Object_Door_Open;
            }
        }
        public static Transform miraship;
        public static void SetDoor()//Transform Miraship)
        {
            
            List<PlainDoor> doors = new List<PlainDoor>();
            doors.Add(CreateDoor(SystemTypes.MeetingRoom,new Vector3(13.45f, 20.45f, 7f),new Vector3(0.7f,0.75f,0.75f),0));
            doors.Add(CreateDoor(SystemTypes.Comms,new Vector3(0.1f, 20.2f, 4f),new Vector3(0.7f, 0.8f,1f),1));
            doors.Add(CreateDoor(SystemTypes.MedBay,new Vector3(0.1f, 15.45f, 4f), new Vector3(0.7f, 0.8f, 1f),2));
            doors.Add(CreateDoor(SystemTypes.Reactor,new Vector3(-6.215f, 17.8f, 4f), new Vector3(0.75f, 0.75f, 1f),3,0));//作業室
            doors.Add(CreateDoor(SystemTypes.Reactor,new Vector3(-9.775f, 11.875f, 4f), new Vector3(0.675f, 0.75f, 0.75f),4));//作業室
            doors.Add(CreateDoor(SystemTypes.LifeSupp,new Vector3(0.075f, 6.36f, 4f), new Vector3(0.69f, 0.8f, 1f),5));
            doors.Add(CreateDoor(SystemTypes.LockerRoom,new Vector3(0.085f, 1.75f, 4f), new Vector3(0.69f, 0.8f, 1f),6));//工具室
            doors.Add(CreateDoor(SystemTypes.Launchpad,new Vector3(-6.2f, 4.75f, 4f), new Vector3(0.75f, 1f, 1f),7,0));//倉庫
            doors.Add(CreateDoor(SystemTypes.Admin,new Vector3(7.95f, 5.35f, 4f), new Vector3(0.64f, 0.66f, 0.64f), 8, 0));
            doors.Add(CreateDoor(SystemTypes.Admin,new Vector3(7.1f, 6f, 4f), new Vector3(0.75f, 0.75f, 0.75f), 12));
            doors.Add(CreateDoor(SystemTypes.Security,new Vector3(18.3f, 5.4f, 0.5f), new Vector3(0.8f, 0.8f, 1), 9, 0));
            doors.Add(CreateDoor(SystemTypes.Security,new Vector3(19.2f, 5.4f, 0.5f), new Vector3(0.8f,0.8f,1), 10, 0));
            doors.Add(CreateDoor(SystemTypes.Laboratory,new Vector3(24.15f, 9.74f, 0.5f), new Vector3(0.7f, 0.9f, 1f), 11));
            doors.Add(CreateDoor(SystemTypes.Laboratory, new Vector3(22.24f, 1.625f, 7f), new Vector3(0.7f, 0.75f, 0.75f), 15));
            doors.Add(CreateDoor(SystemTypes.Electrical, new Vector3(22.9f, 20.45f, 7f), new Vector3(0.7f, 0.75f, 0.75f), 13));
            doors.Add(CreateDoor(SystemTypes.MeetingRoom, new Vector3(9.61f, 15.3376f, 4f), new Vector3(0.64f, 0.66f, 0.64f), 14, 0));
            ShipStatus.Instance.AllDoors = doors.ToArray();
        }
        public static int GetDoorAvailableId()
        {
            var id = 0;
            if (ShipStatus.Instance.AllDoors.Count == 0) return 0;
            while (true)
            {
                if (ShipStatus.Instance.AllDoors.All(v => v.Id != id)) return id;
                id++;
            }
        }
        public static void SetObject(Transform MiraShip)
        {
            Transform CommsTop = MiraShip.FindChild("Comms").FindChild("comms-top");
            CommsTop.gameObject.GetChildren().SetActiveAllObject("", false);
            CommsTop.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Object_ComputerTable");
            GameObject.Destroy(CommsTop.GetComponent<PolygonCollider2D>());
            CommsTop.gameObject.AddComponent<PolygonCollider2D>();
            CommsTop.position = new Vector3(-11.3f, 23f, 0.1f);
            CommsTop.localScale *= 0.5f;
            Transform CommsTop2 = GameObject.Instantiate(CommsTop,CommsTop.parent);
            CommsTop2.position = new Vector3(-7.8f, 23f, 0.1f);

            Transform Template = GameObject.Instantiate(MiraShip.FindChild("Office").FindChild("computerTableB"));
            //GameObject.Destroy(Template.GetComponent<PolygonCollider2D>());
            Template.gameObject.SetActive(true);
            Template.localScale *= 0.5f;

            Transform Labo_Object_fossil_1 = GameObject.Instantiate(Template, MiraShip);
            Labo_Object_fossil_1.position = new Vector3(19.8f, 3.225f, 0.1f);
            Labo_Object_fossil_1.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Object_fossil_1");
            Labo_Object_fossil_1.gameObject.AddComponent<PolygonCollider2D>();
            Labo_Object_fossil_1.name = "Object_fossil_1";

            Transform Labo_Object_fossil_2 = GameObject.Instantiate(Template, MiraShip);
            Labo_Object_fossil_2.position = new Vector3(20.9f, 3.25f, 0.1f);
            Labo_Object_fossil_2.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Object_fossil_2");
            Labo_Object_fossil_2.gameObject.AddComponent<PolygonCollider2D>();
            Labo_Object_fossil_2.name = "Object_fossil_2";

            Transform Labo_Object_kitchen_1 = GameObject.Instantiate(Template, MiraShip);
            Labo_Object_kitchen_1.position = new Vector3(20.7f, 9.2f, 0.1f);
            Labo_Object_kitchen_1.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Object_kitchen_1");
            Labo_Object_kitchen_1.gameObject.AddComponent<PolygonCollider2D>();
            Labo_Object_kitchen_1.name = "Object_kitchen_1";
            Labo_Object_kitchen_1.localScale *= 1.75f;

            Transform Labo_Object_shelves_1 = GameObject.Instantiate(Template, MiraShip);
            Labo_Object_shelves_1.position = new Vector3(22.8f, 9f, 0.1f);
            Labo_Object_shelves_1.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Object_shelves_1");
            Labo_Object_shelves_1.gameObject.AddComponent<PolygonCollider2D>();
            Labo_Object_shelves_1.name = "Object_shelves_1";
            Labo_Object_shelves_1.localScale *= 1.75f;

            Transform Labo_Object_LaboTable_1 = GameObject.Instantiate(Template, MiraShip);
            Labo_Object_LaboTable_1.position = new Vector3(21f, 7.25f, 0.1f);
            Labo_Object_LaboTable_1.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Object_LaboTable_1");
            Labo_Object_LaboTable_1.name = "Object_LaboTable_1";
            Labo_Object_LaboTable_1.localScale *= 0.75f;
            GameObject.Destroy(Labo_Object_LaboTable_1.GetComponent<PolygonCollider2D>());
            Labo_Object_LaboTable_1.gameObject.AddComponent<PolygonCollider2D>();

            Transform Object_brigde_front = GameObject.Instantiate(Template, MiraShip);
            Object_brigde_front.position = new Vector3(13.8f, -0.44f, -10f);
            Object_brigde_front.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Object_brigde_front");
            Object_brigde_front.name = "Object_brigde_front";
            Object_brigde_front.localScale *= 3.6f;
            GameObject.Destroy(Object_brigde_front.GetComponent<PolygonCollider2D>());

            Transform Object_brigde_download = GameObject.Instantiate(Template, MiraShip);
            Object_brigde_download.position = new Vector3(14.2f, 1f, 5f);
            Object_brigde_download.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("bridge_download");
            Object_brigde_download.name = "Object_brigde_download";
            Object_brigde_download.localScale *= 3.6f;
            GameObject.Destroy(Object_brigde_download.GetComponent<PolygonCollider2D>());


            Transform Object_Projecter = GameObject.Instantiate(Template, MiraShip);
            Object_Projecter.position = new Vector3(10.6f, 18.1f, 0.1f);
            GameObject.Destroy(Object_Projecter.GetComponent<PolygonCollider2D>());
            Object_Projecter.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Animation.pro_polygon");
            Object_Projecter.gameObject.AddComponent<PolygonCollider2D>();
            Object_Projecter.name = "Object_Projecter";
            CustomAnimation.Animation Object_Projecter_Animation = new CustomAnimation.Animation();
            Object_Projecter_Animation.Start(8, Object_Projecter);
            Object_Projecter_Animation.Sprites = CustomAnimation.LoadSprites.GetSpritesAgartha("SuperNewRoles.Resources.Agartha.Animation.pro", 32);
            Object_Projecter.localScale *= 2.5f;

            Transform Object_Electric = GameObject.Instantiate(Template, MiraShip);
            Object_Electric.position = new Vector3(21.35f, 15.47f, 0.1f);
            GameObject.Destroy(Object_Electric.GetComponent<PolygonCollider2D>());
            Object_Electric.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Animation.electric_0001");
            Object_Electric.gameObject.AddComponent<PolygonCollider2D>();
            Object_Electric.name = "Object_Electric";
            CustomAnimation.Animation Object_Electric_Animation = new CustomAnimation.Animation();
            Object_Electric_Animation.Start(10, Object_Electric);
            Object_Electric_Animation.Sprites = CustomAnimation.LoadSprites.GetSpritesAgartha("SuperNewRoles.Resources.Agartha.Animation.electric", 8);
            Object_Electric.localScale = new Vector3(1.75f, 1.75f, 1.75f);

            Transform Elec_Breaker = GameObject.Instantiate(Template, Object_Electric);
            Elec_Breaker.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Elec_breaker");
            Elec_Breaker.localScale *= 2;
            Elec_Breaker.localPosition = new Vector3(-1.4f, -0.7f, 3.9f);
            GameObject.Destroy(Elec_Breaker.GetComponent<PolygonCollider2D>());
            Elec_Breaker.gameObject.AddComponent<PolygonCollider2D>();
            Elec_Breaker.name = "Elec_Breaker";

            Transform Elec_Stair_1 = GameObject.Instantiate(Template, Object_Electric);
            Elec_Stair_1.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Elec_Stair_1");
            Elec_Stair_1.localScale = new Vector3(1f, 1f, 1f);
            Elec_Stair_1.localPosition = new Vector3(0.4675f, -1.65f, 3.9f);
            GameObject.Destroy(Elec_Stair_1.GetComponent<PolygonCollider2D>());
            Elec_Stair_1.name = "Elec_Stair_1";

            Transform Elec_Stair_2 = GameObject.Instantiate(Template, Object_Electric);
            Elec_Stair_2.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Elec_Stair_1");
            Elec_Stair_2.localScale = new Vector3(1f, 1f, 1f);
            Elec_Stair_2.localPosition = new Vector3(-0.25f, 1.675f, 3.9f);
            GameObject.Destroy(Elec_Stair_2.GetComponent<PolygonCollider2D>());
            Elec_Stair_2.name = "Elec_Stair_2";

            Transform Comms_Object_CommsTable = GameObject.Instantiate(Template, MiraShip);
            Comms_Object_CommsTable.position = new Vector3(-0.35f, 22.7f, 0.1f);
            Comms_Object_CommsTable.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Comms_Table");
            Comms_Object_CommsTable.name = "Object_CommsTable";
            Comms_Object_CommsTable.localScale = new Vector3(1.8f,1.8f,1.8f);
            GameObject.Destroy(Comms_Object_CommsTable.GetComponent<PolygonCollider2D>());
            Comms_Object_CommsTable.gameObject.AddComponent<PolygonCollider2D>();

            Transform Cafe_carpet = GameObject.Instantiate(Template, MiraShip);
            Cafe_carpet.position = new Vector3(13.5f, 14f, 0.1f);
            Cafe_carpet.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Cafe_carpet");
            Cafe_carpet.name = "Object_Cafe_carpet";
            Cafe_carpet.localScale = new Vector3(1.8f, 1.8f, 1.8f);
            GameObject.Destroy(Cafe_carpet.GetComponent<PolygonCollider2D>());


            for (int i = 0; i < 5; i++)
            {
                Transform Cafe_Chair = GameObject.Instantiate(Template, MiraShip);
                Cafe_Chair.position = new Vector3(i.IsEven() ? 15.2f : 14.3f, 18.7f - (i * 0.4f), 0.04f);
                Cafe_Chair.Rotate(new Vector3(0, 0, UnityEngine.Random.Range(-10f, 10f)));
                Cafe_Chair.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Chair1");
                Cafe_Chair.name = "Object_CafeChair1";
                Cafe_Chair.localScale = new Vector3(1.55f, 1.55f, 1.55f);
                GameObject.Destroy(Cafe_Chair.GetComponent<PolygonCollider2D>());
                Cafe_Chair.gameObject.AddComponent<PolygonCollider2D>();
            }

            for (int i = 1; i <= 5; i++)
            {
                Transform O2_bombe01 = GameObject.Instantiate(Template, MiraShip);
                switch (i)
                {
                    case 1:
                        O2_bombe01.position = new Vector3(-0.8f, 9.5f, 0.03f);
                        break;
                    case 2:
                        O2_bombe01.position = new Vector3(-1f, 8.9f, 0.02f);
                        break;
                    case 3:
                        O2_bombe01.position = new Vector3(-0.75f, 8.5f, 0.01f);
                        break;
                    case 4:
                        O2_bombe01.position = new Vector3(1.3f, 7.345f, 0.01f);
                        break;
                    case 5:
                        O2_bombe01.position = new Vector3(1.7f, 7.7f, 0.02f);
                        break;
                }
                var O2_bombepath = "oxygen.bombe0" + i.ToString();
                if (i == 4)
                {
                    O2_bombepath = "oxygen.bombeup";
                }
                else if (i == 5)
                {
                    O2_bombepath = "oxygen.bombe01";
                }
                O2_bombe01.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite(O2_bombepath);
                O2_bombe01.name = "object_bombe0" + i.ToString();
                O2_bombe01.localScale = new Vector3(1.55f, 1.55f, 1.55f);
                GameObject.Destroy(O2_bombe01.GetComponent<PolygonCollider2D>());
                O2_bombe01.gameObject.AddComponent<PolygonCollider2D>();
            }

            for (int i = 1; i <= 4; i++)
            {
                Transform O2_can01 = GameObject.Instantiate(Template, MiraShip);
                switch (i)
                {
                    case 1:
                        O2_can01.position = new Vector3(-3.15f, 9.5f, 0.13f);
                        break;
                    case 2:
                        O2_can01.position = new Vector3(-3.1f, 9.1f, 0.1f);
                        break;
                    case 3:
                        O2_can01.position = new Vector3(-2.8f, 8.8f, 0.09f);
                        break;
                    case 4:
                        O2_can01.position = new Vector3(-2.85f, 8.4f, 0.08f);
                        break;
                }
                var O2_canpath = "oxygen.can0" + i.ToString();
                if (i == 4)
                {
                    O2_canpath = "oxygen.can01";
                }
                O2_can01.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite(O2_canpath);
                O2_can01.name = "object_can0" + i.ToString();
                O2_can01.localScale = new Vector3(1.55f, 1.55f, 1.55f);
                GameObject.Destroy(O2_can01.GetComponent<PolygonCollider2D>());
                O2_can01.gameObject.AddComponent<PolygonCollider2D>();
            }

            Transform O2_shelf_anything = GameObject.Instantiate(Template, MiraShip);
            O2_shelf_anything.position = new Vector3(1.9f, 9.5f, 0.1f);
            O2_shelf_anything.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("oxygen.shelf_anything");
            O2_shelf_anything.name = "O2_shelf_anything";
            O2_shelf_anything.localScale *= 3.8f;
            GameObject.Destroy(O2_shelf_anything.GetComponent<PolygonCollider2D>());
            O2_shelf_anything.gameObject.AddComponent<PolygonCollider2D>();

            Transform Object_fence_1 = GameObject.Instantiate(Template,MiraShip);
            Object_fence_1.position = new Vector3(14.85f, 22.03f, -2f);
            Object_fence_1.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Object_fence_1");
            Object_fence_1.name = "Object_fence_1";
            Object_fence_1.localScale = new Vector3(1.81f,1.81f,1.81f);
            GameObject.Destroy(Object_fence_1.GetComponent<PolygonCollider2D>());

            Transform Object_fence_2 = GameObject.Instantiate(Template, MiraShip);
            Object_fence_2.position = new Vector3(21.45f, -0.4f, -2f);
            Object_fence_2.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Object_fence_2");
            Object_fence_2.name = "Object_fence_2";
            Object_fence_2.localScale = new Vector3(1.8f,1.8f,1.8f);
            GameObject.Destroy(Object_fence_2.GetComponent<PolygonCollider2D>());

            Transform Object_fence_3 = GameObject.Instantiate(Template, MiraShip);
            Object_fence_3.position = new Vector3(7.05f, -0.4f, -2f);
            Object_fence_3.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Object_fence_3");
            Object_fence_3.name = "Object_fence_3";
            Object_fence_3.localScale *= 3.8f;
            GameObject.Destroy(Object_fence_3.GetComponent<PolygonCollider2D>());

            Transform Object_fence_4 = GameObject.Instantiate(Template, MiraShip);
            Object_fence_4.position = new Vector3(0.425f, 16.56f, -2f);
            Object_fence_4.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Object_fence_4");
            Object_fence_4.name = "Object_fence_4";
            Object_fence_4.localScale = new Vector3(1.81f, 1.81f, 1.81f);
            GameObject.Destroy(Object_fence_4.GetComponent<PolygonCollider2D>());

            GameObject.Destroy(Template.gameObject);
            Template = null;

        }
        private static List<Vector3> DummyPositions = new List<Vector3>() { new Vector3(10.7f, 7.1f, 0f),new Vector3(11.8f, 15.6f, 0f),new Vector3(-0.2f, 8.5f, 0f),new Vector3(13.7f, 0.38f, 0f),new Vector3(20.6f, 13.1f, 0f),new Vector3(-10.7f, 16f, 0f) };
        public static void SetDummy()
        {
            new LateTask(() =>
            {
                for (int i = 1; i < 7; i++)
                {
                    if (DummyPositions.Count >= i)
                    {
                        GameObject obj = GameObject.Find(TranslationController.Instance.GetString(StringNames.Dummy) + " " + i.ToString());
                        obj.transform.position = DummyPositions[i - 1];
                    }
                }
            }, 0f, "SetDummyPosition");
        }
        public static void AddCamera(this Transform Sec,StringNames name,Vector3 pos)
        {
            var referenceCamera = Sec.FindChild("camoff").GetComponent<SurvCamera>();
            byte[] buff = new byte[sizeof(float) * 2];
            Buffer.BlockCopy(BitConverter.GetBytes(pos.x), 0, buff, 0 * sizeof(float), sizeof(float));
            Buffer.BlockCopy(BitConverter.GetBytes(pos.y), 0, buff, 1 * sizeof(float), sizeof(float));
            Vector3 position = Vector3.zero;
            position.x = BitConverter.ToSingle(buff, 0 * sizeof(float));
            position.y = BitConverter.ToSingle(buff, 1 * sizeof(float));
            var camera = UnityEngine.Object.Instantiate<SurvCamera>(referenceCamera,miraship);
            camera.transform.position = new Vector3(position.x, position.y, referenceCamera.transform.position.z - 1f);
            camera.CamName = $"Security Camera";
            //camera.Offset = new Vector3(0f, 0f, camera.Offset.z);
            camera.NewName = name;
            //camera.transform.localRotation = new Quaternion(0, 0, 1, 1); // Polus and Airship 
            List<SurvCamera> camlist = ShipStatus.Instance.AllCameras.ToList();
            camlist.Add(camera);
            ShipStatus.Instance.AllCameras = camlist.ToArray();
        }
        public static void SetCamera()
        {
            //カメラ生成
            Transform Sec = MapLoader.AirshipObject.transform.FindChild("Security");
            Transform newcam = UnityEngine.Object.Instantiate(Sec.FindChild("task_cams"), miraship);
            newcam.transform.position = new Vector3(16.3f, 7.8f, 0.1f);
            newcam.localScale = new Vector3(2.25f, 1.75f, 1.75f);
            GameObject.Destroy(newcam.GetComponent<PolygonCollider2D>());
            newcam.gameObject.AddComponent<PolygonCollider2D>();
            newcam.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("Security_Camera");
            Sec.AddCamera(StringNames.ConfirmUnlinkAccount, new Vector3(-0.9f, 19.31f, 0f));
            Sec.AddCamera(StringNames.ContinueOffline, new Vector3(-0.2f, 4.5f, 0f));
            Sec.AddCamera(StringNames.MeetingRoom, new Vector3(7.3f, 15f, 0f));
            Sec.AddCamera(StringNames.Laboratory, new Vector3(19.55f, 7.5f, 0f));
        }
        public static int GetAvailableId()
        {
            var id = 0;
            if (ShipStatus.Instance.AllVents.Count == 0) return 0;
            while (true)
            {
                if (ShipStatus.Instance.AllVents.All(v => v.Id != id)) return id;
                id++;
            }
        }
        public static Vent SetUpVent(this Transform ventobj)
        {
            Vent vent = ventobj.gameObject.GetComponent<Vent>();
            SetUpVent(vent);
            var allVents = ShipStatus.Instance.AllVents.ToList();
            allVents.Add(vent);
            ShipStatus.Instance.AllVents = allVents.ToArray();
            return vent;

        }
        public static void SetUpVent(this Vent vent)
        {
            vent.Id = GetAvailableId();
        }
        public static void SetVent(Transform Miraship)
        {
            ShipStatus.Instance.AllVents = new List<Vent>().ToArray();
            Transform AdminVentObject = Miraship.FindChild("Admin").FindChild("AdminVent");
            Vent AdminVent = SetUpVent(AdminVentObject);

            Transform Locker = Miraship.FindChild("Locker");
            Locker.gameObject.GetChildren().SetActiveAllObject("LockerVent", false);
            Transform LockerVentObject = Locker.FindChild("LockerVent");
            //LockerVentObject.name = "SecurityVent";
            Vent SecurityVent = SetUpVent(LockerVentObject);

            Transform Reactor = Miraship.FindChild("Reactor");
            Reactor.gameObject.GetChildren().SetActiveAllObject("ReactorVent", false);
            Transform ReactorVentObject = Reactor.FindChild("ReactorVent");
            //ReactorVentObject.name = "CommunityVent";
            ReactorVentObject.gameObject.SetActive(true);
            Vent CommunityVent = SetUpVent(ReactorVentObject);

            Transform ToolVentObject = Miraship.FindChild("Office").FindChild("OfficeVent");
            //ToolVentObject.name = "ToolVent";
            ToolVentObject.gameObject.SetActive(true);
            Vent ToolRoomVent = SetUpVent(ToolVentObject);

            Transform O2VentObject = Miraship.FindChild("MedBay").FindChild("MedVent");
            //O2VentObject.name = "O2Vent";
            Vent O2RoomVent = SetUpVent(O2VentObject);

            Transform MedbayVentObject = Miraship.FindChild("Garden").FindChild("AgriVent");
            //MedbayVentObject.name = "MedbayVent";
            Vent MedbayRoomVent = SetUpVent(MedbayVentObject);

            Transform WareHouseVentObject = Miraship.FindChild("LaunchPad").FindChild("LaunchVent");
            //WareHouseVentObject.name = "WareHouseVent";
            Vent WareHouseVent = SetUpVent(WareHouseVentObject);

            Transform WorkRoomVentObject = Miraship.FindChild("Cafe").FindChild("BalconyVent");
            //WorkRoomVentObject.name = "WorkRoomVent";
            WorkRoomVentObject.gameObject.SetActive(true);
            Vent WorkRoomVent = SetUpVent(WorkRoomVentObject);

            Transform MeetingRoomVentObject = Miraship.FindChild("Decontam").FindChild("DeconVent");
            //WorkRoomVentObject.name = "WorkRoomVent";
            Vent MeetingRoomVent = SetUpVent(MeetingRoomVentObject);

            Transform ElecRoomVentObject = Miraship.FindChild("Laboratory").FindChild("LabVent");
            //WorkRoomVentObject.name = "WorkRoomVent";
            Vent ElecRoomVent = SetUpVent(ElecRoomVentObject);

            Transform LaboVentObject = Miraship.FindChild("SkyBridge").FindChild("YHallRightVent");
            Vent LaboRoomVent = SetUpVent(LaboVentObject);

            AdminVent.Right = SecurityVent;
            AdminVent.Left = null;
            AdminVent.Center = null;

            SecurityVent.Right = AdminVent;
            SecurityVent.Left = null;
            SecurityVent.Center = null;

            CommunityVent.Right = null;
            CommunityVent.Left = null;
            CommunityVent.Center = null;

            ToolRoomVent.Right = null;
            ToolRoomVent.Left = null;
            ToolRoomVent.Center = null;

            O2RoomVent.Right = MedbayRoomVent;
            O2RoomVent.Left = null;
            O2RoomVent.Center = null;

            MedbayRoomVent.Right = O2RoomVent;
            MedbayRoomVent.Left = null;
            MedbayRoomVent.Center = null;

            WareHouseVent.Right = WorkRoomVent;
            WareHouseVent.Left = null;
            WareHouseVent.Center = null;

            WorkRoomVent.Right = WareHouseVent;
            WorkRoomVent.Left = null;
            WorkRoomVent.Center = null;

            MeetingRoomVent.Right = ElecRoomVent;
            MeetingRoomVent.Left = LaboRoomVent;
            MeetingRoomVent.Center = null;

            ElecRoomVent.Right = MeetingRoomVent;
            ElecRoomVent.Left = LaboRoomVent;
            ElecRoomVent.Center = null;

            LaboRoomVent.Right = MeetingRoomVent;
            LaboRoomVent.Left = ElecRoomVent;
            LaboRoomVent.Center = null;

            AdminVentObject.transform.position = new Vector3(12.3f, 4f, 0.1f);
            AdminVentObject.localScale = new Vector3(1.2f, 1.2f, 1.2f);

            LockerVentObject.transform.position = new Vector3(15.3f, 4f, 0.1f);
            LockerVentObject.localScale = new Vector3(1.2f, 1.2f, 1.2f);

            ReactorVentObject.transform.position = new Vector3(1.75f, 21f, 0.1f);
            ReactorVentObject.localScale = new Vector3(1.2f, 1.2f, 1.2f);

            ToolVentObject.transform.position = new Vector3(2.35f, -0.65f, 0.1f);
            ToolVentObject.localScale = new Vector3(1.2f, 1.2f, 1.2f);

            O2VentObject.transform.position = new Vector3(2.35f, 7.45f, 0.1f);
            O2VentObject.localScale = new Vector3(1.2f, 1.2f, 1.2f);

            MedbayVentObject.transform.position = new Vector3(2.35f, 12.65f, 0.1f);
            MedbayVentObject.localScale = new Vector3(1.2f, 1.2f, 1.2f);

            WareHouseVentObject.transform.position = new Vector3(-9.5f, 0.1f, 0.1f);
            WareHouseVentObject.localScale = new Vector3(1.2f, 1.2f, 1.2f);

            new LateTask(() =>
            {
                WorkRoomVentObject.transform.position = new Vector3(-9.5f, 22.9f, 0.1f);
                WorkRoomVentObject.localScale = new Vector3(1.2f, 1.2f, 1.2f);
            }, 0.05f);

            MeetingRoomVentObject.transform.position = new Vector3(15.8f, 11.5f, 0.1f);
            MeetingRoomVentObject.localScale = new Vector3(1.2f, 1.2f, 1.2f);

            ElecRoomVentObject.transform.position = new Vector3(18.9f, 11.65f, 0.1f);
            ElecRoomVentObject.localScale = new Vector3(1.2f, 1.2f, 1.2f);

            LaboVentObject.transform.position = new Vector3(24.3f, 8.6f, 0.1f);
            LaboVentObject.localScale = new Vector3(1.2f, 1.2f, 1.2f);
        }
    }
}
