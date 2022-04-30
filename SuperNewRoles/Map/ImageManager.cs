using System;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

namespace SuperNewRoles.Map
{
    public static class ImageManager
    {
        private static Sprite DoorSabotageButton;
        public static Sprite GetDoorSabotageButton()
        {
            if (DoorSabotageButton != null) return DoorSabotageButton;
            DoorSabotageButton = ModHelpers.loadSpriteFromResources("SuperNewRoles.Resources.DoorSabotageButton.png", 115f);
            return DoorSabotageButton;
        }
    }
}
