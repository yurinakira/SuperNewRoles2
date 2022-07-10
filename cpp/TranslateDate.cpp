#include "TranslateDate.h"
#include "ModHelpers.h"
#include "Patch/ClientOptionsPatch.h"

using namespace HarmonyLib;
using namespace Newtonsoft::Json::Linq;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;

namespace SuperNewRoles
{

int ModTranslation::defaultLanguage = static_cast<int>(SupportedLangs::English);
std::unordered_map<std::wstring, std::unordered_map<int, std::wstring>> ModTranslation::stringData;

	ModTranslation::ModTranslation()
	{

	}

dynamic ModTranslation::LangDate;

	void ModTranslation::Load()
	{
		Assembly *assembly = Assembly::GetExecutingAssembly();
		Stream *stream = assembly->GetManifestResourceStream(L"SuperNewRoles.Resources.translatedate.json");
		auto byteTexture = std::vector<unsigned char>(stream->Length);
		auto read = stream->Read(byteTexture, 0, static_cast<int>(stream->Length));
		std::wstring json = System::Text::Encoding::UTF8->GetString(byteTexture);
		JObject *parsed = JObject::Parse(json);
		for (int i = 0; i < parsed->Count; i++)
		{
			JProperty *token = parsed->ChildrenTokens[i].TryCast<JProperty*>();
			if (token == nullptr)
			{
				continue;
			}

			std::wstring stringName = token->Name;
			auto val = token->Value->TryCast<JObject*>();
			if (token->HasValues)
			{
				auto strings = std::unordered_map<int, std::wstring>();
				for (int j = 0; j < static_cast<int>(SupportedLangs::Irish) + 1; j++)
				{
					std::wstring key = std::to_wstring(j);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
					auto text = val[key] == nullptr ? L"" : val[key].TryCast<JValue*>()->Value->ToString();

					if (text != L"" && text.length() > 0)
					{
						//SuperNewRolesPlugin.Instance.Log.LogInfo($"key: {stringName} {key} {text}");
						strings[j] = text;
					}
				}
				stringData[stringName] = strings;
			}
		}
	}

	unsigned int ModTranslation::GetLang()
	{
		return SaveManager::LastLanguage;
	}

	std::wstring ModTranslation::getString(const std::wstring &key, const std::wstring &def)
	{
		try
		{
			return StringHelper::replace(stringData[key][static_cast<int>(GetLang())], L"\\n", L"\n");
		}
		catch (...)
		{
			try
			{
				return StringHelper::replace(stringData[key][defaultLanguage], L"\\n", L"\n");
			}
			catch (...)
			{
				return key;
			}
		}
	}

	Sprite *ModTranslation::getImage(const std::wstring &key, float pixelsPerUnit)
	{
		key = StringHelper::replace(key, L"/", L".");
		key = StringHelper::replace(key, L"\\", L".");
		key = L"SuperNewRoles.Resources." + key;

		return ModHelpers::loadSpriteFromResources(key, pixelsPerUnit);
	}

	void ModTranslation::SetLanguagePatch::Postfix()
	{
		ClientOptionsPatch::updateTranslations();
	}
}
