using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Newtonsoft.Json.Linq;
using UnityEngine;

namespace SuperNewRoles.CustomCommand
{
    class FileManager
    {
        public static (string,string) Get(string cmd)
        {
            string filePath = Path.GetDirectoryName(Application.dataPath) + @"\SuperNewRoles\CustomMessage\";
            string txt = "";
            string name = "";
            if (File.Exists($"{filePath}\\CustomMsg.json"))
            {
                StreamReader sr = new($"{filePath}\\CustomMsg.json");

                string text = sr.ReadToEnd();

                sr.Close();

                JObject json = null;

                try
                {
                    json = JObject.Parse(text);
                }
                catch
                {
                    return ("", "");
                }
                if (json[cmd] != null){
                    txt = json[cmd]["text"]?.ToString();
                    name = json[cmd]["name"]?.ToString();
                }
            } else
            {
                File.Create($"{filePath}\\CustomMsg.json");
            }
            return (txt,name);
        }
        public static bool TryGet(string cmd, ref (string,string) result)
        {
            result = Get(cmd);
            return result.Item1 != "";
        }
    }
}
