using InnerNet;
using SuperNewRoles.CustomOption;
using SuperNewRoles.CustomRPC;
using SuperNewRoles.EndGame;
using SuperNewRoles.Helpers;
using SuperNewRoles.Patch;
using SuperNewRoles.Roles;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

namespace SuperNewRoles.Mode.SuperHostRoles
{
    public static class WinnerText
    {
        public static string getWinnerText(GameOverReason reason)
        {
            bool saboWin = reason == GameOverReason.ImpostorBySabotage;
            bool JesterWin = OnGameEndPatch.EndData == CustomGameOverReason.JesterWin;
            bool EgoistWin = OnGameEndPatch.EndData == CustomGameOverReason.EgoistWin;
            bool WorkpersonWin = OnGameEndPatch.EndData == CustomGameOverReason.WorkpersonWin;
            bool FalseChargesWin = OnGameEndPatch.EndData == CustomGameOverReason.FalseChargesWin;
            var text = "";
            Color color = Color.white;
            if (EndGameManagerSetUpPatch.IsHaison)
            {
                //bonusText = "jesterWin";
                text = "HAISON";
                color = Color.white;
            }
            else if (JesterWin)
            {
                //bonusText = "jesterWin";
                text = "JesterName";
                color = RoleClass.Jester.color;
            }
            else if (EgoistWin)
            {
                text = "EgoistName";
                color = RoleClass.Egoist.color;
            }
            else if (WorkpersonWin)
            {
                text = "WorkpersonName";
                color = RoleClass.Workperson.color;
            }
            else if (FalseChargesWin)
            {
                text = "FalseChargesName";
                color = RoleClass.FalseCharges.color;
            }
            else if (reason == GameOverReason.HumansByTask || reason == GameOverReason.HumansByVote || reason == GameOverReason.HumansDisconnect)
            {
                text = "CrewMateName";
                color = Palette.White;
            }
            else
            {
                text = "ImpostorName";
                color = RoleClass.ImpostorRed;
            }

            foreach (PlayerControl p in RoleClass.God.GodPlayer)
            {
                if (p.isAlive())
                {
                    var (complate, all) = TaskCount.TaskDateNoClearCheck(p.Data);
                    if (!RoleClass.God.IsTaskEndWin || complate >= all)
                    {
                        text = "GodName";
                        color = RoleClass.God.color;
                    }
                }
            }

            bool IsSingleTeam = CustomOptions.LoversSingleTeam.getBool();
            foreach (List<PlayerControl> plist in RoleClass.Lovers.LoversPlayer)
            {
                bool IsWinLovers = false;
                foreach (PlayerControl p in plist)
                {
                    if (p.isAlive())
                    {
                        IsWinLovers = true;
                    }
                }
                if (IsWinLovers && IsSingleTeam)
                {
                    text = "LoversName";
                    color = RoleClass.Lovers.color;
                }
            }

            var haison = false;
            if (text == "HAISON")
            {
                haison = true;
                text = ModTranslation.getString("HaisonName");
            }
            else
            {
                text = ModTranslation.getString(text);
            }
            bool IsOpptexton = false;
            foreach (PlayerControl player in RoleClass.Opportunist.OpportunistPlayer)
            {
                if (player.isAlive())
                {
                    if (!IsOpptexton && !haison)
                    {
                        IsOpptexton = true;
                        text = text + "&" + ModHelpers.cs(RoleClass.Opportunist.color, ModTranslation.getString("OpportunistName"));
                    }
                }
            }
            bool IsLovetexton = false;
            bool Temp1;
            text = ModHelpers.cs(color,text);
            if (!CustomOptions.LoversSingleTeam.getBool())
            {
                foreach (List<PlayerControl> PlayerList in RoleClass.Lovers.LoversPlayer)
                {
                    Temp1 = false;
                    foreach (PlayerControl player in PlayerList)
                    {
                        if (player.isAlive())
                        {
                            Temp1 = true;
                        }
                        if (Temp1)
                        {
                            if (!IsLovetexton && !haison)
                            {
                                IsLovetexton = true;
                                text = text + "&" + CustomOptions.cs(RoleClass.Lovers.color, "LoversName");
                            }
                        }
                    }
                }
            }
            if (!haison)
            {
                text = string.Format(text + " " + ModTranslation.getString("WinName"));
            }
            return text;
        }
        public static void SetWinnerBot(GameOverReason reason)
        {
            SuperNewRolesPlugin.Logger.LogInfo("\n\n\n\n");
            SuperNewRolesPlugin.Logger.LogInfo("スポーンスタート");
            CustomGameOverReason? enddata = OnGameEndPatch.EndData;
            if (enddata != null)
            {
                if (enddata == CustomGameOverReason.GodWin)
                {

                }
            }
            if (reason == GameOverReason.ImpostorByKill || 
                reason == GameOverReason.ImpostorBySabotage || 
                reason == GameOverReason.ImpostorByVote || 
                reason == GameOverReason.ImpostorDisconnect)
            {
                SuperNewRolesPlugin.Logger.LogInfo("インポスターウィン");
                foreach (PlayerControl p in PlayerControl.AllPlayerControls)
                {
                    if (!p.Data.Disconnected && (p.isRole(RoleId.MadJester) || p.isRole(RoleId.MadMate) || p.isRole(RoleId.MadMayor) || p.isRole(RoleId.MadStuntMan)))
                    {
                        SuperNewRolesPlugin.Logger.LogInfo("スポーン");
                        SpawnBot(p);
                        SuperNewRolesPlugin.Logger.LogInfo("スポーンﾖｼ!");
                    }
                }
            }
            SuperNewRolesPlugin.Logger.LogInfo("\n\n\n\n");
        }
        static PlayerControl bot;
        public static void SpawnBot(PlayerControl outfitplayer)
        {
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

            bot.RpcSetColor((byte)outfitplayer.CurrentOutfit.ColorId);
            bot.RpcSetName(outfitplayer.name);
            bot.RpcSetPet(outfitplayer.CurrentOutfit.PetId);
            bot.RpcSetSkin(outfitplayer.CurrentOutfit.SkinId);
            bot.RpcSetNamePlate(outfitplayer.CurrentOutfit.NamePlateId);

            //new LateTask(() => { SuperNewRolesPlugin.Logger.LogInfo("k"); ;SuperNewRolesPlugin.Logger.LogInfo("n"); }, 0.2f, "Bot TP Task");
            //new LateTask(() => { SuperNewRolesPlugin.Logger.LogInfo("d");  SuperNewRolesPlugin.Logger.LogInfo("s"); }, 0.4f, "Bot Set Role Task");
            //new LateTask(() => { foreach (var pc in PlayerControl.AllPlayerControls) pc.RpcMurderPlayer(bot); }, 0.6f, "Bot Kill Task");
            //new LateTask(() => bot.Despawn(), 3f, "Bot Despawn Task");
        }
        public static void SetWinnerText(GameOverReason reason)
        {
            SuperNewRolesPlugin.Logger.LogInfo("セットうぃなーてきすと");
            List<byte> players = new List<byte>();
            string winnertext = getWinnerText(reason);
            PlayerControl TopWinnerPlayer = null;
            if (reason == GameOverReason.HumansByTask || reason == GameOverReason.HumansByVote || reason == GameOverReason.HumansDisconnect)
            {
                foreach (PlayerControl p in PlayerControl.AllPlayerControls)
                {
                    if (p.Data.Role.TeamType == RoleTeamTypes.Crewmate)
                    {
                        players.Add(p.PlayerId);
                    }
                }
            } else
            {
                foreach (PlayerControl p in PlayerControl.AllPlayerControls)
                {
                    if (p.Data.Role.TeamType == RoleTeamTypes.Impostor)
                    {
                        players.Add(p.PlayerId);
                    }
                }
            }
            bool IsEnd = false;
            foreach (PlayerControl p in PlayerControl.AllPlayerControls)
            {
                if (IsEnd) break;
                if (players.Contains(p.PlayerId)) {
                    TopWinnerPlayer = p;
                    IsEnd = true;
                    break;
                }
            }
            foreach (var p in PlayerControl.AllPlayerControls)
            {
                SuperNewRolesPlugin.Logger.LogInfo("全部");
                if (!p.IsMod())
                {
                    SuperNewRolesPlugin.Logger.LogInfo("前");
                    if (players.Contains(p.PlayerId))
                    {
                        SuperNewRolesPlugin.Logger.LogInfo("自分セット:"+$"<size=300%>{winnertext}</size>\n\n\n\n\n\n\n{p.getDefaultName()}\n\n\n\n\n\n\n\n\n\n\n");
                        p.RpcSetNamePrivate($"<size=300%>{winnertext}</size>\n\n\n\n\n\n\n{p.getDefaultName()}\n\n\n\n\n\n\n\n\n\n\n",p);
                    } else
                    {
                        SuperNewRolesPlugin.Logger.LogInfo("セット前");
                        if (TopWinnerPlayer != null)
                        {
                            SuperNewRolesPlugin.Logger.LogInfo("セット！");
                            TopWinnerPlayer.RpcSetNamePrivate($"<size=300%>{winnertext}</size>\n\n\n\n\n\n\n{TopWinnerPlayer.getDefaultName()}\n\n\n\n\n\n\n\n\n\n\n", p);
                        }
                    }
                }
            }
            try
            {
                SetWinnerBot(reason);
            } catch(Exception e)
            {
                SuperNewRolesPlugin.Logger.LogError("ERROR:"+e);
            }
        }
    }
}
