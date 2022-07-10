#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "stringhelper.h"

using namespace HarmonyLib;
using namespace Newtonsoft::Json::Linq;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;

namespace SuperNewRoles
{
	class ModTranslation
	{
	public:
		static int defaultLanguage;
		static std::unordered_map<std::wstring, std::unordered_map<int, std::wstring>> stringData;

		ModTranslation();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'dynamic' keyword:
		static dynamic LangDate;
		static void Load();

		static unsigned int GetLang();
		static std::wstring getString(const std::wstring &key, const std::wstring &def = L"");

		static Sprite *getImage(const std::wstring &key, float pixelsPerUnit);
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(LanguageSetter), nameof(LanguageSetter.SetLanguage))] class SetLanguagePatch
		class SetLanguagePatch
		{
		private:
			static void Postfix();
		};
	};
}
