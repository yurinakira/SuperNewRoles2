using System;
using System.Collections.Generic;
using System.Text;

namespace SuperNewRoles.CustomCommand
{
    public static class Patch
    {
        public static bool AddChat(PlayerControl source, string text)
        {
            string[] cmd = text.Split("\n");
            (string, string) cmds = new();
            if (FileManager.TryGet(cmd[0], ref cmds)) {
                string returnmsg = ParseMsg.Parse(source, cmds.Item1);
                new LateTask(()=>SuperNewRoles.Patch.AddChatPatch.SendCommand(source, returnmsg, cmds.Item2 != "" ? cmds.Item2 : source.Data.PlayerName),0f);
                return true;
            }
            return false;
        }
    }
}
