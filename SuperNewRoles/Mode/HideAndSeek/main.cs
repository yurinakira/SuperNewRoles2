using SuperNewRoles.EndGame;
using System;
using System.Collections.Generic;
using System.Text;
using UnityEngine;
using static SuperNewRoles.EndGame.CheckGameEndPatch;

namespace SuperNewRoles.Mode.HideAndSeek
{
    class main
    {
        public static bool EndGameCheck(ShipStatus __instance,PlayerStatistics statistics)
        {
            if (statistics.TotalAlive - statistics.TeamImpostorsAlive < 1 && statistics.TeamImpostorsAlive > 0) {
                //SuperNewRolesPlugin.Logger.LogInfo("ENDDED!!!:"+ statistics.TotalAlive - statistics.TeamImpostorsAlive + "、"+ statistics.TeamImpostorsAlive);
                __instance.enabled = false;
                ShipStatus.RpcEndGame(GameOverReason.ImpostorByKill, false);
                return true;
            } else if (GameData.Instance.TotalTasks <= GameData.Instance.CompletedTasks)
            {
                //SuperNewRolesPlugin.Logger.LogInfo("TASKEDD!");
                __instance.enabled = false;
                ShipStatus.RpcEndGame(GameOverReason.HumansByTask, false);
                return true;
            }
            else if(statistics.TeamImpostorsAlive <= 0){
                __instance.enabled = false;
                ShipStatus.RpcEndGame(GameOverReason.HumansDisconnect, false);
                return true;
            }
            else
            {
                return false;
            }
        }
        public static bool UseSabo;
        public static bool UseVent;
        public static bool DeadClearTask;
        public static void ClearAndReload() {
            UseSabo = Options.HASUseSabo.getBool();
            UseVent = Options.HASUseVent.getBool();
            DeadClearTask = Options.HASDeathTask.getBool();
        }
    }
}
