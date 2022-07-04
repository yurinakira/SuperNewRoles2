using HarmonyLib;

namespace SuperNewRoles.Patch
{
    public class HidePetFromOtherVisionPatch
    {

        public static class HidePetFromOtherVisionclass
        {
            public static string DefaultPet;
            public static byte DefaultColor;

             [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.RpcSetPet))]
            public static void RPCHidePetFromOtherVision()
            {
                if (ConfigRoles.HidePetFromOtherVision.Value)
                {
                    var Player = PlayerControl.LocalPlayer;

                    DefaultPet = PlayerControl.LocalPlayer.Data.DefaultOutfit.PetId;
                    DefaultColor = (byte)PlayerControl.LocalPlayer.Data.DefaultOutfit.ColorId;

                    Player.RpcSetPet("");
                    RPCHidePet.RPCHidePetFromOtherVision(Player, DefaultPet, DefaultColor);

                    SuperNewRolesPlugin.Logger.LogInfo("ペットを表示しません" + DefaultPet + DefaultColor);
                }
                else
                {
                    SuperNewRolesPlugin.Logger.LogInfo("ペットを表示します");
                }
            }
        }
    }

    public static class RPCHidePet
    {
        public static void RPCHidePetFromOtherVision(this PlayerControl player, string PetID, int ColorID)
        {
            player.RawSetPet(PetID, ColorID);
        }
    }
}
