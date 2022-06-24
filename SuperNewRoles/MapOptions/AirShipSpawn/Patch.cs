using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace SuperNewRoles.MapOptions
{
    public static class Extensions
    {
        public static T Random<T>(this IList<T> self)
        {
            if (self.Count > 0)
            {
                return self[UnityEngine.Random.Range(0, self.Count)];
            }
            return default;
        }

                public static void Shuffle<T>(this IList<T> self, int startAt = 0)
        {
            for (int i = startAt; i < self.Count - 1; i++)
            {
                T value = self[i];
                int index = UnityEngine.Random.Range(i, self.Count);
                self[i] = self[index];
                self[index] = value;
            }
        }
    }
    public static class ButtonPatch
    {
        public static bool stopCountdown = true;
    }
}
