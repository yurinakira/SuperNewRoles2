using System;
using System.Collections.Generic;
using System.Linq;
using Hazel;
using SuperNewRoles.Buttons;
using SuperNewRoles.CustomRPC;
using UnityEngine;
using HarmonyLib;
using SuperNewRoles.Mode;

namespace SuperNewRoles.Roles
{
    public static class Eliminator
    {
        public static void resetCoolDown()
        {
            HudManagerStartPatch.DoubleKillerMainKillButton.MaxTimer = RoleClass.Eliminator.KillCoolTime;
            HudManagerStartPatch.DoubleKillerMainKillButton.Timer = RoleClass.Eliminator.KillCoolTime;
        }
        public static void EndMeeting()
        {
            resetCoolDown();
            ResetScientist();
            ScientistEnd();
            ResetCoolDown();
        }
        public static void setPlayerOutline(PlayerControl target, Color color)
        {
            if (target == null || target.MyRend == null) return;

            target.MyRend().material.SetFloat("_Outline", 1f);
            target.MyRend().material.SetColor("_OutlineColor", color);
        }




        public static void ResetCoolDown()
        {
            float CoolTime;
            CoolTime = RoleClass.Eliminator.CoolTime;

            HudManagerStartPatch.EliminatorButton.MaxTimer = CoolTime;
            RoleClass.Eliminator.ButtonTimer = DateTime.Now;
        }
        public static void Start()
        {
            RoleClass.Eliminator.IsScientist = true;
            MessageWriter writer = AmongUsClient.Instance.StartRpcImmediately(PlayerControl.LocalPlayer.NetId, (byte)CustomRPC.CustomRPC.SetEliminatorRPC, Hazel.SendOption.Reliable, -1);
            writer.Write(true);
            writer.Write(CachedPlayer.LocalPlayer.PlayerId);
            AmongUsClient.Instance.FinishRpcImmediately(writer);
            CustomRPC.RPCProcedure.SetEliminatorRPC(true, CachedPlayer.LocalPlayer.PlayerId);
            Eliminator.ResetCoolDown();
        }
        public static void ResetScientist() { }
        public static void ScientistEnd()
        {
            RoleClass.Eliminator.IsScientist = false;
            MessageWriter writer = AmongUsClient.Instance.StartRpcImmediately(PlayerControl.LocalPlayer.NetId, (byte)CustomRPC.CustomRPC.SetEliminatorRPC, Hazel.SendOption.Reliable, -1);
            writer.Write(false);
            writer.Write(CachedPlayer.LocalPlayer.PlayerId);
            AmongUsClient.Instance.FinishRpcImmediately(writer);
            CustomRPC.RPCProcedure.SetEliminatorRPC(false, CachedPlayer.LocalPlayer.PlayerId);
            ResetScientist();
        }
        public static void setOpacity(PlayerControl player, float opacity, bool cansee)
        {
            // Sometimes it just doesn't work?
            var color = Color.Lerp(Palette.ClearWhite, Palette.White, opacity);
            try
            {
                if (player.MyRend() != null)
                    player.MyRend().color = color;

                if (player.GetSkin().layer != null)
                    player.GetSkin().layer.color = color;

                if (player.HatRend() != null)
                    player.HatRend().color = color;

                if (player.GetPet()?.rend != null)
                    player.GetPet().rend.color = color;

                if (player.GetPet()?.shadowRend != null)
                    player.GetPet().shadowRend.color = color;

                if (player.VisorSlot() != null)
                    player.VisorSlot().Image.color = color;

                if (player.nameText != null)
                    if (opacity == 0.1f)
                    {
                        player.nameText().text = "";
                    }
            }
            catch { }
        }
        [HarmonyPatch(typeof(PlayerPhysics), nameof(PlayerPhysics.FixedUpdate))]
        public static class PlayerPhysicsScientist
        {
            public static void Postfix(PlayerPhysics __instance)
            {
                if (AmongUsClient.Instance.GameState != AmongUsClient.GameStates.Started) return;
                if (!ModeHandler.isMode(ModeId.Default)) return;
                if (__instance.myPlayer.isRole(CustomRPC.RoleId.Eliminator))
                {
                    var Eliminator = __instance.myPlayer;
                    if (Eliminator == null || Eliminator.isDead()) return;
                    var ison = RoleClass.Eliminator.IsScientistPlayers.ContainsKey(__instance.myPlayer.PlayerId) && GameData.Instance && RoleClass.Eliminator.IsScientistPlayers[__instance.myPlayer.PlayerId];
                    bool canSee =
                        (__instance.myPlayer.isImpostor() && PlayerControl.LocalPlayer.isImpostor()) ||
                         PlayerControl.LocalPlayer.isDead() || !ison;

                    var opacity = canSee ? 0.1f : 0.0f;
                    if (ison)
                    {
                        opacity = Math.Max(opacity, 0);
                        Eliminator.MyRend().material.SetFloat("_Outline", 0f);
                    }
                    else
                    {
                        opacity = Math.Max(opacity, 1.5f);
                    }
                    setOpacity(Eliminator, opacity, canSee);
                }
            }
        }
    }
}

