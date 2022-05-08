using System.IO;
using System.Reflection;
using UnityEngine;
using UnityEngine.UI;

namespace SuperNewRoles
{
    public static class AssetLoader
    {
        private static AssetBundle AgarthaAssetBundle;
        public static void LoadAssets()
        {

            var resourceStreamBundle = Assembly.GetExecutingAssembly().GetManifestResourceStream("SuperNewRoles.Resources.Agartha.Assets");
            var bytedata = new byte[resourceStreamBundle.Length];
            _ = resourceStreamBundle.Read(bytedata, 0, (int)resourceStreamBundle.Length);
            AgarthaAssetBundle = AssetBundle.LoadFromMemory(bytedata);

        }

        public static Sprite GetAgarthaAssets(string path)
        {
            SuperNewRolesPlugin.Logger.LogInfo("path:"+path);
            var data = AgarthaAssetBundle.LoadAsset(path);
            SuperNewRolesPlugin.Logger.LogInfo("b");
            Texture2D texture2D = GameObject.Instantiate(data).TryCast<Texture2D>();
            SuperNewRolesPlugin.Logger.LogInfo("c:"+texture2D);
            Sprite data2 = Sprite.Create(texture2D, new Rect(0, 0, texture2D.width, texture2D.height), Vector2.zero);
            SuperNewRolesPlugin.Logger.LogInfo("d");
            return data2;
        }
    }
}