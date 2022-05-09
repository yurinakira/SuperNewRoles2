using System.IO;
using System.Reflection;
using UnityEngine;
using UnityEngine.UI;
using Il2CppType = UnhollowerRuntimeLib.Il2CppType;

namespace SuperNewRoles
{
    public static class AssetLoader
    {
        private static readonly Assembly allaudio = Assembly.GetExecutingAssembly();
        private static bool flag = false;
        private static AssetBundle AgarthaAssetBundle;
        public static void LoadAssets()
        {
            if (!flag) return;
            flag = true;
            SuperNewRolesPlugin.Logger.LogInfo("ロード");
            var resourceAudioAssetBundleStream = allaudio.GetManifestResourceStream("SuperNewRoles.Resources.Agartha.AgarthaBundle");
            AgarthaAssetBundle = AssetBundle.LoadFromMemory(resourceAudioAssetBundleStream.ReadFully());
        }
        public static byte[] ReadFully(this Stream input)
        {
            using (var ms = new MemoryStream())
            {
                input.CopyTo(ms);
                return ms.ToArray();
            }
        }
        public static T LoadAsset<T>(string name) where T : UnityEngine.Object
        {
            return null;// AgarthaAssetBundle.LoadAsset(name, Il2CppType.Of<T>())?.Cast<T>();
        }
        public static T DontUnload<T>(this T obj) where T : Object
        {
            obj.hideFlags |= HideFlags.DontUnloadUnusedAsset;
            return obj;
        }
    }


}