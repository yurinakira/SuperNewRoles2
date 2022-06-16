using HarmonyLib;
using SuperNewRoles.CustomOption;
using SuperNewRoles.CustomRPC;
using SuperNewRoles.Intro;
using SuperNewRoles.Mode;
using SuperNewRoles.Roles;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TMPro;
using UnityEngine;

namespace SuperNewRoles.Patch
{
    public class SetNamesClass
    {
        public static Dictionary<int, string> AllNames = new Dictionary<int, string>();

        public static void SetPlayerNameColor(PlayerControl p, Color color)
        {
            if (p.IsBot()) return;
            p.nameText.color = color;
            if (MeetingHud.Instance)
            {
                foreach (PlayerVoteArea player in MeetingHud.Instance.playerStates)
                {
                    if (p.PlayerId == player.TargetPlayerId)
                    {
                        player.NameText.color = color;
                    }
                }
            }
        }
        public static void SetPlayerNameText(PlayerControl p, string text)
        {
            if (p.IsBot()) return;
            p.nameText.text = text;
            if (MeetingHud.Instance)
            {
                foreach (PlayerVoteArea player in MeetingHud.Instance.playerStates)
                {
                    if (player.TargetPlayerId == p.PlayerId)
                    {
                        player.NameText.text = text;
                        return;
                    }
                }
            }
        }
        public static void resetNameTagsAndColors()
        {
            Dictionary<byte, PlayerControl> playersById = ModHelpers.allPlayersById();

            foreach (var pro in PlayerInfos)
            {
                pro.Value.text = "";
            }
            foreach (var pro in MeetingPlayerInfos)
            {
                pro.Value.text = "";
            }
            foreach (PlayerControl player in CachedPlayer.AllPlayers)
            {
                player.nameText.text = ModHelpers.hidePlayerName(PlayerControl.LocalPlayer, player) ? "" : player.CurrentOutfit.PlayerName;
                if (PlayerControl.LocalPlayer.isImpostor() && (player.isImpostor() || player.isRole(RoleId.Egoist)))
                {
                    SetPlayerNameColor(player, RoleClass.ImpostorRed);
                }
                else
                {
                    SetPlayerNameColor(player, Color.white);
                }
            }
        }
        public static Dictionary<byte, TextMeshPro> PlayerInfos = new Dictionary<byte, TextMeshPro>();
        public static Dictionary<byte, TextMeshPro> MeetingPlayerInfos = new Dictionary<byte, TextMeshPro>();

