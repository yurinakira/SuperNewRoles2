using HarmonyLib;

namespace SuperNewRoles.Patch
{
    public class HidePetFromOtherVisionPatch
    {


        [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.RpcSetPet))]
        public static class HidePetFromOtherVisionclass
        {
            public static string DefaultPetId;
            public static byte DefaultColor;
            public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] ref string PetId)
            {
                if (ConfigRoles.HidePetFromOtherVision.Value)
                {
                    SuperNewRolesPlugin.Logger.LogInfo("0-0");
                    HidePetFromOtherVision(PlayerControl.LocalPlayer);
                    SuperNewRolesPlugin.Logger.LogInfo("0-1");
                }
                else
                {
                    SuperNewRolesPlugin.Logger.LogInfo("0-2");
                    SuperNewRolesPlugin.Logger.LogInfo("ペットを表示します");
                    SuperNewRolesPlugin.Logger.LogInfo("0-3");
                }
                return false;
            }
            public static void HidePetFromOtherVision(PlayerControl player)
            {

                SuperNewRolesPlugin.Logger.LogInfo("1-1");
                DefaultPetId = player.Data.DefaultOutfit.PetId;
                SuperNewRolesPlugin.Logger.LogInfo("1-2");
                DefaultColor = (byte)player.Data.DefaultOutfit.ColorId;

                SuperNewRolesPlugin.Logger.LogInfo("1-3");

                /*  LateTaskをかけない場合[player.RpcSetPet]の部分で、処理が競合しループする。
                    その為、LateTaskを用いて処理を遅延した。*/
                new LateTask(() =>
                {
                    player.RpcSetPet("");
                    SuperNewRolesPlugin.Logger.LogInfo("1-4");
                }, 20f, "RpcSetPet");

                new LateTask(() =>
                {
                    RPCHidePet.RPCHidePetFromOtherVision(PlayerControl.LocalPlayer, DefaultPetId, DefaultColor);
                    SuperNewRolesPlugin.Logger.LogInfo("ペットを表示しません:" + "[" + DefaultPetId + "]" + "[" + DefaultColor + "]");
                }, 25f, "RawSetPet");

                return;
            }
        }
    }

    public static class RPCHidePet
    {
        public static void RPCHidePetFromOtherVision(this PlayerControl player, string PetID, int ColorID)
        {
            player.RawSetPet(PetID, ColorID);
            return;
        }

    }
}
