using System;
using System.Collections.Generic;
using System.Text;
using HarmonyLib;
using System.Net;
using System.Linq;
using SuperNewRoles.Buttons;

namespace SuperNewRoles.Roles.Neutral
{
    public class Akujo
    {
        public void Postfix()
        {
            if (RoleClass.Akujo.CanCreateKeepLimit == RoleClass.Akujo.KeepCreatedCount ||//Keep作成可能数がKeep作成数と等しいなら
            RoleClass.Akujo.CanCreateKeepLimit < RoleClass.Akujo.KeepCreatedCount)//また、Keep作成可能数がKeep作成数より少ないなら
            {
                RoleClass.Akujo.IsCanCreateKeep = false;
            }
        }
    }
}