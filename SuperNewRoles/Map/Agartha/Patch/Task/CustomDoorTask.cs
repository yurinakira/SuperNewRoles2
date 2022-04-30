using HarmonyLib;
using System;
using System.Collections.Generic;
using System.Text;
using UnityEngine;
using static UnityEngine.UI.Button;

namespace SuperNewRoles.Map.Agartha.Patch.Task
{
    public static class CustomDoorTask
    {
        [HarmonyPatch(typeof(DoorCardSwipeGame), nameof(DoorCardSwipeGame.Begin))]
        class DoorBeginPatch
        {
            public static void Postfix(DoorCardSwipeGame __instance, [HarmonyArgument(0)] PlayerTask task)
            {
                if (!DoorData.ContainsKey(__instance.MyDoor.Id))
                {
                    DoorData[__instance.MyDoor.Id] = 10;
                }
                __instance.StatusText.text = string.Format(ModTranslation.getString("残り{0}回クリック"), DoorData[__instance.MyDoor.Id]);
                DoorBtn = __instance.gameObject.AddComponent<PassiveButton>();
                DoorBtn.OnClick = new ButtonClickedEvent();
                DoorBtn.OnClick.AddListener((Action)(() =>
                {
                    if (!IsController)
                    {
                        SoundManager.Instance.PlaySound(ModHelpers.loadAudioClipFromResources("SuperNewRoles.Resources.Agartha.DoorSound.raw"), false, 1.5f);
                        DoorData[__instance.MyDoor.Id]--;
                        IsController = false;
                    }
                }));
                Transform ClickObject = __instance.col.transform;
                DoorBtn.Colliders = new List<Collider2D>() { __instance.col }.ToArray();
                ClickObject.localScale *= 3f;
                ClickObject.localPosition = new Vector3(0.2f, 0.2f, 0);
                ClickObject.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("DoorOpenMinigame_ClickObject");
                __instance.StatusText.transform.localPosition = new Vector3(1.05f, -0.925f, -4f);
                __instance.transform.FindChild("admin_Wallet").gameObject.SetActive(false);
                Hammer = __instance.transform.FindChild("admin_sliderTop");
                if (HammerSprite == null)
                {
                    HammerSprite = ImageManager.AgarthagetSprite("DoorOpenMinigame_Hammer");
                }
                Hammer.GetComponent<SpriteRenderer>().sprite = HammerSprite;
                Transform sliderbottom = __instance.transform.FindChild("admin_sliderBottom");
                sliderbottom.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("DoorOpenMinigame_BackGround");
                sliderbottom.localScale *= 1.5f;
                sliderbottom.localPosition -= new Vector3(0,0.5f,0);
                ControllerPosition = new Vector3(0,0,-51);
            }
        }
        public static PassiveButton DoorBtn;
        public static bool IsController;
        public static Sprite HammerSprite;
        public static Transform Hammer;
        private static Vector3 ControllerPosition;
        [HarmonyPatch(typeof(DoorCardSwipeGame), nameof(DoorCardSwipeGame.Update))]
        class DoorUpdatePatch
        {
            public static bool Prefix(DoorCardSwipeGame __instance)
            {
                if (__instance.StatusText.text != string.Format(ModTranslation.getString("残り{0}回クリック"), DoorData[__instance.MyDoor.Id])){
                    __instance.StatusText.text = string.Format(ModTranslation.getString("残り{0}回クリック"), DoorData[__instance.MyDoor.Id]);
                }
                if (DoorData[__instance.MyDoor.Id] <= 0)
                {
                    __instance.MyDoor.SetDoorway(true);
                    Hammer.gameObject.SetActive(false);
                    __instance.StartCoroutine(__instance.CoStartClose(0f));
                    DoorData[__instance.MyDoor.Id] = 10;
                }
                if (Controller.currentTouchType == Controller.TouchType.Joystick)
                {
                    IsController = true;
                    Hammer.localPosition = ControllerPosition;
                    ControllerPosition.x += ConsoleJoystick.player.GetAxis(2);
                    ControllerPosition.y += ConsoleJoystick.player.GetAxis(3);
                    if (ConsoleJoystick.player.GetButtonDown(6))
                    {
                        SoundManager.Instance.PlaySound(ModHelpers.loadAudioClipFromResources("SuperNewRoles.Resources.Agartha.DoorSound.raw"), false, 1.5f);
                        DoorData[__instance.MyDoor.Id]--;
                    }
                }
                else
                {
                    Hammer.position = Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x + 55f, Input.mousePosition.y - 5f, -51f));
                    IsController = false;
                }
                return false;
            }
        }
        public static Dictionary<int, int> DoorData;
        [HarmonyPatch(typeof(DoorConsole),nameof(DoorConsole.Use))]
        class UsePatch
        {
            public static bool Prefix(DoorConsole __instance)
            {
                if (!Data.IsMap(CustomMapNames.Agartha))
                {
                    return true;
                }
                __instance.CanUse(PlayerControl.LocalPlayer.Data, out var canUse, out var _);
                if (!canUse)
                {
                    return false;
                }
                return true;
                if (DoorData.ContainsKey(__instance.MyDoor.Id))
                {
                    DoorData[__instance.MyDoor.Id]--;
                    if (DoorData[__instance.MyDoor.Id] <= 0)
                    {
                        __instance.MyDoor.SetDoorway(true);
                        DoorData[__instance.MyDoor.Id] = 10;
                    }
                } else
                {
                    DoorData[__instance.MyDoor.Id] = 0;
                    if (DoorData[__instance.MyDoor.Id] <= 0)
                    {
                        __instance.MyDoor.SetDoorway(true);
                        DoorData[__instance.MyDoor.Id] = 10;
                    }
                }
                return false;
            }
        }
    }
}
