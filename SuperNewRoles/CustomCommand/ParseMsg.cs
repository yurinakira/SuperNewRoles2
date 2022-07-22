using System;
using System.Collections.Generic;
using System.Text;

namespace SuperNewRoles.CustomCommand
{
    class ParseMsg
    {
        public static string Parse(PlayerControl source, string text)
        {            
            //自分系を置き換え
            text = text.Replace("{hostname}", CachedPlayer.LocalPlayer.Data.PlayerName)
                .Replace("{hostlevel}", CachedPlayer.LocalPlayer.Data.PlayerLevel.ToString())
                .Replace("{hostcolor}", FastDestroyableSingleton<TranslationController>.Instance.GetString(Palette.ColorNames[PlayerControl.LocalPlayer.CurrentOutfit.ColorId]))
                .Replace("{hostfriendcode}", CachedPlayer.LocalPlayer.Data.FriendCode);
            //実行者系を置き換え
            text = text.Replace("{sourcename}", source.Data.PlayerName)
                .Replace("{sourcelevel}", source.Data.PlayerLevel.ToString())
                .Replace("{sourcecolor}", FastDestroyableSingleton<TranslationController>.Instance.GetString(Palette.ColorNames[PlayerControl.LocalPlayer.CurrentOutfit.ColorId]))
                .Replace("{sourcefriendcode}", source.Data.FriendCode);
            //SNR系を置き換え
            text = text.Replace("{snrversion}", SuperNewRolesPlugin.VersionString)
                .Replace("{snrdiscord}", SuperNewRoles.Patch.MainMenuPatch.snrdiscordserver);

            return text;
        }
    }
}