        public static void SetPlayerRoleInfoView(PlayerControl p, Color roleColors, string roleNames)
        {
            if (p.IsBot()) return;
            bool commsActive = false;
            foreach (PlayerTask t in PlayerControl.LocalPlayer.myTasks)
            {
                if (t.TaskType == TaskTypes.FixComms)
                {
                    commsActive = true;
                    break;
                }
            }
            Transform playerInfoTransform = p.nameText.transform.parent.FindChild("Info");
            TMPro.TextMeshPro playerInfo = playerInfoTransform != null ? playerInfoTransform.GetComponent<TMPro.TextMeshPro>() : null;
            if (playerInfo == null)
            {
                playerInfo = UnityEngine.Object.Instantiate(p.nameText, p.nameText.transform.parent);
                playerInfo.fontSize *= 0.75f;
                playerInfo.gameObject.name = "Info";
            }

            // Set the position every time bc it sometimes ends up in the wrong place due to camoflauge
            playerInfo.transform.localPosition = p.nameText.transform.localPosition + Vector3.up * 0.5f;

            PlayerVoteArea playerVoteArea = MeetingHud.Instance?.playerStates?.FirstOrDefault(x => x.TargetPlayerId == p.PlayerId);
            Transform meetingInfoTransform = playerVoteArea != null ? playerVoteArea.NameText.transform.parent.FindChild("Info") : null;
            TMPro.TextMeshPro meetingInfo = meetingInfoTransform != null ? meetingInfoTransform.GetComponent<TMPro.TextMeshPro>() : null;
            if (meetingInfo == null && playerVoteArea != null)
            {
                meetingInfo = UnityEngine.Object.Instantiate(playerVoteArea.NameText, playerVoteArea.NameText.transform.parent);
                meetingInfo.transform.localPosition += Vector3.down * 0.1f;
                meetingInfo.fontSize = 1.5f;
                meetingInfo.gameObject.name = "Info";
            }

            // Set player name higher to align in middle
            if (meetingInfo != null && playerVoteArea != null)
            {
                var playerName = playerVoteArea.NameText;
                playerName.transform.localPosition = new Vector3(0.3384f, (0.0311f + 0.0683f), -0.1f);
            }
            string TaskText = "";
            if (!p.isImpostor())
            {
                try
                {
                    if (commsActive)
                    {
                        var all = TaskCount.TaskDateNoClearCheck(p.Data).Item2;
                        TaskText += ModHelpers.cs(Color.yellow, "(?/" + all + ")");
                    }
                    else
                    {
                        var (complate, all) = TaskCount.TaskDateNoClearCheck(p.Data);
                        TaskText += ModHelpers.cs(Color.yellow, "(" + complate + "/" + all + ")");
                    }
                }
                catch
                {

                }
            }
            string playerInfoText = "";
            string meetingInfoText = "";
            playerInfoText = $"{CustomOptions.cs(roleColors, roleNames)}{TaskText}";
            meetingInfoText = $"{CustomOptions.cs(roleColors, roleNames)}{TaskText}".Trim();
            playerInfo.text = playerInfoText;
            playerInfo.gameObject.SetActive(p.Visible);
            if (meetingInfo != null) meetingInfo.text = MeetingHud.Instance.state == MeetingHud.VoteStates.Results ? "" : meetingInfoText; p.nameText.color = roleColors;
        }
        public static void SetPlayerRoleInfo(PlayerControl p)
        {
            if (p.IsBot()) return;
            string roleNames = "";
            Color roleColors = Color.white;
            var role = p.getRole();
            if (role == CustomRPC.RoleId.DefaultRole || (role == CustomRPC.RoleId.Bestfalsecharge && p.isAlive()))
            {
                if (p.Data.Role.IsImpostor)
                {
                    roleNames = "ImpostorName";
                    roleColors = Roles.RoleClass.ImpostorRed;
                }
                else
                {
                    roleNames = "CrewMateName";
                    roleColors = Roles.RoleClass.CrewmateWhite;
                }
            }
            else if (role == RoleId.SchrodingerCat)
            {
                var introdate = Intro.IntroDate.GetIntroDate(role);
                roleNames = introdate.NameKey + "Name";
                switch (RoleClass.SchrodingerCat.Get(p))
                {
                    case RoleClass.SchrodingerCat.SchrodingerCatType.VoteDead:
                    case RoleClass.SchrodingerCat.SchrodingerCatType.Default:
                        roleColors = introdate.color;
                        break;
                    case RoleClass.SchrodingerCat.SchrodingerCatType.Impostor:
                        roleColors = RoleClass.ImpostorRed;
                        break;
                    case RoleClass.SchrodingerCat.SchrodingerCatType.Jackal:
                        roleColors = RoleClass.Jackal.color;
                        break;
                    case RoleClass.SchrodingerCat.SchrodingerCatType.Crewmate:
                        if (RoleClass.SchrodingerCat.IsChangeToSheriff)
                        {
                            roleColors = RoleClass.Sheriff.color;
                        }
                        else
                        {
                            roleColors = Color.white;
                        }
                        break;
                }
            }
            else
            {
                var introdate = Intro.IntroDate.GetIntroDate(role);
                roleNames = introdate.NameKey + "Name";
                roleColors = introdate.color;
            }
            SetPlayerRoleInfoView(p, roleColors, roleNames);
        }
        public static void SetPlayerNameColors(PlayerControl player)
        {
            var role = player.getRole();
            if (role == RoleId.DefaultRole || (role == RoleId.Bestfalsecharge && player.isAlive())) return;
            SetPlayerNameColor(player, Intro.IntroDate.GetIntroDate(role).color);
            Color color = Intro.IntroDate.GetIntroDate(role).color;
            if (role == RoleId.SchrodingerCat)
            {
                switch (RoleClass.SchrodingerCat.Get(player))
                {
                    case RoleClass.SchrodingerCat.SchrodingerCatType.Impostor:
                        color = RoleClass.ImpostorRed;
                        break;
                    case RoleClass.SchrodingerCat.SchrodingerCatType.Jackal:
                        color = RoleClass.Jackal.color;
                        break;
                    case RoleClass.SchrodingerCat.SchrodingerCatType.Crewmate:
                        if (RoleClass.SchrodingerCat.IsChangeToSheriff)
                        {
                            color = RoleClass.Sheriff.color;
                        }
                        else
                        {
                            color = Color.white;
                        }
                        break;
                }
            }
        }

