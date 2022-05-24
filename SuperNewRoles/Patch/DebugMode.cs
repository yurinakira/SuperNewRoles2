using BepInEx;
using BepInEx.Configuration;
using BepInEx.IL2CPP;
using HarmonyLib;
using Hazel;
using System.Security.Cryptography;
using System.Linq;
using System.Net;
using System.IO;
using System;
using System.Reflection;
using UnhollowerBaseLib;
using UnityEngine;
using SuperNewRoles.CustomOption;
using InnerNet;
using System.Collections;
using System.Collections.Generic;

namespace SuperNewRoles.Patch
{
    class DebugMode
    {
        [HarmonyPatch(typeof(MapConsole), nameof(MapConsole.Use))]
        public static class MapConsoleUsePatch
        {
            public static void Prefix(MapConsole __instance)
            {
                if (ConfigRoles.DebugMode.Value)
                {
                    SuperNewRolesPlugin.Logger.LogInfo("アドミンの場所(x):" + __instance.transform.position.x);
                    SuperNewRolesPlugin.Logger.LogInfo("アドミンの場所(y):" + __instance.transform.position.y);
                    SuperNewRolesPlugin.Logger.LogInfo("アドミンの場所(Z):" + __instance.transform.position.z);
                }
            }
        }
        [HarmonyPatch(typeof(KeyboardJoystick), nameof(KeyboardJoystick.Update))]
        public static class DebugManager
        {
            private static readonly System.Random random = new System.Random((int)DateTime.Now.Ticks);
            private static List<PlayerControl> bots = new List<PlayerControl>();
            public class LateTask
            {
                public string name;
                public float timer;
                public Action action;
                public static List<LateTask> Tasks = new List<LateTask>();
                public bool run(float deltaTime)
                {
                    timer -= deltaTime;
                    if (timer <= 0)
                    {
                        action();
                        return true;
                    }
                    return false;
                }
                public LateTask(Action action, float time, string name = "No Name Task")
                {
                    this.action = action;
                    this.timer = time;
                    this.name = name;
                    Tasks.Add(this);
                }
                public static void Update(float deltaTime)
                {
                    var TasksToRemove = new List<LateTask>();
                    Tasks.ForEach((task) => {
                        if (task.run(deltaTime))
                        {
                            TasksToRemove.Add(task);
                        }
                    });
                    TasksToRemove.ForEach(task => Tasks.Remove(task));
                }
            }
            public static bool IsHide = false;
            public static void Postfix(KeyboardJoystick __instance)
            {
                if (Input.GetKeyDown(KeyCode.B))
                {
                    IsHide = !IsHide;
                    if (AmongUsClient.Instance.AmHost)
                    {
                        if (IsHide)
                        {
                            HudManager.Instance.SetHudActive(false);
                        }
                        else
                        {
                            HudManager.Instance.SetHudActive(true);
                        }
                    }
                }
                if (!ConfigRoles.DebugMode.Value) return;

                // Spawn dummys
                if (Input.GetKey(KeyCode.LeftControl) && Input.GetKeyDown(KeyCode.G))
                {
                    var playerControl = UnityEngine.Object.Instantiate(AmongUsClient.Instance.PlayerPrefab);
                    var i = playerControl.PlayerId = (byte)GameData.Instance.GetAvailableId();

                    bots.Add(playerControl);
                    GameData.Instance.AddPlayer(playerControl);
                    AmongUsClient.Instance.Spawn(playerControl, -2, InnerNet.SpawnFlags.None);

                    int hat = random.Next(HatManager.Instance.allHats.Count);
                    int pet = random.Next(HatManager.Instance.allPets.Count);
                    int skin = random.Next(HatManager.Instance.allSkins.Count);
                    int visor = random.Next(HatManager.Instance.allVisors.Count);
                    int color = random.Next(Palette.PlayerColors.Length);
                    int nameplate = random.Next(HatManager.Instance.allNamePlates.Count);
                    var id = 0;
                    foreach (PlayerControl p in PlayerControl.AllPlayerControls)
                    {
                        SuperNewRolesPlugin.Logger.LogInfo(p.PlayerId);
                        if (id < p.PlayerId && p.PlayerId != 255)
                        {
                            SuperNewRolesPlugin.Logger.LogInfo("idセット:" + id);
                            id = p.PlayerId;
                        }
                    }
                    id++;
                    var bot = UnityEngine.Object.Instantiate(AmongUsClient.Instance.PlayerPrefab);
                    bot.PlayerId = (byte)id;
                    GameData.Instance.AddPlayer(bot);
                    AmongUsClient.Instance.Spawn(bot, -2, SpawnFlags.None);
                    bot.transform.position = PlayerControl.LocalPlayer.transform.position;
                    bot.NetTransform.enabled = true;
                    GameData.Instance.RpcSetTasks(bot.PlayerId, new byte[0]);

                    bot.RpcSetColor((byte)PlayerControl.LocalPlayer.CurrentOutfit.ColorId);
                    bot.RpcSetName(PlayerControl.LocalPlayer.name);
                    bot.RpcSetPet(PlayerControl.LocalPlayer.CurrentOutfit.PetId);
                    bot.RpcSetSkin(PlayerControl.LocalPlayer.CurrentOutfit.SkinId);
                    bot.RpcSetNamePlate(PlayerControl.LocalPlayer.CurrentOutfit.NamePlateId);
                }
                
                if (Input.GetKeyDown(KeyCode.I))
                {
                    MeetingRoomManager.Instance.AssignSelf(PlayerControl.LocalPlayer, null);
                    DestroyableSingleton<HudManager>.Instance.OpenMeetingRoom(PlayerControl.LocalPlayer);
                    PlayerControl.LocalPlayer.RpcStartMeeting(PlayerControl.LocalPlayer.Data);
                }
                if (Input.GetKeyDown(KeyCode.F))
                {
                    if (Default == 0) Default = Camera.main.orthographicSize;
                    Camera.main.orthographicSize = Default * 2.5f;
                    HudManager.Instance.UICamera.orthographicSize = Default * 2.5f;
                }
                if (Input.GetKeyDown(KeyCode.N))
                {
                    if (Default == 0) Default = Camera.main.orthographicSize;
                    Camera.main.orthographicSize = Default * 7f;
                    HudManager.Instance.UICamera.orthographicSize = Default * 7f;
                }
                if (Input.GetKeyDown(KeyCode.C))
                {
                    if (Default == 0) return;
                    Camera.main.orthographicSize = Default;
                    HudManager.Instance.UICamera.orthographicSize = Default;
                }
                if (Input.GetKeyDown(KeyCode.F10))
                {
                    BotManager.Spawn($"bot{(byte)GameData.Instance.GetAvailableId()}");                
                }
                if (Input.GetKeyDown(KeyCode.F11))
                {
                    BotManager.AllBotDespawn();
                }
            }
            public static float Default = 0;
            public static string RandomString(int length)
            {
                const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
                return new string(Enumerable.Repeat(chars, length)
                    .Select(s => s[random.Next(s.Length)]).ToArray());
            }
        }
        public static bool IsDebugMode() {
            var IsDebugModeBool = false;
            if (ConfigRoles.DebugMode.Value) {
                if (CustomOptions.IsDebugMode.getBool()) {
                    IsDebugModeBool = true;
                }
            }
            return IsDebugModeBool;
        }
    }
}
