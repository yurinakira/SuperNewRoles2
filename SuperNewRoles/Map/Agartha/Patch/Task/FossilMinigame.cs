using System;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

namespace SuperNewRoles.Map.Agartha.Patch.Task
{
    public static class FossilMinigame
    {
        public static Sprite BackGroundSprite;
        public static void Start(Minigame minigame,NormalPlayerTask task)
        {
            if (BackGroundSprite == null)
            {
                BackGroundSprite = ImageManager.AgarthagetSprite("Task.FossilMinigame_BackGround");
            }
            SuperNewRolesPlugin.Logger.LogInfo("すたーと！");
        }
    }
}
