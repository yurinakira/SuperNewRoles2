using System;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

namespace SuperNewRoles.Map.Agartha.Patch.Task
{
    public sealed class FossilMinigame : Minigame
    {
        private void Start()
        {
            SuperNewRolesPlugin.Logger.LogInfo("ミニゲームが呼び出された！");
        }
        private void Update()
        {
            MyNormTask.NextStep();
        }
    }
}
