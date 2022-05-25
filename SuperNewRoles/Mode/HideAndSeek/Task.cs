using HarmonyLib;
using System;
using System.Collections.Generic;
using System.Text;

namespace SuperNewRoles.Mode.HideAndSeek
{
    class Task
    {
        public static void TaskCountHideAndSeek(GameData __instance)
        {
            __instance.TotalTasks = 0;
            __instance.CompletedTasks = 0;
            for (int i = 0; i < __instance.AllPlayers.Count; i++)
            {
                GameData.PlayerInfo playerInfo = __instance.AllPlayers[i];
                if ((playerInfo.Object.isAlive() || !main.DeadClearTask) && !playerInfo.Object.isImpostor())
                {
                    var (playerCompleted, playerTotal) = SuperNewRoles.Patch.TaskCount.TaskDate(playerInfo);
                    __instance.TotalTasks += playerTotal;
                    __instance.CompletedTasks += playerCompleted;
                }
            }
        }
    }
}
