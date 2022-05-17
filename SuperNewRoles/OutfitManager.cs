using System;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

namespace SuperNewRoles
{
    public static class OutfitManager
    {
        public static void setOutfit(this PlayerControl pc, GameData.PlayerOutfit outfit, bool visible = true)
        {
            pc.Data.Outfits[PlayerOutfitType.Shapeshifted] = outfit;
            pc.CurrentOutfitType = PlayerOutfitType.Shapeshifted;
            SuperNewRolesPlugin.Logger.LogInfo("チェンジ");
            pc.RawSetName(outfit.PlayerName);
            pc.RawSetHat(outfit.HatId, outfit.ColorId);
            pc.RawSetVisor(outfit.VisorId);
            pc.RawSetColor(outfit.ColorId);
            ModHelpers.setSkinWithAnim(pc.MyPhysics, outfit.SkinId);

            // idk how to handle pets right now, so just not doing it
            // TODO: FIX PETS
            /*            if (!pc.Data.IsDead)
                        {
                            pc.CurrentPet.Data = HatManager.Instance.GetPetById(outfit.PetId);
                            pc.CurrentPet.transform.position = pc.transform.position;
                            pc.CurrentPet.Source = pc;
                            pc.CurrentPet.Visible = visible;
                            PlayerControl.SetPlayerMaterialColors(outfit.ColorId, pc.CurrentPet.rend);
                        }*/
        }
        public static void setLook(this PlayerControl target, String playerName, int colorId, string hatId, string visorId, string skinId, string petId)
        {
            SuperNewRolesPlugin.Logger.LogInfo("a");
            target.RawSetColor(colorId);
            SuperNewRolesPlugin.Logger.LogInfo("b");
            target.RawSetVisor(visorId);
            SuperNewRolesPlugin.Logger.LogInfo("c");
            target.RawSetHat(hatId, colorId);
            SuperNewRolesPlugin.Logger.LogInfo("d");
            target.RawSetName(ModHelpers.hidePlayerName(PlayerControl.LocalPlayer, target) ? "" : playerName);
            SuperNewRolesPlugin.Logger.LogInfo("e");

            SkinViewData nextSkin = DestroyableSingleton<HatManager>.Instance.GetSkinById(skinId).viewData.viewData;
            PlayerPhysics playerPhysics = target.MyPhysics;
            AnimationClip clip = null;
            var spriteAnim = playerPhysics.Skin.animator;
            var currentPhysicsAnim = playerPhysics.Animator.GetCurrentAnimation();
            SuperNewRolesPlugin.Logger.LogInfo("f");
            /*
            if (currentPhysicsAnim == playerPhysics.CurrentAnimationGroup.RunAnim) clip = nextSkin.RunAnim;
            else if (currentPhysicsAnim == playerPhysics.CurrentAnimationGroup.SpawnAnim) clip = nextSkin.SpawnAnim;
            else if (currentPhysicsAnim == playerPhysics.CurrentAnimationGroup.EnterVentAnim) clip = nextSkin.EnterVentAnim;
            else if (currentPhysicsAnim == playerPhysics.CurrentAnimationGroup.ExitVentAnim) clip = nextSkin.ExitVentAnim;
            else if (currentPhysicsAnim == playerPhysics.CurrentAnimationGroup.IdleAnim) clip = nextSkin.IdleAnim;
            else clip = nextSkin.IdleAnim;
            */
            SuperNewRolesPlugin.Logger.LogInfo("g");
            float progress = playerPhysics.Animator.m_animator.GetCurrentAnimatorStateInfo(0).normalizedTime;
            SuperNewRolesPlugin.Logger.LogInfo("III");
            playerPhysics.Skin.skin = nextSkin;
            SuperNewRolesPlugin.Logger.LogInfo("KKKK");
            /*
            if (playerPhysics.Skin.layer.material == DestroyableSingleton<HatManager>.Instance.PlayerMaterial)
                PlayerControl.SetPlayerMaterialColors(colorId, playerPhysics.Skin.layer);
            }*/
            SuperNewRolesPlugin.Logger.LogInfo("h");
            /*
            spriteAnim.Play(clip, 1f);
            spriteAnim.m_animator.Play("a", 0, progress % 1);
            spriteAnim.m_animator.Update(0f);

            if (target.CurrentPet) UnityEngine.Object.Destroy(target.CurrentPet.gameObject);
            target.CurrentPet = UnityEngine.Object.Instantiate<PetBehaviour>(DestroyableSingleton<HatManager>.Instance.GetPetById(petId).viewData.viewData);
            target.CurrentPet.transform.position = target.transform.position;
            target.CurrentPet.Source = target;
            SuperNewRolesPlugin.Logger.LogInfo("h");
            target.CurrentPet.Visible = target.Visible;
            PlayerControl.SetPlayerMaterialColors(colorId, target.CurrentPet.rend);
            */
            SuperNewRolesPlugin.Logger.LogInfo("i");
        }
        public static void changeToPlayer(this PlayerControl pc, PlayerControl target)
        {
            setOutfit(pc, target.Data.DefaultOutfit, target.Visible);
        }
        public static void resetChange(this PlayerControl pc)
        {
            changeToPlayer(pc, pc);
            pc.CurrentOutfitType = PlayerOutfitType.Default;
        }

    }
}
