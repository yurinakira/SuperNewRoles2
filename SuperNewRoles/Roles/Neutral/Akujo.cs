using System;
using System.Collections.Generic;
using System.Text;

namespace SuperNewRoles.Roles.Neutral
{
    public static class Akujo
    {
        public static void Postfix()
        {
            if (RoleClass.Akujo.CanCreateKeepLimit == RoleClass.Akujo.KeepCreatedCount||//Keep作成可能数がKeep作成数と等しいなら
            RoleClass.Akujo.CanCreateKeepLimit < RoleClass.Akujo.KeepCreatedCount)//また、Keep作成可能数がKeep作成数より少ないなら
            {
                RoleClass.Akujo.IsCanCreateKeep = false;
            }
        }
    }
}