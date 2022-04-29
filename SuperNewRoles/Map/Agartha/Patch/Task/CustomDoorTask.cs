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
                ClickObject.localScale *= 1.5f;
                ClickObject.localPosition = new Vector3(0.2f, 0.2f, 0);
                ClickObject.GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("DoorOpenMinigame_ClickObject");
                __instance.StatusText.transform.localPosition = new Vector3(1.05f, -0.925f, -4f);
                __instance.transform.FindChild("admin_sliderTop").gameObject.SetActive(false);
                __instance.transform.FindChild("admin_Wallet").gameObject.SetActive(false);
                __instance.transform.FindChild("admin_sliderBottom").GetComponent<SpriteRenderer>().sprite = ImageManager.AgarthagetSprite("DoorOpenMinigame_BackGround");
            }
        }
        public static PassiveButton DoorBtn;
        public static bool IsController;
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
                    __instance.StartCoroutine(__instance.CoStartClose(0f));
                }
                if (Controller.currentTouchType == Controller.TouchType.Joystick)
                {
                    IsController = true;
                    if (ConsoleJoystick.player.GetButtonDown(6))
                    {
                        SoundManager.Instance.PlaySound(ModHelpers.loadAudioClipFromResources("SuperNewRoles.Resources.Agartha.DoorSound.raw"), false, 1.5f);
                        DoorData[__instance.MyDoor.Id]--;
                    }
                }
                else
                {
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
                return true;
                if (DoorData.ContainsKey(__instance.MyDoor.Id))
                {
                    DoorData[__instance.MyDoor.Id]--;
                    if (DoorData[__instance.MyDoor.Id] <= 0)
                    {
                        __instance.MyDoor.SetDoorway(true);
                        DoorData[__instance.MyDoor.Id] = 0;
                    }
                } else
                {
                    DoorData[__instance.MyDoor.Id] = 0;
                    if (DoorData[__instance.MyDoor.Id] <= 0)
                    {
                        __instance.MyDoor.SetDoorway(true);
                        DoorData[__instance.MyDoor.Id] = 0;
                    }
                }
                return false;
            }
        }
    }
}
