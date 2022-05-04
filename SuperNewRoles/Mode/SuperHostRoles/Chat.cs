
using HarmonyLib;
using InnerNet;
using SuperNewRoles.EndGame;
using SuperNewRoles.Helpers;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

namespace SuperNewRoles.Mode.SuperHostRoles
{
    class Chat
    {
        public static bool IsOldSHR = false;
        public static CustomGameOverReason? WinCond = null;
        public static List<PlayerControl> Winner = null;

        public static PlayerControl bot;
        public static void SendMyRoleChat()
        {
            foreach (PlayerControl p in PlayerControl.AllPlayerControls)
            {
                if (p.Data.Disconnected) continue;
                if (bot == null)
                {
                    bot = UnityEngine.Object.Instantiate(AmongUsClient.Instance.PlayerPrefab);
                    bot.PlayerId = 15;
                    GameData.Instance.AddPlayer(bot);
                    AmongUsClient.Instance.Spawn(bot, -2, SpawnFlags.None);
                    bot.transform.position = PlayerControl.LocalPlayer.transform.position;
                    bot.NetTransform.enabled = true;
                    GameData.Instance.RpcSetTasks(bot.PlayerId, new byte[0]);
                }

                bot.RpcSetColor((byte)PlayerControl.LocalPlayer.CurrentOutfit.ColorId);
                bot.RpcSetName(PlayerControl.LocalPlayer.name);
                bot.RpcSetPet(PlayerControl.LocalPlayer.CurrentOutfit.PetId);
                bot.RpcSetSkin(PlayerControl.LocalPlayer.CurrentOutfit.SkinId);
                bot.RpcSetNamePlate(PlayerControl.LocalPlayer.CurrentOutfit.NamePlateId);

                new LateTask(() => bot.NetTransform.RpcSnapTo(new Vector2(0, 15)), 0.2f, "Bot TP Task");
                new LateTask(() => { foreach (var pc in PlayerControl.AllPlayerControls) pc.RpcMurderPlayer(bot); }, 0.4f, "Bot Kill Task");
                new LateTask(() => { bot.RpcSendChat(p.PlayerId.ToString()); }, 0.6f);
                new LateTask(() => bot.Despawn(), 0.8f, "Bot Despawn Task");
            }
            
        }

        [HarmonyPatch(typeof(GameStartManager), nameof(GameStartManager.Start))]
        public class GameStartManagerStartPatch
        {
            public static void Postfix()
            {
                if (!AmongUsClient.Instance.AmHost) return;
                if (IsOldSHR && WinCond != null && AmongUsClient.Instance.AmHost)
                {
                    var Template = "最終結果\n勝利陣営:{0}"; 
                    if (WinCond == CustomGameOverReason.GodWin)
                    {
                        var players = "";
                        try
                        {
                            foreach (PlayerControl p in Winner)
                            {
                                if (players == "")
                                {
                                    players += p.nameText.text;
                                }
                                else
                                {
                                    players += "," + p.nameText.text;
                                }
                            }
                        }
                        catch { }
                        //new LateTask(() => {
                        PlayerControl.LocalPlayer.RpcSendChat(string.Format(Template + "\n勝者:{1}", "神(God)", players));
                        //}, 3f, "SendResult");
                    }
                    else if (WinCond == CustomGameOverReason.CrewmateWin)
                    {
                        //new LateTask(() => {
                        PlayerControl.LocalPlayer.RpcSendChat(string.Format(Template, "クルーメイト(Crewmate)"));
                        //}, 3f, "SendResult");
                    } else if(WinCond == CustomGameOverReason.ImpostorWin)
                    {
                        //new LateTask(() => {
                        PlayerControl.LocalPlayer.RpcSendChat(string.Format(Template, "インポスター(Impostor)"));
                        //}, 3f, "SendResult");
                    } else if(WinCond == CustomGameOverReason.JesterWin && Winner != null)
                    {
                        //new LateTask(() => {
                        PlayerControl.LocalPlayer.RpcSendChat(string.Format(Template + "\n勝者:{1}", "てるてる(Jester)", Winner[0].nameText.text));
                       // }, 3f, "SendResult");
                    } else if (WinCond == CustomGameOverReason.WorkpersonWin && Winner != null)
                    {
                        // new LateTask(() => {
                        PlayerControl.LocalPlayer.RpcSendChat(string.Format(Template + "\n勝者:{1}", "仕事人(Workperson)", Winner[0].nameText.text));
                        //}, 3f, "SendResult");
                    }
                }
                IsOldSHR = false;
                WinCond = null;
                Winner = null;
            }
        }
    }
}
