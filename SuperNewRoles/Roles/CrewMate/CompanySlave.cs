using SuperNewRoles.Patch;

namespace SuperNewRoles.Roles
{
    public static class CompanySlave
    {
        public static bool EndTask(PlayerControl p)
        {
            int CheckTask = 0;
            CheckTask = RoleClass.CompanySlave.MurderTask;
            var taskdata = TaskCount.TaskDate(p.Data).Item1;
            if (CheckTask <= taskdata)
            {
                return true;
            }
            return false;
        }
        public static void Postfix()
        {
            foreach (PlayerControl p in RoleClass.CompanySlave.CompanySlavePlayer)
            {
                if (EndTask(PlayerControl.LocalPlayer))
                {
                    p.RpcMurderPlayer(p);
                }
            }
        }
    }
}