        public static void SetPlayerRoleNames(PlayerControl player)
        {
            SetPlayerRoleInfo(player);
        }
        public static void QuarreledSet()
        {
            string suffix = ModHelpers.cs(RoleClass.Quarreled.color, "○");
            if (PlayerControl.LocalPlayer.IsQuarreled() && PlayerControl.LocalPlayer.isAlive())
            {
                PlayerControl side = PlayerControl.LocalPlayer.GetOneSideQuarreled();
                SetPlayerNameText(PlayerControl.LocalPlayer, PlayerControl.LocalPlayer.nameText.text + suffix);
                if (!side.Data.Disconnected)
                {
                    SetPlayerNameText(side, side.nameText.text + suffix);
                }
            }
            if (!PlayerControl.LocalPlayer.isAlive() && RoleClass.Quarreled.QuarreledPlayer != new List<List<PlayerControl>>())
            {
                foreach (List<PlayerControl> ps in RoleClass.Quarreled.QuarreledPlayer)
                {
                    foreach (PlayerControl p in ps)
                    {
                        if (!p.Data.Disconnected)
                        {
                            SetPlayerNameText(p, p.nameText.text + suffix);
                        }
                    }
                }
            }
        }
        public static void LoversSet()
        {
            string suffix = ModHelpers.cs(RoleClass.Lovers.color, " ♥");
            if (PlayerControl.LocalPlayer.IsLovers() && PlayerControl.LocalPlayer.isAlive())
            {
                PlayerControl side = PlayerControl.LocalPlayer.GetOneSideLovers();
                SetPlayerNameText(PlayerControl.LocalPlayer, PlayerControl.LocalPlayer.nameText.text + suffix);
                if (!side.Data.Disconnected)
                {
                    SetPlayerNameText(side, side.nameText.text + suffix);
                }
            }
            if ((PlayerControl.LocalPlayer.isDead() || PlayerControl.LocalPlayer.isRole(RoleId.God)) && RoleClass.Lovers.LoversPlayer != new List<List<PlayerControl>>())
            {
                foreach (List<PlayerControl> ps in RoleClass.Lovers.LoversPlayer)
                {
                    foreach (PlayerControl p in ps)
                    {
                        if (!p.Data.Disconnected)
                        {
                            SetPlayerNameText(p, p.nameText.text + suffix);
                        }
                    }
                }
            }
        }
        public static void DemonSet()
        {
            if (PlayerControl.LocalPlayer.isRole(RoleId.Demon) || PlayerControl.LocalPlayer.isDead() || PlayerControl.LocalPlayer.isRole(RoleId.God))
            {
                foreach (PlayerControl player in CachedPlayer.AllPlayers)
                {
                    if (Demon.IsViewIcon(player))
                    {
                        if (!player.nameText.text.Contains(ModHelpers.cs(RoleClass.Demon.color, " ▲")))
                        {
                            SetPlayerNameText(player, player.nameText.text + ModHelpers.cs(RoleClass.Demon.color, " ▲"));
                        }
                    }
                }
            }
        }
        public static void ArsonistSet()
        {
            if (PlayerControl.LocalPlayer.isRole(RoleId.Arsonist) || PlayerControl.LocalPlayer.isDead() || PlayerControl.LocalPlayer.isRole(RoleId.God))
            {
                foreach (PlayerControl player in CachedPlayer.AllPlayers)
                {
                    if (Arsonist.IsViewIcon(player))
                    {
                        if (!player.nameText.text.Contains(ModHelpers.cs(RoleClass.Arsonist.color, " §")))
                        {
                            SetNamesClass.SetPlayerNameText(player, player.nameText.text + ModHelpers.cs(RoleClass.Arsonist.color, " §"));
                        }
                    }
                }
            }
        }
        public static void CelebritySet()
        {
            if (RoleClass.Celebrity.ChangeRoleView)
            {
                foreach (PlayerControl p in RoleClass.Celebrity.ViewPlayers)
                {
                    SetPlayerNameColor(p, RoleClass.Celebrity.color);
                }
            }
            else
            {
                foreach (PlayerControl p in RoleClass.Celebrity.CelebrityPlayer)
                {
                    SetPlayerNameColor(p, RoleClass.Celebrity.color);
                }
            }
        }
    }
    public class SetNameUpdate
    {
        public static void Postfix(PlayerControl __instance)
        {
            SetNamesClass.resetNameTagsAndColors();
            RoleId LocalRole = PlayerControl.LocalPlayer.getRole();
            if (PlayerControl.LocalPlayer.isDead() && LocalRole != RoleId.NiceRedRidingHood)
            {
                foreach (PlayerControl player in CachedPlayer.AllPlayers)
                {
                    SetNamesClass.SetPlayerNameColors(player);
                    SetNamesClass.SetPlayerRoleNames(player);
                }
            }
            else if (LocalRole == RoleId.God)
            {
                foreach (PlayerControl player in CachedPlayer.AllPlayers)
                {
                    if (RoleClass.IsMeeting || player.isAlive())
                    {
                        SetNamesClass.SetPlayerNameColors(player);
                        SetNamesClass.SetPlayerRoleNames(player);
                    }
                }
            }
            else
            {
                if (Madmate.CheckImpostor(PlayerControl.LocalPlayer) ||
                    LocalRole == RoleId.MadKiller ||
                    LocalRole == RoleId.Marine ||
                    (RoleClass.Demon.IsCheckImpostor && LocalRole == RoleId.Demon)
                    )
                {
                    foreach (PlayerControl p in CachedPlayer.AllPlayers)
                    {
                        if (p.isImpostor())
                        {
                            SetNamesClass.SetPlayerNameColor(p, RoleClass.ImpostorRed);
                        }
                    }
                }
                if (PlayerControl.LocalPlayer.isImpostor())
                {
                    foreach (PlayerControl p in RoleClass.SideKiller.MadKillerPlayer)
                    {
                        SetNamesClass.SetPlayerNameColor(p, RoleClass.ImpostorRed);
                    }
                }
                if (LocalRole == RoleId.Jackal ||
                    LocalRole == RoleId.Sidekick ||
                    LocalRole == RoleId.TeleportingJackal ||
                    LocalRole == RoleId.JackalSeer ||
                    LocalRole == RoleId.SidekickSeer ||
                    JackalFriends.CheckJackal(PlayerControl.LocalPlayer))
                {
                    List<PlayerControl> Sets = RoleClass.Jackal.JackalPlayer;
                    Sets.AddRange(RoleClass.Jackal.SidekickPlayer);
                    Sets.AddRange(RoleClass.TeleportingJackal.TeleportingJackalPlayer);
                    Sets.AddRange(RoleClass.JackalSeer.JackalSeerPlayer);
                    Sets.AddRange(RoleClass.JackalSeer.SidekickSeerPlayer);
                    foreach (PlayerControl p in Sets)
                    {
                        if (p != PlayerControl.LocalPlayer)
                        {
                            SetNamesClass.SetPlayerRoleNames(p);
                            SetNamesClass.SetPlayerNameColors(p);
                        }
                    }
                    foreach (PlayerControl p in RoleClass.JackalSeer.FakeSidekickSeerPlayer)
                    {
                        if (p != PlayerControl.LocalPlayer)
                        {
                            SetNamesClass.SetPlayerNameColor(p, RoleClass.Jackal.color);
                            SetNamesClass.SetPlayerRoleInfoView(p, RoleClass.Jackal.color, Intro.IntroDate.SidekickIntro.NameKey + "Name");
                        }
                    }
                }
                if (!RoleClass.SchrodingerCat.IsChangeToJackalFriends)
                {
                    foreach (PlayerControl p in RoleClass.SchrodingerCat.SchrodingerCatPlayer)
                    {
                        if (RoleClass.SchrodingerCat.Get(p) == RoleClass.SchrodingerCat.SchrodingerCatType.Jackal)
                        {
                            SetNamesClass.SetPlayerNameColor(p, RoleClass.Jackal.color);
                            SetNamesClass.SetPlayerRoleNames(p);
                        }
                    }
                }
                SetNamesClass.SetPlayerRoleNames(PlayerControl.LocalPlayer);
                SetNamesClass.SetPlayerNameColors(PlayerControl.LocalPlayer);
            }
            SetNamesClass.ArsonistSet();
            SetNamesClass.DemonSet();
            SetNamesClass.CelebritySet();
            SetNamesClass.QuarreledSet();
            SetNamesClass.LoversSet();
            if (ModeHandler.isMode(ModeId.Default))
            {
                if (Sabotage.SabotageManager.thisSabotage == Sabotage.SabotageManager.CustomSabotage.CognitiveDeficit)
                {
                    foreach (PlayerControl p3 in CachedPlayer.AllPlayers)
                    {
                        if (p3.isAlive() && !Sabotage.CognitiveDeficit.main.OKPlayers.IsCheckListPlayerControl(p3))
                        {
                            if (PlayerControl.LocalPlayer.isImpostor())
                            {
                                if (!(p3.isImpostor() || p3.isRole(RoleId.MadKiller)))
                                {
                                    SetNamesClass.SetPlayerNameColor(p3, new Color32(18, 112, 214, byte.MaxValue));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}