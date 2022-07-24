using System;
using System.Collections.Generic;
using System.IO;

namespace SuperNewRoles
{
    public class ModTranslation
    {
        public static Dictionary<string, Dictionary<int, string>> tr;
        public static void Init()
        {
            SuperNewRolesPlugin.Logger.LogInfo("Language Dictionary Initialize...");
            LoadLangs();
            SuperNewRolesPlugin.Logger.LogInfo("Language Dictionary Initialize Finished");
        }
        public static void LoadLangs()
        {
            var assembly = System.Reflection.Assembly.GetExecutingAssembly();
            var stream = assembly.GetManifestResourceStream("SuperNewRoles.Resources.TranslateData.csv");
            var sr = new StreamReader(stream);
            tr = new Dictionary<string, Dictionary<int, string>>();

            string[] header = sr.ReadLine().Split(',');

            int currentLine = 1;

            while (!sr.EndOfStream)
            {
                currentLine++;
                string line = sr.ReadLine();
                if (line == "" || line[0] == '#') continue;
                string[] values = line.Split(',');
                List<string> fields = new(values);
                Dictionary<int, string> tmp = new();
                try
                {
                    for (var i = 1; i < fields.Count; ++i)
                    {
                        if (fields[i] != string.Empty && fields[i].TrimStart()[0] == '"')
                        {
                            while (fields[i].TrimEnd()[^1] != '"')
                            {
                                fields[i] = fields[i] + "," + fields[i + 1];
                                fields.RemoveAt(i + 1);
                            }
                        }
                    }
                    for (var i = 1; i < fields.Count; i++)
                    {
                        var tmp_str = fields[i].Replace("\\n", "\n").Trim('"');
                        tmp.Add(Int32.Parse(header[i]), tmp_str);
                    }
                    if (tr.ContainsKey(fields[0])) { SuperNewRolesPlugin.Logger.LogWarning($"翻訳用CSVに重複があります。{currentLine}行目: \"{fields[0]}\""); continue; }
                    tr.Add(fields[0], tmp);
                }
                catch
                {
                    var err = $"翻訳用CSVファイルに誤りがあります。{currentLine}行目:";
                    foreach (var c in fields) err += $" [{c}]";
                    Logger.Error(err, "Translator");
                    continue;
                }
            }
        }

        public static string GetString(string s, Dictionary<string, string> replacementDic = null)
        {
            var langId = TranslationController.InstanceExists ? TranslationController.Instance.currentLanguage.languageID : SupportedLangs.English;
            string str = GetString(s, langId);
            if (replacementDic != null)
                foreach (var rd in replacementDic)
                {
                    str = str.Replace(rd.Key, rd.Value);
                }
            return str;
        }

        public static string GetString(string s, SupportedLangs langId)
        {
            var res = "";
            if (tr.TryGetValue(s, out var dic))
            {
                if (dic.TryGetValue((int)langId, out res))
                {
                    return res;
                }
                else
                {
                    if (dic.TryGetValue(0, out res))
                    {
                        SuperNewRolesPlugin.Logger.LogInfo($"Redirect to English: {res}");
                        return res;
                    }
                    else
                    {
                        return $"<INVALID:{s}>";
                    }
                }
            }
            else
            {
                return $"<INVALID:{s}>";
            }
        }
    }
}